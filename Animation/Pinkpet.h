#pragma once

#include "Animation.h"
#include "Utility.h"
#include "Collision.h"
#include "Config.h"


const float max_vec_x = 3.3;


class Pinkpet : public Animation
{

public:
	class State
	{
	public:
		static constexpr const char* LEFT = "walkleft";
		static constexpr const char* RIGHT = "walkright";
		static constexpr const char* BASIC = "basic";
		static constexpr const char* JUMP = "jump";
	private:
		State();
	};

private:
	void draw(RenderTarget& target, RenderStates sates)const {
		target.draw(sprite);
	}

public:


	void update(float dt) {

		vec += acc * dt;

		if (vec.x > max_vec_x) {
			vec.x = max_vec_x;
		}
		else if (vec.x < -max_vec_x) {
			vec.x = -max_vec_x;
		}

		loc += vec * dt;

		auto anim_state = Animation::getAnimationState(state);

		if (anim_state != nullptr) {
			auto index = unsigned int(index_state) % anim_state->size();
			sprite.setTextureRect((*anim_state)[index].rect);
			index_state += dt * (*anim_state)[index].speed / 100.f * Utility::magnitude(vec);
		}
		sprite.setPosition(loc);

		acc *= 0.f;
	}

	bool checkCollisionGround(vector<Sprite>* groundSprite) {
		for (auto ground : *groundSprite) {
			auto pos = Collision::Normal(&sprite, &ground);
			if (pos != 0) return true;
		}
		return false;
	}

	void checkCollision(vector<Sprite>* groundSprite) {

		if (checkCollisionGround(groundSprite) == true) {
			for (auto ground : *groundSprite) {
				auto pos = Collision::Normal(&sprite, &ground);
				if (pos == 1) {
					loc.x = ground.getGlobalBounds().left + ground.getGlobalBounds().width;
					if (vec.x <= 0) {
						vec.x = -vec.x / 2;
					}
				}
				else if (pos == -1) {
					loc.x = ground.getGlobalBounds().left - sprite.getGlobalBounds().width;
					if (vec.x >= 0) {
						vec.x = 0;
					}
				}
				else if (pos == 2) {
					loc.y = ground.getGlobalBounds().top + ground.getGlobalBounds().height;
					if (vec.y <= 0) {
						vec.y = -vec.y;
					}
				}
				else if (pos == -2) {
					loc.y = ground.getGlobalBounds().top - sprite.getGlobalBounds().height;
					vec.y = 0;
					if (state == State::JUMP) {
						vec.x = 0;
					}
					state = State::BASIC;
				}
			}
		}
		else {

			acc += Config::Gravity;
		}
	}

	void process() {
		if (state == State::BASIC) {
			vec.x *= 0.f;
		}
		if (state == State::LEFT) {
			acc.x += -0.3;
			//if (state != State::Jump)
			//	state = State::Left;
		}
		if (state == State::RIGHT) {
			acc.x += 0.5;
			//if (state != State::Jump)
			//	state = State::Right;
		}
		if (state == State::JUMP) {
			/*	if (state == State::None) {

				}*/
			vec.y = -10;
		}
		
	}

	void setState(string state) {
		this->state = state;
	}
	void setPosition(Vector2f pos) {
		this->loc = pos;
		sprite.setPosition(pos);
	}
public:
	Vector2f loc;
	Vector2f acc;
	Vector2f vec;

	string state;

};

