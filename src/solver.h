#pragma once
#include "DCEL.h"

class Solver
{
public:
	DCEL* solve(const std::vector<Segment>& segments);
	std::vector<Line> findAllLines(const std::vector<Segment>& segments);
	std::vector<RationalPoint> findAllPoints(const std::vector<Line>& lines);
	DCEL* initDCEL(const std::vector<RationalPoint>& points);
private:
	std::pair<Point, Point> findEdgeValues(const std::vector<Line>& lines);
};