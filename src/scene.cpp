#include "scene.h"

void Scene::addGeometryPoint(const Point& point)
{
	m_pen.setColor(m_pointColor);
	m_pen.setStyle(m_pointStyle);
	float r = 1.5;
	addEllipse(point.x() - r, point.y() - r, r * 2.0, r * 2.0, m_pen, QBrush(Qt::SolidPattern));
}

void Scene::addGeometryPoint(const RationalPoint& point)
{
	m_pen.setColor(m_pointColor);
	m_pen.setStyle(m_pointStyle);
	float r = 1.5;
	addEllipse(point.x() - r, point.y() - r, r * 2.0, r * 2.0, m_pen, QBrush(Qt::SolidPattern));
}

void Scene::addGeometrySegment(const Segment& segment)
{
	m_pen.setColor(m_segmentColor);
	m_pen.setStyle(m_segmentStyle);
	addLine(segment.first().x(), segment.first().y(), segment.second().x(), segment.second().y(), m_pen);
	addGeometryPoint(segment.first());
	addGeometryPoint(segment.second());
}

void Scene::addGeometryLine(const Line& line)
{
	m_pen.setColor(m_lineColor);
	m_pen.setStyle(m_lineStyle);
	if (line.isHorizontal())
	{
		qreal value = line.valuebyX(0.0);
		addLine(0.0, value, this->width(), value, m_pen);
		return;
	}

	if (line.isVertical())
	{
		qreal value = line.valuebyY(0.0);
		addLine(value, 0.0, value, this->height(), m_pen);
		return;
	}

	addLine(0.0, line.valuebyX(0.0), this->width(), line.valuebyX(this->width()), m_pen);
	return;
}

void Scene::addDCEL(const DCEL* dcel)
{
	for (auto face : dcel->getFaces())
	{
		QList<QPointF> points;
		Edge* edge = face->m_indicentEdge;
		do
		{
			addGeometryPoint(edge->m_origin->m_point);
			points.append(QPointF(edge->m_origin->m_point.x(), edge->m_origin->m_point.y()));
			edge = edge->m_next;
		} while (edge != face->m_indicentEdge);

		m_pen.setColor(m_lineColor);
		m_pen.setStyle(m_lineStyle);

		addPolygon(points, m_pen);
	}
}
