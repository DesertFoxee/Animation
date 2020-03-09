#include <SFML/Graphics.hpp>
#include "Collision.h"
#include <iostream>
#include "TextureManager.h"
#include "Pinkpet.h"
#include "Config.h"

using namespace sf;
using namespace std;
using namespace Config;

sf::RenderWindow window;


Clock clockfps;
Clock clock1;
Clock time_refes_title;


float accumulator = 0;
const float timestep = 1.0f / FPS;



vector<Sprite> bg;
TextureManager texture;
Pinkpet pet;


void drawRectangle(Sprite* sprite) {

	auto bound = sprite->getGlobalBounds();


	Vector2f pos = { bound.left , bound.top };
	float width = bound.width;
	float height = bound.height;
	RectangleShape shape;

	shape.setFillColor(Color::Transparent);
	shape.setPosition(pos);

	shape.setOutlineThickness(1);
	shape.setOutlineColor(Color::Red);
	shape.setSize({ width , height });

	window.draw(shape);
}


void setup() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window.create(sf::VideoMode(screen_width, screen_height), title, sf::Style::Default, settings);

	texture.loadTextureFromXML("assets/config.xml");
	texture.loadSpriteSheet();


	for (auto i = 0; i < 5; i++) {
		Sprite sprite;
		sprite.setTexture(*texture.getTexture("ground"));
		bg.push_back(sprite);
	}


	bg[0].setPosition({ 100  , 260 });
	bg[1].setPosition({ 170  , 260 });
	bg[2].setPosition({ 240  , 260 });
	bg[3].setPosition({ 70  , 100 });
	bg[4].setPosition({ 0  , 100 });

	pet.setTexture(texture.getTexture("pinkpet"));
	pet.setRectTexture(texture.getRectTexture("pinkpet"));

	pet.setState("basic");
	pet.setPosition({ 400 ,100 });
	pet.sprite.setScale(2, 2);


}


void process(float dt) {
	if (sf::Keyboard::isKeyPressed(Keyboard::A)) {

		pet.setState(Pinkpet::State::LEFT);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::D)) {

		pet.setState(Pinkpet::State::RIGHT);

	}
	if (sf::Keyboard::isKeyPressed(Keyboard::W)) {

		pet.setState(Pinkpet::State::JUMP);
	}

	pet.process();

}

void processOne(sf::Event& event) {
	if (event.type == sf::Event::EventType::Closed) {
		window.close();
	}

	if (event.type == sf::Event::EventType::KeyReleased) {
		if (event.key.code == Keyboard::A) {
			;
			pet.setState(Pinkpet::State::BASIC);
		}
		if (event.key.code == Keyboard::D) {
			pet.setState(Pinkpet::State::BASIC);
			
		}
	}
}
void update(float dt) {
	pet.update(dt);

	//pet.checkCollision(&bg);





	//vec += acc * dt;
	//loc += vec * dt;

	//human.setPosition(loc);
	//acc *= 0.f;

}

void draw() {
	window.draw(pet);

	for (auto b : bg) {
		window.draw(b);
	}

	//drawRectangle(&background);

}



void clear() {
	window.clear();
}


void display() {
	window.display();
}


void miscellaneous() {
	if (showfps) {
		auto time = clock1.restart().asMilliseconds();
		auto time_refes = time_refes_title.getElapsedTime().asMilliseconds();
		if (time_refes > 100) {
			window.setTitle(title + "- FPS : " + std::to_string(1000 / time));
			time_refes_title.restart();
		}
	}
}

int main() {

	setup();

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			processOne(event);
		}

		accumulator = clockfps.restart().asSeconds();


		process(accumulator * 20.f);

		while (accumulator >= timestep) {
			accumulator -= timestep;
			update(timestep * game_speed);
		}
		update(accumulator / timestep);

		clear();
		draw();
		display();
		miscellaneous();

	}

	return 0;
}






