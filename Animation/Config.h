#pragma once


#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


namespace Config{
	const string title = "Animation";
	const unsigned int screen_width = 900;
	const unsigned int screen_height = 500;
	const unsigned int FPS = 60;
	const bool showfps = false;
	const float game_speed = 100.f;

	const Vector2f Gravity = { 0 ,0.3 };
}




