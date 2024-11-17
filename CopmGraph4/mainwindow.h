#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QGridLayout>
#include <random>
#include <QVector>
#include <QPoint>
#include <QRectF>
#include <QLineF>

#include "CohenSutherland.h"

//typedef for more readable code 
typedef QVector<QLineF> Lines;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void drawVisibleLines();
    void drawAllLines();

private:
    void setupWindow();
    void setupContent();

    QLineF generateLine(const int& minX, const int& maxX, const int& minY, const int& maxY);

private:
    Lines m_lines;

    //prefer use constansts over magic numbers
    const qint16 c_linesCount = 20;

    //points of rectangle (2 points is enough)
    const QPoint c_topLeft = {100, -400};
    const QPoint c_botRight = {500, -200};

    const QRectF c_rect = { c_topLeft, c_botRight };

    //window size
    const int c_width = 800;
    const int c_height = 600;

    //pens
    const QPen c_defaultLinePen{ Qt::blue };
    const QPen c_visibleLinePen{ QColor{ 237, 118, 14 } };
    const QPen c_invisibleLinePen{ Qt::lightGray };

//ui
private:
    QWidget*        m_centralWidget;

    QGridLayout*    m_layout;

    QGraphicsView*  m_view;
    QGraphicsScene* m_scene;

    QPushButton*    m_showAllButton;
    QPushButton*    m_showVisibleButton;
};
#endif // MAINWINDOW_H
