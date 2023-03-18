#pragma once

#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "ui_Segment_Vis.h"

#include "Scene.h"
#include "Solver.h"

class Segment_Vis : public QMainWindow
{
    Q_OBJECT

public:
    Segment_Vis(QWidget *parent = nullptr);
    ~Segment_Vis();

private:
    static constexpr qreal m_width = 1200.0;
    static constexpr qreal m_height = 800.0;

    Scene* m_pScene = nullptr;
    QGraphicsView* m_pView = nullptr;

    Ui::Segment_VisClass ui;
};
