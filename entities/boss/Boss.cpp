#include "Boss.h"

#include <iostream>
#include <random>

#include "../../core/config.h"

Boss::Boss(BossState state, sf::Color color, int health, int speed, float directionChangeInterval, float timeSinceDirectionChange, sf::Vector2f position)
    : animation(ANIMATION_SPEED),
      position(position),
      state(state),
      weapon(WeaponType::Rifle),
      health(health),
      size(BOSS_SIZE),
      isAlive(true),
      speed(speed),
      directionChangeInterval(directionChangeInterval),
      timeSinceDirectionChange(timeSinceDirectionChange) {
    boss.setFillColor(color);
    boss.setSize(sf::Vector2f(size, size));
    boss.setOrigin(boss.getLocalBounds().width / 2, boss.getLocalBounds().height / 2);
    setRandomDirection();

    for (int i = 1; i <= 4; ++i) {
        sf::Texture texture;
        texture.loadFromFile(SRC_SKULLER + std::to_string(i) + PNG);
        animation.addFrame(texture);
    }

    animation.applyToSprite(sprite);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(position);
    sprite.setScale(SCALE_FACTOR_BOSS_LEFT);

    if (!font.loadFromFile(SRC_FONT_MONOCRAFT)) {
        throw std::runtime_error("Failed to load font");
    }
    healthText.setFont(font);
    healthText.setCharacterSize(FONT_SIZE);
    healthText.setFillColor(COLOR_LIGHT_YELLOW);

}

void Boss::processInput(sf::Vector2f playerPosition, float globalTime, std::vector<Bullet>& gameBullets) {
    processViewDirection(playerPosition);
    if (state == BossState::attack) {
        processShoot(globalTime, gameBullets, playerPosition);
    }
}

void Boss::processViewDirection(sf::Vector2f playerPosition) {
    sf::Vector2f newDirection(0.f, 0.f);

    float deltaX = playerPosition.x - position.x;
    float deltaY = playerPosition.y - position.y;

    if (std::abs(deltaX) > std::abs(deltaY)) {
        newDirection.x = (deltaX > 0) ? 1.f : -1.f;
    } else {
        newDirection.y = (deltaY > 0) ? 1.f : -1.f;
    }
    setViewDirection(newDirection);
    if (newDirection.x > 0) {
        sprite.setScale(SCALE_FACTOR_BOSS_LEFT);
    } else if (newDirection.x < 0) {
        sprite.setScale(SCALE_FACTOR_BOSS_RIGHT);
    }
}

void Boss::processShoot(float globalTime, std::vector<Bullet>& gameBullets, sf::Vector2f playerPosition) {
    // Вычисляем направление на игрока
    sf::Vector2f directionToPlayer = playerPosition - position;

    // Нормализуем направление
    float length = std::sqrt(directionToPlayer.x * directionToPlayer.x + directionToPlayer.y * directionToPlayer.y);
    if (length != 0) {
        directionToPlayer /= length;  // Делаем вектор единичным
    }

    // Устанавливаем направление выстрела
    viewDirection = directionToPlayer;

    // Пытаемся выстрелить
    auto bulletOpt = weapon.tryShoot(position, viewDirection, globalTime, Bullet::OwnerType::Boss);
    if (bulletOpt) {
        gameBullets.push_back(bulletOpt.value());
    }
}

void Boss::setRandomDirection() {
    static std::default_random_engine engine(std::random_device{}());
    static std::uniform_real_distribution<float> dist(-1.f, 1.f);

    // Случайное направление
    float x = dist(engine);
    float y = dist(engine);

    // Избегаем направления в стену (делаем противоположное текущему)
    if (moveDirection.x != 0) x = -moveDirection.x;
    if (moveDirection.y != 0) y = -moveDirection.y;

    // Нормализуем вектор направления
    float length = std::sqrt(x * x + y * y);
    if (length != 0) {
        moveDirection = sf::Vector2f(x / length, y / length);
    } else {
        moveDirection = sf::Vector2f(0.f, 0.f);
    }
}

void Boss::draw(sf::RenderWindow& window) { window.draw(sprite); window.draw(healthText);}

void Boss::update(float deltaTime) {
    // Рассчитываем целевую позицию
    sf::Vector2f targetPosition = position + moveDirection * speed * deltaTime;

    // Проверка коллизий (внешний вызов CollisionManager должен откатить движение, если нужно)
    position = targetPosition;  // Применяем движение
    boss.setPosition(position);
    sprite.setPosition(position);

    animation.update(deltaTime);
    animation.applyToSprite(sprite);

    // Сохраняем текущую позицию для последующего отката
    previousPosition = position;

    healthText.setString("Health [ " + std::to_string(health) + " ]");
    healthText.setPosition(position.x - healthText.getLocalBounds().width / 2, position.y + size / 2 + 5.f);
}

void Boss::setPosition(float x, float y) { position = sf::Vector2f(x, y); }

sf::Vector2f Boss::getPosition() const { return position; }

void Boss::takeDamage(int damage) {
    std::cout << " Boss health - " + std::to_string(health) << std::endl;
    health -= damage;
    if (health <= 0 && isAlive) {
        isAlive = false;
    }
}

bool Boss::getIsAlive() const { return isAlive; }


sf::FloatRect Boss::getGlobalBounds() const { return boss.getGlobalBounds(); }

void Boss::setViewDirection(const sf::Vector2f& newViewDirection) { viewDirection = newViewDirection; }

BossState Boss::getState() const { return state; }

void Boss::setState(BossState newState) { state = newState; }

void Boss::blockMovement() {
    position = previousPosition;  // Возвращаемся к предыдущей позиции
    setRandomDirection();         // выбираем случайное направление двжиения
    boss.setPosition(position);  // Обновляем положение в графике
}
