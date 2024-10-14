#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include "qcustomplot.h"
#include <QGridLayout>
#include "Matrix.h"
#include "CSpline.h"

struct UIpoint
{
    QLabel* m_xLabel = nullptr;
    QLabel* m_yLabel = nullptr;
    QSpinBox* m_xSpinBox = nullptr;
    QSpinBox* m_ySpinBox = nullptr;

    ~UIpoint();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void addPoints();
    void redraw();

private:
    void setupWindow();

private:
    int m_lastRow;//строка с которой можно добавлять 

private://ui elements
    QWidget* m_centraWidget;
    QCustomPlot* m_plot;
    QGridLayout* m_layout;
    QVector<UIpoint*> m_uiPoints;
    QPushButton* m_resetButton;
    QPushButton* m_redrawButton;
    QSpinBox* m_pointCountSpinBox;
    QLabel* m_pointCountLabel;
    QPushButton* m_addPointsButton;

    CMatrix<double> m_matrix;

private://const values
    const int c_minPointCount = 3;
    const int c_maxPointCount = 10;

};
#endif // MAINWINDOW_H
