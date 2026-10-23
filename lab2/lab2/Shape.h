
#pragma once
#include <windows.h>

class Shape
{
protected:
    POINT start;
    POINT end;

public:
    Shape(POINT p1, POINT p2)
        : start(p1), end(p2)
    {
    }

    virtual ~Shape() = default;

    virtual void Draw(HDC hdc) = 0;
};
