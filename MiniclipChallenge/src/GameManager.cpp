#include "GameManager.h"

#include "Constants.h"
#include "SoundManager.h"

#include <cmath>

//TEMP INCLUDE 
#include <iostream>

GameManager* GameManager::sGameManagerInstance_ = nullptr;

const int GameManager::cColumnTime = 10000;
const float GameManager::cColumnTimeMultiplier = 0.95f;
const int GameManager::cEndGemsMargin = 4;
const int GameManager::cStartColumns = 13;

int GameManager::GetLevel() { return level_; }
int GameManager::GetScore() { return score_; }
int GameManager::GetFillsLeft() { return fillsLeft_; }


int GameManager::TimePerColumn() {
	return cColumnTime * pow(cColumnTimeMultiplier, GameManager::Instance()->GetLevel() - 1);
}

GameManager* GameManager::Instance() {
	if (!sGameManagerInstance_) {
		sGameManagerInstance_ = new GameManager();
	}
	return sGameManagerInstance_;
}

void GameManager::AddScore(int gemNumber) {

	score_ += 10 * pow(2, gemNumber - 1);

	while (score_ >= 1000 * level_ + 100 * (static_cast<int>(pow(2, level_-1))-1) ) {
		SoundManager::Instance()->PlaySFX("LevelUp", false);
		++level_;
		if (fillsLeft_ <= 9) {
			++fillsLeft_;
		}
	}
		
	//1 - 1000  = 1000 +     0
	//2 - 2100  = 2000 +   100
	//3 - 3200  = 3000 +   200
	//4 - 4400  = 4000 +   400
	//5 - 5800  = 5000 +   800
	//6 - 7600  = 6000 +  1600
	//7 - 10200 = 7000 +  3200
	//8 - 14400 = 8000 +  6400
	//9 - 21800 = 9000 + 12800
}

void GameManager::UseFill() {
	--fillsLeft_;
}

void GameManager::Reset() {
	level_ = 1;
	score_ = 0;
	fillsLeft_ = 2;
}