#pragma once


#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "TextureManager.h"

using namespace sf;
using namespace std;

class Animation :public Drawable
{

public:
	virtual void draw(RenderTarget& target, RenderStates state) const = 0;

	void setTexture(const Texture* texture, Vector2f scale = {1.f , 1.f}) {
		sprite.setTexture(*texture);
		sprite.setPosition({0 , 0});
		sprite.setScale(scale.x, scale.y);
	}

	void setRectTexture(unordered_map <string, vector<TextureManager::u_rect>>* anim) {
		animation = anim;
	}

	vector<TextureManager::u_rect>* getAnimationState(string state) {

		if (animation == nullptr) return nullptr;
		auto iter_finder = animation->find(state);
		if (iter_finder != animation->end() && iter_finder->second.size() >0) {
			return &iter_finder->second;
		}
		return nullptr;
	}

public:
	Sprite sprite;
	float index_state;

	unordered_map <string, vector<TextureManager::u_rect>>* animation;

};

