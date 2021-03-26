#include "Game.h"

#include "GameStates/TitleScreenState.h"
#include "GameStates/PlayingState.h"
#include "GameObjects/Background.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "GameManager.h"
#include "SoundManager.h"

#include <iostream>

#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>

#define MUS_ONLYTRACK		"res/sounds/visager_shoots.mp3"
#define SND_BREAK			"res/sounds/break.wav"
#define SND_PUSHCOLUMN		"res/sounds/columnpush.wav"
#define SND_FILL			"res/sounds/fill.wav"
#define SND_GAMEOVER		"res/sounds/gameover.wav"
#define SND_GAMESTART		"res/sounds/gamestart.wav"
#define SND_LEVELUP			"res/sounds/levelup.wav"
#define SND_PIECEFALL		"res/sounds/piecefall.wav"

Game* Game::sGameInstance_ = nullptr;

Game* Game::Instance() {
	if (!sGameInstance_) {
		sGameInstance_ = new Game();
	}
	return sGameInstance_;
}

bool Game::bRunning() { return bRunning_; }
GameStateMachine* Game::gameStateMachine() { return gameStateMachine_; }
SDL_Renderer* Game::renderer() { return renderer_; }

bool Game::Init(const char* title, int width, int height, bool fullscreen) {
	//INIT WINDOW AND RENDERER

	int flags = 0;
	
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (window_) {
			std::cout << "Window created successfully.\n";
			renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
			if (renderer_) {
				std::cout << "Renderer created successfully.\n";
				SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
			}
			else {
				std::cout << "Renderer creation failed.\n";
				return false;
			}
		}
		else {
			std::cout << "Window creation failed.\n";
			return false;
		}
		std::cout << "SDL_Init successful.\n";
		bRunning_ = true;


		TextureManager::Instance();
		if (TTF_Init() != 0) {
			std::cout << "TTF Init failed.\n";
			return false;
		}
		InputHandler::Instance();
		SoundManager::Instance();

		GameManager::Instance();
		

		//SoundManager::Instance()->Load(MUS_ONLYTRACK,"onlyTrack",SoundManager::soundType::MUSIC,4);
		//SoundManager::Instance()->playMusic("onlyTrack", 1);
		//SoundManager::Instance()->setMusicPosition(33.5);

		//Load SFX
		SoundManager::Instance()->Load(SND_BREAK,     "Break",     SoundManager::soundType::SFX, 8);
		SoundManager::Instance()->Load(SND_PUSHCOLUMN,"PushColumn",SoundManager::soundType::SFX, 8);
		SoundManager::Instance()->Load(SND_FILL,      "Fill",      SoundManager::soundType::SFX, 12);
		SoundManager::Instance()->Load(SND_GAMEOVER,  "GameOver",  SoundManager::soundType::SFX, 16);
		SoundManager::Instance()->Load(SND_GAMESTART, "GameStart", SoundManager::soundType::SFX, 12);
		SoundManager::Instance()->Load(SND_LEVELUP,	  "LevelUp",   SoundManager::soundType::SFX, 8);
		SoundManager::Instance()->Load(SND_PIECEFALL, "PieceFall", SoundManager::soundType::SFX, 8);

		background_ = new Background(-15, 0);

		gameStateMachine_ = new GameStateMachine();
		gameStateMachine_->pushState(new TitleScreenState());
		
		return true;
		//----------------------------------
	}
	else {
		std::cout << "SDL_Init failed.\n";
		return false;
	}
}

void Game::HandleEvents() {
	InputHandler::Instance()->Update();
}

void Game::Quit() {
	bRunning_ = false;
}

void Game::Update(int deltaTime) {
	background_->Update(deltaTime);
	gameStateMachine_->Update(deltaTime);
}

void Game::Render() {

	SDL_RenderClear(renderer_);
	background_->Render();

	gameStateMachine_->Render();

	SDL_RenderPresent(renderer_);
}

void Game::Clean() {
	
	background_->Clean();

	TextureManager::Instance()->Clean();
	InputHandler::Instance()->Clean();

	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer_);
	TTF_Quit();
	SDL_Quit();

	delete gameStateMachine_;
	delete sGameInstance_;
}