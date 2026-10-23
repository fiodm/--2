
#pragma once
#include "Shape.h"

class LineShape : public Shape
{
public:
    LineShape(POINT p1, POINT p2)
        : Shape(p1, p2)
    {
    }

    void Draw(HDC hdc) override
    {
        HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HPEN oldPen = (HPEN)SelectObject(hdc, pen);

        MoveToEx(hdc, start.x, start.y, nullptr);
        LineTo(hdc, end.x, end.y);

        SelectObject(hdc, oldPen);
        DeleteObject(pen);
    }
};
