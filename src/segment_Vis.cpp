#include "segment_Vis.h"

Segment_Vis::Segment_Vis(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(m_width, m_height);
    Scene* pScene = new Scene();

    if (!pScene) {
        return;
    }

    m_pScene = pScene;

    m_pScene->setSceneRect(0, 0, m_width, m_height);

    QGraphicsView* pView = new QGraphicsView(m_pScene, this);

    if (!pView) {
        delete(m_pScene);
        m_pScene = nullptr;
        return;
    }

    m_pView = pView;

    m_pView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_pView->setGeometry(0, 0, m_width, m_height);
    m_pView->show();

    //Point point1(100, 100);
    //Point point3(600, 100);
    //Point point4(600, 600);
    //Point point5(1500, 400);

    //auto segment = Segment(Point(15, 15), Point(70, 100));

    //m_pScene->addGeometrySegment(segment);

    //m_pScene->addGeometryLine(Line(segment));

    

    Solver solver;

    Segment segment1({ 530, 527 }, { 545, 535 });
    Segment segment2({ 580, 527 }, { 565, 555 });
    Segment segment3({ 595, 515 }, { 600, 515 });
    Segment segment4({ 495, 532 }, { 573, 480 });
   

    auto lines = solver.findAllLines({ segment1, segment4 });
    auto points = solver.findAllPoints(lines);
    DCEL* dcel = solver.solve({ segment1, segment4 });

    for (const auto& line : lines)
    {
        m_pScene->addGeometryLine(line);
    }

    for (const auto& point : points)
    {
        m_pScene->addGeometryPoint(point);
    }

    if (dcel != nullptr)
    {
        m_pScene->addDCEL(dcel);
    }

    m_pScene->addGeometrySegment(segment1);
    //m_pScene->addGeometrySegment(segment2);
    //m_pScene->addGeometrySegment(segment3);
    m_pScene->addGeometrySegment(segment4);

    qreal top = -INFINITY;
    qreal bot = INFINITY;
    qreal right = -INFINITY;
    qreal left = INFINITY;

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

        if (point.y() > top)
        {
            top = point.y();
        }

        if (point.y() < bot)
        {
            bot = point.y();
        }
    }

    /*m_pView->setSceneRect(left, top, right - left, bot - top);*/
    m_pView->scale(2, 2);

    m_pView->update();

    ui.setupUi(this);
}

Segment_Vis::~Segment_Vis()
{
    delete(m_pScene);
    delete(m_pView);
}
