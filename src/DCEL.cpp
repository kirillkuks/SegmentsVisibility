#include "DCEL.h"

DCEL* DCEL::createFromPoints(const std::vector<Point>& points)
{
    DCEL* dcel = new DCEL();

    if (!dcel)
    {
        return nullptr;
    }

    if (!dcel->init(points))
    {
        return nullptr;
    }
    return dcel;
}

std::vector<Vertex*> DCEL::getVertices() const
{
    return m_vertices;
}

std::vector<Face*> DCEL::getFaces() const
{
    return m_faces;
}

std::vector<Edge*> DCEL::getEdges() const
{
    return m_edges;
}

DCEL::~DCEL()
{
    for (auto vert : m_vertices)
    {
        delete vert;
    }

    for (auto face : m_faces)
    {
        delete face;
    }

    for (auto edge : m_edges)
    {
        delete edge;
    }
}

bool DCEL::init(const std::vector<Point>& points)
{
    size_t size = points.size();
    if (size < 3)
    {
        return false;
    }

    m_faces.push_back(new Face());

    for (auto point : points)
    {
        Vertex* vertex = new Vertex();
        vertex->m_point = point;

        m_vertices.push_back(vertex);

        m_edges.push_back(new Edge());
        m_edges.push_back(new Edge());
    }


    m_faces[0]->m_indicentEdge = m_edges[0];

    m_edges[2 * size - 2]->m_destination = m_vertices[0];

    m_edges[2 * size - 2]->m_next = m_edges[0];
    m_edges[1]->m_next = m_edges[2 * size - 1];

    m_edges[0]->m_prev = m_edges[2 * size - 2];
    m_edges[2 * size - 1]->m_prev = m_edges[1];

    m_edges[2 * size - 1]->m_origin = m_vertices[0];

    for (int i = 0; i < size; ++i)
    {
        if (i != 0)
        {
            m_edges[2 * i + 1]->m_next = m_edges[2 * i - 1];
            m_edges[2 * i]->m_prev = m_edges[2 * i - 2];
        }

        if (i != size - 1)
        {
            m_edges[2 * i]->m_destination = m_vertices[i + 1];
            m_edges[2 * i + 1]->m_origin = m_vertices[i + 1];
            m_edges[2 * i]->m_next = m_edges[2 * i + 2];
            m_edges[2 * i + 1]->m_prev = m_edges[2 * i + 3];
        }

        m_edges[2 * i + 1]->m_destination = m_vertices[i];
        m_edges[2 * i]->m_indicentFace = m_faces[0];
        m_edges[2 * i + 1]->m_indicentFace = m_faces[0];
        m_edges[2 * i]->m_origin = m_vertices[i];
        m_edges[2 * i]->m_twin = m_edges[2 * i + 1];
        m_edges[2 * i + 1]->m_twin = m_edges[2 * i];

        m_vertices[i]->m_indicentEdge = m_edges[2 * i];
    }

    return true;
}
