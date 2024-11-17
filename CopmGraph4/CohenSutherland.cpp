#include "CohenSutherland.h"

CohenSutherland::CohenSutherland(const QRectF& rect)
{
    m_top = -rect.top();
    m_bottom = -rect.bottom();
    m_left = rect.left();
    m_right = rect.right();
}

bool CohenSutherland::operator()(const QLineF& f)
{
    ECodes code_1 = getCode(f.p1());
    ECodes code_2 = getCode(f.p2());

    return isInRect(code_1, code_2);
}

ECodes CohenSutherland::getCode(const QPointF& p)
{
    int x = p.x();
    int y = -p.y();

    if (y > m_top)
    {
        if (x < m_left) return ECodes::TOP_LEFT;
        else if (x > m_right)return ECodes::TOP_RIGHT;
        else return ECodes::TOP;
    }

    if (y < m_bottom)
    {
        if (x < m_left) return ECodes::BOTTOM_LEFT;
        else if (x > m_right)return ECodes::BOTTOM_RIGHT;
        else return ECodes::BOTTOM;
    }

    if (x < m_left) return ECodes::LEFT;

    if (x > m_right) return ECodes::RIGHT;

    return ECodes::CENTER;
}

bool CohenSutherland::isInRect(const ECodes& a, const ECodes& b)
{
    return (a & b) > 0 ? true : false;
}
