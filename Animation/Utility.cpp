#include "Utility.h"

Vector2f Utility::normalize(const Vector2f& vec) {
	float mag = Utility::magnitude(vec);

	if (mag != 0) {
		return sf::Vector2f(vec / mag);
	}
	return sf::Vector2f(0, 0);
}

float Utility::magnitude(const Vector2f& vec) {
	return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

float Utility::radiusToDegree(float angleR) {
	return angleR * float(180 / PI);
}

float Utility::degreeToRadius(float angleD) {
	return angleD * float(PI / 180);
}

float Utility::angle360(const Vector2f& vec) {
	auto angle = atan2f(vec.y, vec.x) * float(180/PI);

	if (angle < 0) {
		angle = float(360 + angle);
	}
	return angle;
}

float Utility::angle(const Vector2f& vec) {
	return atan2f(vec.y, vec.x);
}

float Utility::angleBetween(const Vector2f& vec1, const Vector2f& vec2) {
	float dot = vec1.x * vec2.x + vec1.y * vec2.y;
	float mag = Utility::magnitude(vec1) * Utility::magnitude(vec2);

	return (mag != 0) ? acosf(dot / mag) : 0.f;
}

Vector2f Utility::rotatePoint(const Vector2f& vec, float angleR) {
	sf::Vector2f r_vec;
	r_vec.x = cosf(angleR) * vec.x - sinf(angleR) * vec.y;
	r_vec.y = sinf(angleR) * vec.x + cos(angleR) * vec.y;
	return r_vec;
}

Vector2f Utility::movePoint(const Vector2f& vec, float angleR, float distance) {
	sf::Vector2f point_move;
	point_move.x = vec.x + cosf(angleR) * distance;
	point_move.y = vec.y + sinf(angleR) * distance;
	return point_move;
}

bool Utility::checkAngleInRange360(float value, float start_angle,  float end_angle) {
	bool result =false;

	if (start_angle <= end_angle) {
		if (value >= start_angle && value <= end_angle) {
			result = true;
		}
	}
	else {
		if (value <= end_angle) value = value + 360 ;
		end_angle = 360 + end_angle;
		if (value >= start_angle && value <= end_angle) {
			result = true;
		}
	}
	return result;
}

void Utility::clampPoint(Vector2f& vec, const Vector2f& vec_limit) {
	vec.x = (vec.x <= vec_limit.x) ? vec.x : vec_limit.x;
	vec.y = (vec.y <= vec_limit.y) ? vec.y : vec_limit.y;
}

float Utility::clamp(float& val, float min, float max) {
	if (val < min)
		return min;
	else if (val > max) {
		return max;
	}
	else return val;
}

bool Utility::isZero(const Vector2f& vec) {
	return vec.x == 0 && vec.y == 0;
}

float Utility::dotProduct(const Vector2f& vec1, const Vector2f& vec2) {
	return vec1.x * vec2.x + vec1.y + vec2.y;
}

float Utility::determinant(const Vector2f& vec1, const Vector2f& vec2) {
	return vec1.x * vec2.y - vec1.y * vec2.x;
}

int Utility::orientation(const Vector2f& p, const Vector2f& q, const Vector2f& r) {
	float val = (p.x - q.x) * (r.y - q.y) -(r.x - q.x) * (p.y - q.y);
	if (val == 0) return 0;
	return (val > 0) ? 1 : 2;
}

bool Utility::checkSegmentIntersection(const Vector2f& v1, const Vector2f& v2, const Vector2f& u1, const Vector2f& u2) {
	return determinant(v2 - v1, u1 - v1) * determinant(v2 - v1, u2 - v1) < 0
		&& determinant(u2 - u1, v1 - u1) * determinant(u2 - u1, v2 - u1) < 0;
}

Vector2f Utility::getSegmentIntersection(const Vector2f& v1, const Vector2f& v2, const Vector2f& u1, const Vector2f& u2) {
	if (determinant(v2 - v1, u1 - v1) * determinant(v2 - v1, u2 - v1) < 0
		&& determinant(u2 - u1, v1 - u1) * determinant(u2 - u1, v2 - u1) < 0) {

		if (v1.x - v2.x != 0 && u1.x -u2.x != 0) {
			float a1 = (v1.y - v2.y) / (v1.x - v2.x);
			float a2 = (u1.y - u2.y) / (u1.x - u2.x);

			float b1 = v1.y - a1 * v1.x;
			float b2 = u1.y - a2 * u1.x;

			float Ix = (b2-b1) / ( a1- a2);
			float Iy = a1 * Ix + b1;
			return Vector2f(Ix, Iy);
		}
		if (v1.x - v2.x == 0) {
			float a2 = (u1.y - u2.y) / (u1.x - u2.x);
			float b2 = u1.y - a2 * u1.x;

			float b1 = v1.x;
			float Ix = b1;
			float Iy = a2 *Ix + b2;
			return Vector2f(Ix, Iy);

		}
		if (u1.x - u2.x == 0) {
			float a1 = (v1.y - v2.y) / (v1.x - v2.x);
			float b1 = v1.y - a1 * v1.x;
			float b2 = u1.x;
			float Ix = b2;
			float Iy = a1 * Ix + b1;
			return Vector2f(Ix, Iy);
		}
	}
	return Vector2f();
}

bool Utility::checkSameDirection(const Vector2f& v1, const Vector2f& v2) {
	if (magnitude(v1) != 0 && magnitude(v2) != 0) {

		return normalize(v1) == normalize(v2);
	}
	return false;
}

void Utility::drawLine(const Vector2f& v1, const Vector2f& v2, RenderWindow& window, Color color ) {
	VertexArray line(Lines , 2);
	line[0].position = v1;
	line[0].color = color;
	line[1].position = v2;
	line[1].color = color;
	window.draw(line);
}
void Utility::drawPoint(const Vector2f& pos, const float radius, RenderWindow& window, Color color) {
	CircleShape point;
	point.setRadius(radius);
	point.setPosition(pos - Vector2f{ radius , radius });
	point.setFillColor(color);
	window.draw(point);
}

void Utility::drawTriangle(const Vector2f& p1, const Vector2f& p2, const Vector2f& p3, RenderWindow& window, Color color) {
	ConvexShape triangle;
	triangle.setPointCount(3);

	triangle.setPoint(0, p1);
	triangle.setPoint(1, p2);
	triangle.setPoint(2, p3);

	triangle.setFillColor(color);
	window.draw(triangle);
}

float Utility::map(const float value, const Vector2f rang_src, const Vector2f rang_dist) {

	if (value > rang_src.y) return rang_dist.y;
	if (value < rang_src.x) return rang_dist.x;

	float a1 = value - rang_src.x;
	float a2 = rang_src.y - value;

	if (a2 + a1 == 0) {
		return rang_dist.x;
	}
	float b = a1 * rang_dist.y - a2 * rang_dist.x;
	
	return b / (a1 + a2);
}

