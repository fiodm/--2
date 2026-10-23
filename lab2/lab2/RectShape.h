
#pragma once
#include "Shape.h"
#include <algorithm>

class RectShape : public Shape
{
public:
    RectShape(POINT p1, POINT p2)
        : Shape(p1, p2)
    {
    }

    void Draw(HDC hdc) override
    {

        int left = (start.x < end.x) ? start.x : end.x;
        int top = (start.y < end.y) ? start.y : end.y;
        int right = (start.x > end.x) ? start.x : end.x;
        int bottom = (start.y > end.y) ? start.y : end.y;


        HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HBRUSH brush = CreateSolidBrush(RGB(135, 206, 235));

        HPEN oldPen = (HPEN)SelectObject(hdc, pen);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

        Rectangle(hdc, left, top, right, bottom);

        SelectObject(hdc, oldPen);
        SelectObject(hdc, oldBrush);

        DeleteObject(pen);
        DeleteObject(brush);
    }
};
