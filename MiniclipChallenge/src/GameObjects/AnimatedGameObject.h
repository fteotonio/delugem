#pragma once

#include<SDL_image.h>
#include<map>
#include<string>

#include "GameObject.h"
#include "../Animation.h"

class AnimatedGameObject : public GameObject { 
public:  
	virtual void Init(float x, float y, int w, int h, SDL_Texture* texture, std::string animationID, bool playNow);
	virtual void Update(int deltaTime);
	virtual void Render();
	virtual void Clean();

	virtual void addAnimation(std::string id, Animation* animation);
	virtual void setAnimation(std::string id, bool playNow);
protected:
	int w_;
	int h_;

	SDL_Texture* texture_;
	Animation* currentAnimation_;
	std::map<std::string, Animation*> animations_;
};