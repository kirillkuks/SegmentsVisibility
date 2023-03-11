#pragma once

struct DSegment;

struct DPoint
{
	int x;
	int y;
	size_t ind;
	DSegment* segment;
};

struct DSegment
{
	DPoint* first;
	DPoint* second;
	bool isCorrect;
};

struct DEdge
{
	DPoint* s_1;
	DPoint* s_2;
};