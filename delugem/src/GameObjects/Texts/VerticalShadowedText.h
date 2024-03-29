#pragma once

#include <string>
#include <vector>

#include "../GameObject.h"
#include "Text.h"

class VerticalShadowedText : public GameObject {
public:

	VerticalShadowedText(Position pos, Text::Align align, std::string font, int size, int spacing, std::string text, SDL_Color textColor, SDL_Color shadowColor);

	void Update(int deltaTime);
	void Render();
	void Clean();

private:

	std::vector<GameObject*> _textObjects;

};