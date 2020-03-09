#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/Graphics.hpp>

#define PI 3.14159265359

using namespace sf;

class Utility
{

public:
	

	static Vector2f normalize(const Vector2f& vec);

	/*
		Converted from radius to degree
		- return float degree
	*/
	static float radiusToDegree(float angleR);

	/*
		Converted from degree to radius
		- return float radius
	*/
	static float degreeToRadius(float angleD);

	/*
		Calculate the magnitude of the vector
		- return float 
		-> Error : 0.f
	*/
	static float magnitude(const Vector2f& vec);

	/*
		Calculate the angle of the vector [Vector corner with horizontal axis]
		Note :Anticlockwise
		- return radius [0 -> 2*PI]
	*/
	static float angle360(const Vector2f& vec);

	/*
		Calculate the angle of the vector [Vector corner with horizontal axis]
		Note :Anticlockwise
		- return radius [0->PI] and [-PI->0]
	*/
	static float angle(const Vector2f& vec);

	/*
		Calculate the angle of two vector
		- return radius [0->PI] 
	*/
	static float angleBetween(const Vector2f& vec1, const Vector2f& vec2);

	/*
		Rotate the vector at the current position an angle
		- return Vector2f [new point]
	*/
	static Vector2f rotatePoint(const Vector2f& vec, float angleR);

	/*
		Find the new position of the point knowing angle and distance
		- return Vector2f [new point]
	*/
	static Vector2f movePoint(const Vector2f& vec, float angleR, float distance);

	/*
		Check values in the range value start to end value [0->360]
		Note : degree
		- return true  _ Ex: 9 in [250 -> 10]
		- return false _ Ex : 9 not in [10->170]
	*/
	static bool checkAngleInRange360( float value , float start_angle , float end_angle);
	
	/*
		Point limit in the range [vec.x , vec.y]
		- return Vector2f
	*/
	static void clampPoint(Vector2f& vec, const Vector2f& vec_limit);

	/*
		Value limit in the range [min , max]
		- return float
	*/
	static float clamp(float& val, float min, float max);

	/*
		Equal test with vector(0 , 0)
		- return true  : yes
		- return false : no
	*/
	static bool isZero(const Vector2f& vec);

	/*
		Find dot product
		- return float
	*/
	static float dotProduct(const Vector2f& vec1, const Vector2f& vec2);

	/*
		Find dêtrminant
		- return float
	*/
	static float determinant(const Vector2f& vec1, const Vector2f& vec2);

	/*
		To find orientation of ordered triplet (p, q, r).
		- return 0 They colinear
		- return 1 They are all clockwise
		- return 2 Thay are counter clockwise
	*/
	static int orientation(const Vector2f& p, const Vector2f& q, const Vector2f& r);

	/*
		Check two segment intersection
		- return true : intersect
		- return fale : not intersect
	*/
	static bool checkSegmentIntersection(const Vector2f& v1, const Vector2f& v2, const Vector2f& u1, const Vector2f& u2);

	/*
		Get point two segment intersection
		- return Vector2f point
	*/
	static Vector2f getSegmentIntersection(const Vector2f& v1, const Vector2f& v2, const Vector2f& u1, const Vector2f& u2);

	/*
		Check two vetor same direction
		- return true : if the same
		- return flase : then
	*/
	static bool checkSameDirection(const Vector2f& v1, const Vector2f& v2);

	/*
		Draw point used CircleShape
		- return graphic : draw point with radius
	*/
	static void drawPoint(const Vector2f& pos, const float radius, RenderWindow& window, Color color = Color::White);

	/*
		Draw point used ConvexShape
		- return graphic : draw triangle with three point
	*/
	static void drawTriangle(const Vector2f& p1, const Vector2f& p2, const Vector2f& p3, RenderWindow& window, Color color = Color::White);

	/*
		Draw line used VertexArray
		- return graphic : draw line two point
	*/
	static void drawLine(const Vector2f& v1, const Vector2f& v2, RenderWindow& window, Color color = Color::White);

	/*
		Mapping value from source to destination ranges [a-b] -> [c-d]
		- return float : x => [c-d]
	*/
	static float map(const float value, const Vector2f rang_src, const Vector2f rang_dist);

};


#endif // !UTILITY_H


