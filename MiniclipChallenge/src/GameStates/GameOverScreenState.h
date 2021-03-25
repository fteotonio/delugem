#pragma once

#include "GameState.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Button.h"

#include <vector>

class GameOverScreenState : public GameState {
public:
	void Init();
	void Update(int deltaTime);
	void Render();
	void Clean();

	std::string stateID();
private:
	static const std::string stateID_;
	std::vector<GameObject*> gameObjects_;

	Button* playAgainButton_;
	Button* exitButton_;
};
