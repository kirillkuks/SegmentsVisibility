#pragma once
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

int64_t gcd(int64_t a, int64_t b);

class Point
{
private:
	int64_t m_x;
	int64_t m_y;
public:
	Point(int64_t x = 0, int64_t y = 0) : m_x(x), m_y(y) {};

	inline int64_t x() const { return m_x; };
	inline int64_t y() const { return m_y; };

	Point& operator+=(const Point& rhs);
	friend Point operator+ (const Point& lhs, const Point& rhs);

	Point& operator-=(const Point& rhs);
	friend Point operator- (const Point& lhs, const Point& rhs);

	Point& operator*=(int64_t rhs);
	friend Point operator* (const Point& lhs, int64_t rhs);
};

class RationalPoint
{
private:
	int64_t m_xNum;
	int64_t m_xDenom;
	int64_t m_yNum;
	int64_t m_yDenom;
public:
	RationalPoint(int64_t xNum = 0, int64_t xDenom = 1, int64_t yNum = 0, int64_t yDenom = 1);

	inline float x() const { return (float)m_xNum / m_xDenom; };
	inline float y() const { return (float)m_yNum / m_yDenom; };
};

class Segment 
{
private:
	Point m_first;
	Point m_second;
public:
	Segment(Point first, Point second);

	inline Point first() const { return m_first; };
	inline Point second() const { return m_second; };
};

class Line {
private:
	Point m_first;
	Point m_second;
public:
	Line(Point first, Point second) : m_first(first), m_second(second) {};
	Line(Segment segment);

	static bool isIntersect(const Line& l1, const Line& l2, RationalPoint& intersectionPoint);

	bool isVertical() const;
	bool isHorizontal() const;

	float valuebyX(float x) const;
	float valuebyY(float y) const;

private:
	static bool intersectWithVertical(const Line& lVert, const Line& l, RationalPoint& intersectionPoint);
	static bool intersectWithHorizontal(const Line& lHor, const Line& l, RationalPoint& intersectionPoint);
};