#pragma once

#include "BitmaskManager.h"
#include <sfml/Graphics.hpp>
#include <iostream>
#include "Utility.h"



using namespace std;
using namespace sf;

class Collision
{
private:
	static Vector2f getCenterSprite(const Sprite* sprite) {
		auto bound = sprite->getGlobalBounds();

		Vector2f center;
		center.x = bound.left + (bound.width / 2);
		center.y = bound.top + (bound.height / 2);
		return center;
	}

public:
	static int Normal(const Sprite* sprite1, const Sprite* sprite2) {

		auto bound1 = sprite1->getGlobalBounds();
		auto bound2 = sprite2->getGlobalBounds();

		if (bound1.intersects(bound2)) {

			Vector2f c1 = getCenterSprite(sprite1);
			Vector2f c2 = getCenterSprite(sprite2);

			auto positive_x = true;
			auto positive_y = true;

			if (c1.x >= c2.x) {
				positive_x = true;
			}
			else positive_x = false;


			if (c1.y >= c2.y) {
				positive_y = true;
			}
			else positive_y = false;

			if (c1.x >= c2.x) {
				c1.x = c1.x - (bound1.width / 2 + bound2.width / 2);
			}
			else {
				c1.x = c1.x + bound1.width / 2 + bound2.width / 2;
			}

			if (c1.y <= c2.y) {
				c1.y = c1.y + bound1.height / 2 + bound2.height / 2;
			}
			else {
				c1.y = c1.y - (bound1.height / 2 + bound2.height / 2);
			}

			if (std::abs(c1.x - c2.x) <= std::abs(c1.y - c2.y)) {
				return (positive_x == true) ? 1 : -1;
			}
			else {
				return (positive_y == true) ? 2 : -2;
			}
		}
		return 0;
	}

	static bool Cricle(const Sprite* cricle1, const Sprite* cricle2) {
		if (cricle1->getGlobalBounds().intersects(cricle2->getGlobalBounds())) {

			float radius1 = cricle1->getTextureRect().width / 2 * cricle1->getScale().x;
			float radius2 = cricle2->getTextureRect().width / 2 * cricle2->getScale().y;



			auto vec_dis = getCenterSprite(cricle1) - getCenterSprite(cricle2);


			float dis_center = sqrtf(vec_dis.x * vec_dis.x + vec_dis.y * vec_dis.y);

			if (dis_center <= (radius1 + radius2)) {
				return true;
			}
		}
		return false;
	}

	static Vector2f getIntersectionCricle(const Sprite* cricle1, const Sprite* cricle2) {

		FloatRect rec_inter;

		if (cricle1->getGlobalBounds().intersects(cricle2->getGlobalBounds(), rec_inter)) {

			float xi = rec_inter.left + rec_inter.width / 2;
			float yi = rec_inter.top + rec_inter.height / 2;


			return Vector2f(xi, yi);
		}
		return  Vector2f();
	}

	/*static bool Perfect(BitmaskManager* bitmasks, const Sprite* sprite1, const Sprite* sprite2, Uint8 anpha = 0) {

		FloatRect intersection;

		if (sprite1->getGlobalBounds().intersects(sprite2->getGlobalBounds(), intersection)) {

			IntRect rect_cur1 = sprite1->getTextureRect();
			IntRect rect_cur2 = sprite2->getTextureRect();


			Uint8* mask1 = bitmasks->getMask(sprite1->getTexture());
			Uint8* mask2 = bitmasks->getMask(sprite2->getTexture());


			for (unsigned int x = intersection.left; x < intersection.left + intersection.width; x++) {
				for (unsigned int y = intersection.top; y < intersection.top + intersection.height; y++) {

					Vector2f p1 = sprite1->getInverseTransform().transformPoint(x, y);
					Vector2f p2 = sprite2->getInverseTransform().transformPoint(x, y);

					if (p1.x >= 0 && p1.y >= 0 && p2.x >= 0 && p2.y >= 0 && p2.x < rect_cur2.width && p2.y < rect_cur2.height
						&& p1.x < rect_cur1.width && p1.y < rect_cur1.height) {

						if (bitmasks->getPixel(sprite1->getTexture(), mask1, rect_cur1.left + int(p1.x), rect_cur1.top + int(p1.y)) > anpha&&
							bitmasks->getPixel(sprite2->getTexture(), mask2, rect_cur2.left + int(p2.x), rect_cur2.top + int(p2.y)) > anpha) {
							return true;
						}
					}
				}
			}
		}
		return false;
	}*/

};

