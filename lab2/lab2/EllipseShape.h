
#pragma once
#include "Shape.h"
#include <algorithm>

class EllipseShape : public Shape
{
public:
    EllipseShape(POINT p1, POINT p2)
        : Shape(p1, p2)
    {
    }

    void Draw(HDC hdc) override
    {
        // Перша точка - центр еліпса
        int dx = abs(end.x - start.x);
        int dy = abs(end.y - start.y);

        int left = start.x - dx;
        int top = start.y - dy;
        int right = start.x + dx;
        int bottom = start.y + dy;

        HPEN pen = CreatePen(
            PS_SOLID, 2, RGB(0, 0, 0)
        );

        HBRUSH brush = CreateSolidBrush(
            RGB(255, 255, 255)
        );

        HPEN oldPen = (HPEN)SelectObject(hdc, pen);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

        Ellipse(hdc, left, top, right, bottom);

        SelectObject(hdc, oldPen);
        SelectObject(hdc, oldBrush);

        DeleteObject(pen);
        DeleteObject(brush);
    }
};
