#ifndef WALL_H
#define WALL_H


#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Utility.h"

using namespace std;
using namespace sf;




class Wall : public Drawable
{
	struct Uwall
	{
		Vector2f start;
		Vector2f end;
	};

private:
	vector<Uwall> getSegmentWalls() {

		vector<Uwall> walls;

		for (unsigned int i = 0; i < points.size(); i++) {
			Uwall wall;
			wall.start = points[i];

			if (&points[i] == &points.back()) {
				if (points.size() > 2) {
					wall.end = points[0];
				}
				else {
					break;
				}
			}
			else  wall.end = points[i + 1];

			walls.push_back(wall);
		}

		return walls;
	}

private:
	virtual void draw(RenderTarget& target, RenderStates states) const {

		Color color_shape = Color::White;

		if (points.size() == 2) {
			VertexArray line(Lines, 2);

			line[0].position = points[0];
			line[1].position = points[1];

			line[0].color = color_shape;
			line[1].color = color_shape;
			target.draw(line);
		}
		else {
			ConvexShape shape_wall;

			shape_wall.setPointCount(points.size());

			for (unsigned int i = 0; i < points.size(); i++) {
				shape_wall.setPoint(i, points[i]);
				shape_wall.setFillColor(color_shape);
			}
			target.draw(shape_wall);

		}
	}


	vector<Vector2f > points;


private:
	void loadPoints(Vector2f point) {
		points.push_back(point);
	}

	template<typename... Types>
	void loadPoints(Vector2f p_first, Types... p_rest) {
		points.push_back(p_first);
		loadPoints(p_rest...);
	}

public:
	Wall() {};


	template<typename... Types>
	void init(Types... points) {
		this->loadPoints(points...);
	}


	void update() {};

	bool checkIntersection(Vector2f src, Vector2f dist) {
		auto walls = this->getSegmentWalls();
		for (Uwall& wall : walls) {
			if (Utility::checkSegmentIntersection(src, dist, wall.start, wall.end)) {
				return true;
			}
		}
		return false;
	}

	Vector2f getIntersection(Vector2f src, Vector2f dist) {

		auto walls = this->getSegmentWalls();
		Vector2f intersection(-10000, 10000);

		for (Uwall& wall : walls) {
			Vector2f intersec;
			intersec = Utility::getSegmentIntersection(src, dist, wall.start, wall.end);

			if (Utility::checkSegmentIntersection(src, dist, wall.start, wall.end)) {
				if (Utility::magnitude(src - intersection) >= Utility::magnitude(src - intersec)) {
					intersection = intersec;
				}
			}
		}

		return intersection;
	};
	bool checkCollision(Vector2f s, Vector2f d) {
		if (points.size() == 1 || points.size() == 0) return false;

		vector<Uwall> wall_segments = this->getSegmentWalls();

		for (auto wall_segment : wall_segments) {
			if (Utility::checkSegmentIntersection(s, d, wall_segment.start, wall_segment.end))
				return true;
		}
		return false;
	}

	bool checkPerfectCollision() {
		return false;
	}
};

#endif // !WALL_H

