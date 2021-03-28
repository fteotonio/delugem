#pragma once

#include "AnimatedGameObject.h"
#include "../Timer.h"
#include "../Position.h"

class Background : public AnimatedGameObject {
public:
	static const char* cPath;
	static const int cMaxSteps;
	static const int cTimePerStep;
	static const int cW;
	static const int cH;

	Background(Position pos);

	void Update(int deltaTime);
private:
	int steps_ = 0;
	Timer* stepTimer_;
};