#pragma once
#include "geometry.h"

class Edge;

struct Vertex
{
	Point m_point;
	Edge* m_indicentEdge;
};

struct Face
{
	Edge* m_indicentEdge;
};

struct Edge
{
	Edge* m_twin;
	Vertex* m_origin;
	Vertex* m_destination;
	Face* m_indicentFace;
	Edge* m_next;
	Edge* m_prev;
};

class DCEL
{
public:
	static DCEL* createFromPoints(const std::vector<Point>& points);

	std::vector<Vertex*> getVertices() const;
	std::vector<Face*> getFaces() const;
	std::vector<Edge*> getEdges() const;

	~DCEL();
private:
	DCEL() {};
	bool init(const std::vector<Point>& points);
private:
	std::vector<Vertex*> m_vertices;
	std::vector<Face*> m_faces;
	std::vector<Edge*> m_edges;
};


