#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QLabel>
#include <QVector>
#include <QGraphicsView>
#include <QDebug>
#include <QGraphicsItem>
#include "Matrix.h"

#define _USE_MATH_DEFINES
#include <math.h>

typedef QVector< QVector<double> > Matrix;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void pointChanged(const int& val);
    void rotate();

private:
    void setupWindow();
    void setWindowContent();

    CMatrix<double> invertY(const CMatrix<double>& m);

    Matrix matrixMultiplication(const Matrix& first, const Matrix& second);

    void redraw();

private:
    CMatrix <double> m_figure;

    QGraphicsItem* m_point;
    QGraphicsItem* m_poligon;

//interface
private:
    QWidget* m_centralWidget;
    QGridLayout* m_layout;

    QGraphicsView* m_view;
    QGraphicsScene* m_scene;

    QLabel* m_xLabel;
    QSpinBox* m_xSpinBox;

    QLabel* m_yLabel;
    QSpinBox* m_ySpinBox;

    QLabel* m_angleLabel;
    QSpinBox* m_angleSpinBox;

    QPushButton* m_redrawButton;
};
#endif // MAINWINDOW_H
