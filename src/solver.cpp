#include "solver.h"

DCEL* Solver::solve(const std::vector<Segment>& segments)
{
    std::vector<Line> lines = findAllLines(segments);
	std::vector<RationalPoint> points = findAllPoints(lines);
	return initDCEL(points);
}

std::vector<Line> Solver::findAllLines(const std::vector<Segment>& segments)
{
	auto lines = std::vector<Line>();
	for (int i = 0; i < segments.size(); ++i)
	{
		lines.push_back({ segments[i].first(), segments[i].second() });

		for (int j = i + 1; j < segments.size(); ++j)
		{
			lines.push_back({ segments[i].first(), segments[j].first() });
			lines.push_back({ segments[i].first(), segments[j].second() });
			lines.push_back({ segments[i].second(), segments[j].first() });
			lines.push_back({ segments[i].second(), segments[j].second() });
		}
	}
	return lines;
}

std::vector<RationalPoint> Solver::findAllPoints(const std::vector<Line>& lines)
{
	auto points = std::vector<RationalPoint>();
	
	for (int i = 0; i < lines.size() - 1; ++i)
	{
		for (int j = i + 1; j < lines.size(); ++j)
		{
			RationalPoint rPoint;
			if (Line::isIntersect(lines[i], lines[j], rPoint))
			{
				points.push_back(rPoint);
			}
		}
	}
	return points;
}

DCEL* Solver::initDCEL(const std::vector<RationalPoint>& points)
{
	int64_t diff = 10;
	double top = INFINITY;
	double bot = -INFINITY;
	double right = -INFINITY;
	double left = INFINITY;

	for (const auto& point : points)
	{
		if (point.x() < left)
		{
			left = point.x();
		}

		if (point.x() > right)
		{
			right = point.x();
		}

		if (point.y() < top)
		{
			top = point.y();
		}

		if (point.y() > bot)
		{
			bot = point.y();
		}
	}

	return DCEL::createFromPoints({ 
		{ (int64_t)floor(left) - diff, (int64_t)floor(top) - diff },
		{ (int64_t)ceil(right) + diff, (int64_t)floor(top) - diff },
		{ (int64_t)ceil(right) + diff, (int64_t)ceil(bot) + diff },
		{ (int64_t)floor(left) - diff, (int64_t)ceil(bot) + diff },
	});
}
