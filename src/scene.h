#pragma once
#include <qgraphicsscene.h>

#include "DCEL.h"

class Scene : public QGraphicsScene
{
	Q_OBJECT
public:
	void addGeometryPoint(const Point& point);
	void addGeometryPoint(const RationalPoint& point);
	void addGeometrySegment(const Segment& segment);
	void addGeometryLine(const Line& line);
	void addDCEL(const DCEL* dcel);
private:
	QPen m_pen;
	QColor m_segmentColor = QColorConstants::Blue;
	QColor m_pointColor = QColorConstants::Red;
	QColor m_lineColor = QColorConstants::Gray;

	Qt::PenStyle m_segmentStyle = Qt::SolidLine;
	Qt::PenStyle m_pointStyle = Qt::SolidLine;
	Qt::PenStyle m_lineStyle = Qt::DotLine;
};