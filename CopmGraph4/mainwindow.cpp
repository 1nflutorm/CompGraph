#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow{ parent }
{
    setupWindow();
    setupContent();

    connect(m_showAllButton, &QPushButton::clicked, this, &MainWindow::drawAllLines);
    connect(m_showVisibleButton, &QPushButton::clicked, this, &MainWindow::drawVisibleLines);
}

MainWindow::~MainWindow() {}

void MainWindow::drawAllLines()
{
    m_scene->clear();

    m_scene->addRect(c_rect);
    for (const auto& line : m_lines)
    {
        m_scene->addLine(line, c_defaultLinePen);
    }
}

void MainWindow::drawVisibleLines()
{
    m_scene->clear();
    m_scene->addRect(c_rect);

    CohenSutherland cohenSutherland{ c_rect };
    for (const auto& line : m_lines)
    {
        if (!cohenSutherland(line))
        {
            m_scene->addLine(line, c_visibleLinePen);
        }
        else
        {
            m_scene->addLine(line, c_invisibleLinePen);
        }
    }
}

void MainWindow::setupWindow()
{
    m_centralWidget = new QWidget{ this };

    m_centralWidget->setMinimumSize(c_width, c_height);

    m_layout = new QGridLayout{ m_centralWidget };

    m_view = new QGraphicsView{ m_centralWidget };
    m_scene = new QGraphicsScene{ m_view };
    m_view->setScene(m_scene);

    m_showAllButton = new QPushButton{ "Отображать все линии", m_centralWidget };
    m_showVisibleButton = new QPushButton{ "Отображать только видимиые линии", m_centralWidget };

    m_layout->addWidget(m_view, 0, 0, 6, 6);
    m_layout->addWidget(m_showAllButton, 6, 0, 1, 3);
    m_layout->addWidget(m_showVisibleButton, 6, 3, 1, 3);
    m_centralWidget->setLayout(m_layout);

    setCentralWidget(m_centralWidget);
}

void MainWindow::setupContent()
{
    m_scene->addRect(c_rect);

    for (int i = 0; i < c_linesCount; i++)
    {
        QLineF line = generateLine(c_topLeft.x() - 200, c_botRight.x() + 200, -1 * c_botRight.y() - 200, -1 * c_topLeft.y() + 200);
        m_scene->addLine(line, c_defaultLinePen);
        m_lines.push_back(line);
    }
}

QLineF MainWindow::generateLine(const int& minX, const int& maxX, const int& minY, const int& maxY)
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distributionX(minX, maxX);
    std::uniform_int_distribution<> distributionY(minY, maxY);
    int x, y;

    x = distributionX(generator);
    y = distributionX(generator);
    QPoint first{ x, -y };

    x = distributionX(generator);
    y = distributionX(generator);
    QPoint second{ x, -y };

    return QLineF{ first, second };
}
