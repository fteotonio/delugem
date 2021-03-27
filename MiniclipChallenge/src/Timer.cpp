#include "Timer.h"

Timer::Timer(int milliseconds, bool startNow) {
	timeToPass_ = milliseconds;
	isRunning_ = startNow;
}

bool Timer::IsRunning() { return isRunning_; }

void Timer::ResetTimer() {
	timePassed_ = 0;
	isRunning_ = true;
}

void Timer::ResetTimer(int milliseconds) {
	timeToPass_ = milliseconds;
	timePassed_ = 0;
	isRunning_ = true;
}

void Timer::StartTimer() {
	isRunning_ = true;
}

void Timer::PauseTimer() {
	isRunning_ = false;
}

bool Timer::HasRung() {
	return (isRunning_ && timePassed_ > timeToPass_);
}

float Timer::HowMuchPassed() {
	return timePassed_ / (timeToPass_ * 1.0f);
}

void Timer::Update(int deltaTime) {
	if (isRunning_)
		timePassed_ += deltaTime;
}