#include "geometry.h"

int64_t gcd(int64_t a, int64_t b)
{
	if (a <= 0 || b <= 0) {
		return 1;
	}

	int64_t tmpb = b;
	int64_t tmpa = a;
	a = std::min(tmpa, tmpb);
	b = std::max(tmpa, tmpb);
	while (a != b)
	{
		if (a > b)
		{
			int64_t tmp = a;
			a = b;
			b = tmp;
		}
		b = b - a;
	}
	return a;
}

Point& Point::operator+=(const Point& rhs)
{
	m_x += rhs.x();
	m_y += rhs.y();
	return *this;
}

Point& Point::operator-=(const Point& rhs)
{
	m_x -= rhs.x();
	m_y -= rhs.y();
	return *this;
}

Point& Point::operator*=(int64_t rhs)
{
	m_x *= rhs;
	m_y *= rhs;
	return *this;
}

Segment::Segment(Point first, Point second)
	: m_first(first)
	, m_second(second)
{
}

Line::Line(Segment segment)
{
	m_first = segment.first();
	m_second = segment.second();
}

bool Line::isIntersect(const Line& l1, const Line& l2, RationalPoint& intersectionPoint)
{
	if (l1.isVertical())
	{
		return intersectWithVertical(l1, l2, intersectionPoint);
	}

	if (l2.isVertical())
	{
		return intersectWithVertical(l2, l1, intersectionPoint);
	}

	if (l1.isHorizontal())
	{
		return intersectWithHorizontal(l1, l2, intersectionPoint);
	}

	if (l2.isHorizontal())
	{
		return intersectWithHorizontal(l2, l1, intersectionPoint);
	}

	int64_t aFirst = l1.m_second.x() - l1.m_first.x();
	int64_t bFirst = l1.m_second.y() - l1.m_first.y();

	int64_t aSecond = l2.m_second.x() - l2.m_first.x();
	int64_t bSecond = l2.m_second.y() - l2.m_first.y();
	
	int64_t xNum = aFirst * aSecond * (l2.m_first.y() - l1.m_first.y()) + l1.m_first.x() * bFirst * aSecond
		- l2.m_first.x() * bSecond * aFirst;
	int64_t xDenom = aSecond * bFirst - aFirst * bSecond;

	int64_t g = gcd(abs(xNum), abs(xDenom));
	xNum /= g; 
	xDenom /= g;

	int64_t yNum = (xNum - l1.m_first.x() * xDenom) * bFirst + l1.m_first.y() * xDenom * aFirst;
	int64_t yDenom = xDenom * aFirst;

	intersectionPoint = RationalPoint(xNum, xDenom, yNum, yDenom);

	return true;
}

bool Line::isVertical() const
{
	if (m_first.x() == m_second.x())
	{
		return true;
	}
	return false;
}

bool Line::isHorizontal() const
{
	if (m_first.y() == m_second.y())
	{
		return true;
	}
	return false;
}

float Line::valuebyX(float x) const
{
	if (isVertical())
	{
		return 0.0;
	}
	return (x - m_first.x()) / (m_second.x() - m_first.x()) * (m_second.y() - m_first.y()) + m_first.y();
}

float Line::valuebyY(float y) const
{
	if (isHorizontal())
	{
		return 0.0;
	}
	return (y - m_first.y()) / (m_second.y() - m_first.y()) * (m_second.x() - m_first.x()) + m_first.x();
}

bool Line::intersectWithVertical(const Line& lVert, const Line& l, RationalPoint& intersectionPoint)
{
	if (!lVert.isVertical() || l.isVertical()) {
		return false;
	}

	int64_t xNum = lVert.m_first.x();
	int64_t xDenom = 1;

	if (l.isHorizontal())
	{
		intersectionPoint = RationalPoint(xNum, 1, l.m_first.y(), 1);
		return true;
	}

	int64_t tmp = xNum - l.m_first.x();
	int64_t yNum;
	int64_t yDenom;

	if (tmp == 0)
	{
		yNum = l.m_first.y();
		yDenom = 1;
	}
	else
	{
		yNum = tmp * (l.m_second.y() - l.m_first.y()) + l.m_first.y() * (l.m_second.x() - l.m_first.x());
		yDenom = l.m_second.x() - l.m_first.x();
	}

	intersectionPoint = RationalPoint(xNum, xDenom, yNum, yDenom);
	return true;
}

bool Line::intersectWithHorizontal(const Line& lHor, const Line& l, RationalPoint& intersectionPoint)
{
	if (!lHor.isHorizontal() || l.isHorizontal()) {
		return false;
	}

	int64_t yNum = l.m_first.y();
	int64_t yDenom = 1;

	if (l.isVertical())
	{
		intersectionPoint = RationalPoint(l.m_first.x(), 1, yNum, yDenom);
		return true;
	}

	int64_t tmp = yNum - l.m_first.y();
	int64_t xNum;
	int64_t xDenom;

	if (tmp == 0)
	{
		xNum = l.m_first.x();
		xDenom = 1;
	}
	else
	{
		xNum = tmp * (l.m_second.x() - l.m_first.x()) + l.m_first.x() * (l.m_second.y() - l.m_first.y());
		xDenom = l.m_second.y() - l.m_first.y();
	}

	intersectionPoint = RationalPoint(xNum, xDenom, yNum, yDenom);
	return true;
}

Point operator+(const Point& lhs, const Point& rhs)
{
	Point tmp = lhs;
	tmp += rhs;
	return tmp;
}

Point operator-(const Point& lhs, const Point& rhs)
{
	Point tmp = lhs;
	tmp -= rhs;
	return tmp;
}

Point operator*(const Point& lhs, int64_t rhs)
{
	Point tmp = lhs;
	tmp *= rhs;
	return tmp;
}

RationalPoint::RationalPoint(int64_t xNum, int64_t xDenom, int64_t yNum, int64_t yDenom)
	: m_xNum(xNum)
	, m_xDenom(xDenom)
	, m_yNum(yNum)
	, m_yDenom(yDenom)
{
	if (xDenom == 0)
	{
		m_xDenom = 1;
	}
	if (yDenom == 0)
	{
		m_yDenom = 1;
	}

	int64_t sign = 1;
	if (m_xDenom < 0) {
		sign = -1;
	}
	int64_t g = gcd(abs(m_xNum), abs(m_xDenom));
	m_xNum = m_xNum / g * sign;
	m_xDenom = m_xDenom / g * sign;


	sign = 1;
	if (m_yDenom < 0) {
		sign = -1;
	}
	g = gcd(abs(m_yNum), abs(m_yDenom));
	m_yNum = m_yNum / g * sign;
	m_yDenom = m_yDenom / g * sign;
}