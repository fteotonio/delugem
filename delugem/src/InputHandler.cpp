#include "InputHandler.h"

#include "Constants.h"
#include "Game.h"

InputHandler* InputHandler::_inputHandlerInstance = nullptr;

InputHandler* InputHandler::Instance() {
	if (!_inputHandlerInstance) {
		_inputHandlerInstance = new InputHandler();
	}
	return _inputHandlerInstance;
}

bool   InputHandler::GetMouseLeft() { 
	return _mouseLeft; 
}

Sint32 InputHandler::GetMouseX() { 
	return _mouseX / GAME_SCALE; 
}

Sint32 InputHandler::GetMouseY() { 
	return _mouseY / GAME_SCALE; 
}

void InputHandler::Update() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
				_mouseLeft = true;
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
				_mouseLeft = false;
			break;
		case SDL_MOUSEMOTION :
			_mouseX = event.motion.x;  
			_mouseY = event.motion.y;
			break;
		case SDL_QUIT:
			Game::Instance()->Quit();
			break;
		default:
			break;
		}
	}
}

void InputHandler::Clean() {
	delete _inputHandlerInstance;
}