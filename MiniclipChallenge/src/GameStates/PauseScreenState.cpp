#include "PauseScreenState.h"

#include "../Constants.h"
#include "../GameObjects/ForegroundStrip.h"
#include "../GameObjects/Buttons/BigButton.h"
#include "../GameObjects/Texts/ShadowedText.h"
#include "../Game.h"
#include "../GameManager.h"
#include "PlayingState.h"
#include "TitleScreenState.h"

void PauseScreenState::Init() {

	stateID_ = "PAUSESCREEN";

	gameObjects_.push_back(new ForegroundStrip(0, 0));
	gameObjects_.push_back(new ForegroundStrip(0, SCREEN_HEIGHT- ForegroundStrip::cH));

	gameObjects_.push_back(new ShadowedText(SCREEN_WIDTH/2, SCREEN_HEIGHT/2-50, Text::Align::MID, FNT_M6X11, 32, "GAME PAUSED", WHITE, BLACK));
	gameObjects_.push_back(new ShadowedText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 30, Text::Align::MID, FNT_M3X6, 16, "The Gems can wait, don't worry.", WHITE, BLACK));
	
	float bXR = SCREEN_WIDTH / 2 - 60 - BigButton::cW / 2;
	float bXE = SCREEN_WIDTH / 2 + 60 - BigButton::cW / 2;
	float bY = 140;
	gameObjects_.push_back(resumeButton_ = new BigButton(bXR, bY));
	resumeButton_->AddContent(new ShadowedText(bXR + BigButton::cW / 2, bY + BigButton::cH / 2, Text::Align::MID, FNT_M6X11, 16, "RESUME", WHITE, BLACK));


	gameObjects_.push_back(new ShadowedText(SCREEN_WIDTH / 2, 110, Text::Align::MID, FNT_M6X11, 16, "CURRENT SCORE: " + std::to_string(GameManager::Instance()->score()), WHITE, BLACK));

	
	gameObjects_.push_back(exitButton_ = new BigButton(bXE, bY));
	exitButton_->AddContent(new ShadowedText(bXE + BigButton::cW / 2, bY + BigButton::cH / 2, Text::Align::MID, FNT_M6X11, 16, "EXIT GAME", WHITE, BLACK));
}

void PauseScreenState::Update(int deltaTime) {
	GameState::Update(deltaTime);

	if (resumeButton_->buttonState() == Button::ButtonState::PRESS_ACTION) {
		Game::Instance()->gameStateMachine()->popState();
		return;
	}
	if (exitButton_->buttonState() == Button::ButtonState::PRESS_ACTION)
		Game::Instance()->gameStateMachine()->changeState(new TitleScreenState());
}