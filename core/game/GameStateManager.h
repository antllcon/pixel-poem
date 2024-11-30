#pragma once

class GameStateManager {
   public:
    enum class GameState { Start, Play, Pause, End };
    enum class GamePlayState { None, Attack, Sleep };

    GameStateManager();

    GameState getState() const;
    GamePlayState getPlayState() const;
    void setState(GameState state);
    void setPlayState(GamePlayState state);


   private:
    GameState currentState;
    GamePlayState currentPlayState;
};