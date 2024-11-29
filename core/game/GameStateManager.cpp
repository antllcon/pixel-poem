#include "GameStateManager.h"

GameStateManager::GameStateManager() : currentState(GameState::Start), currentPlayState(GamePlayState::None) {}

GameStateManager::GameState GameStateManager::getState() const { return currentState; }

GameStateManager::GamePlayState GameStateManager::getPlayState() const { return currentPlayState; }

void GameStateManager::setState(GameState state) { currentState = state; }

void GameStateManager::setPlayState(GamePlayState state) { currentPlayState = state; }
