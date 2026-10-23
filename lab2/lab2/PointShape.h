
#pragma once
#include "Shape.h"

class PointShape : public Shape
{
public:
    PointShape(POINT p)
        : Shape(p, p)
    {
    }

    void Draw(HDC hdc) override
    {
        HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));

        RECT r = {
            start.x - 3,
            start.y - 3,
            start.x + 4,
            start.y + 4
        };

        FillRect(hdc, &r, brush);
        DeleteObject(brush);
    }
};
