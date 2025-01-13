#include "Enemy.h"

#include <cmath>
#include <random>

#include "../../Utils.h"
#include "../../core/config.h"

Enemy::Enemy(EnemyState state, sf::Color color, int health, int speed, float directionChangeInterval, float timeSinceDirectionChange, sf::Vector2f position)
    : animation(ANIMATION_SPEED),
      position(position),
      state(state),
      weapon(WeaponType::Pistol),
      health(health),
      size(BOT_SIZE),
      isAlive(true),
      speed(speed),
      directionChangeInterval(directionChangeInterval),
      timeSinceDirectionChange(timeSinceDirectionChange) {
    enemy.setFillColor(color);
    enemy.setSize(sf::Vector2f(size, size));
    enemy.setOrigin(enemy.getLocalBounds().width / 2, enemy.getLocalBounds().height / 2);

    sf::Texture texture;
    if (rand() % 2 == 0) {

        for (int i = 1; i <= 4; ++i) {
            // рандомно эта или эта текстура
            texture.loadFromFile(SRC_SKELETON + std::to_string(i) + PNG);
            animation.addFrame(texture);
        }
    } else {
        for (int i = 1; i <= 4; ++i) {
            texture.loadFromFile(SRC_VAMPIRE + std::to_string(i) + PNG);
            animation.addFrame(texture);
        }
    }

    animation.applyToSprite(sprite);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(position);
    sprite.setScale(SCALE_FACTOR_LEFT);
}

void Enemy::draw(sf::RenderWindow& window) { window.draw(sprite); }

void Enemy::update(float deltaTime) {
    // Рассчитываем целевую позицию
    sf::Vector2f targetPosition = position + moveDirection * speed * deltaTime;

    // Проверка коллизий (внешний вызов CollisionManager должен откатить движение, если нужно)
    position = targetPosition;  // Применяем движение
    enemy.setPosition(position);
    sprite.setPosition(position);

    animation.update(deltaTime);
    animation.applyToSprite(sprite);


    // Сохраняем текущую позицию для последующего отката
    previousPosition = position;
}

void Enemy::processInput(sf::Vector2f playerPosition, float globalTime, std::vector<Bullet>& gameBullets) {
    processViewDirection(playerPosition);
    if (state == EnemyState::attack) {
        processShoot(globalTime, gameBullets);
    }
    if (globalTime - timeSinceDirectionChange > directionChangeInterval) {
        setRandomDirection();
        timeSinceDirectionChange = globalTime;
    }
}

void Enemy::processViewDirection(sf::Vector2f playerPosition) {
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
        sprite.setScale(SCALE_FACTOR_LEFT);
    } else if (newDirection.x < 0) {
        sprite.setScale(SCALE_FACTOR_RIGHT);
    }
}

void Enemy::processShoot(float globalTime, std::vector<Bullet>& gameBullets) {
    auto bulletOpt = weapon.tryShoot(position, viewDirection, globalTime, Bullet::OwnerType::Bot);
    if (bulletOpt) {
        SoundManager::getInstance().playSound(SoundEffect::Fire);
        gameBullets.push_back(bulletOpt.value());
    }
}

void Enemy::setRandomDirection() {
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

void Enemy::setPosition(float x, float y) { position = sf::Vector2f(x, y); }

sf::Vector2f Enemy::getPosition() const { return position; }

void Enemy::takeDamage(int damage) {
    health -= damage;
    if (health <= 0 && isAlive) {
        isAlive = false;
    }
}

bool Enemy::getIsAlive() const { return isAlive; }

sf::FloatRect Enemy::getGlobalBounds() const { return enemy.getGlobalBounds(); }

void Enemy::setViewDirection(const sf::Vector2f& newViewDirection) { viewDirection = newViewDirection; }

EnemyState Enemy::getState() const { return state; }

void Enemy::setState(EnemyState newState) { state = newState; }

void Enemy::blockMovement() {
    position = previousPosition;
    setRandomDirection();
    enemy.setPosition(position);
}
