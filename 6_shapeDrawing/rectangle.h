#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"

namespace Shapes
{
    class Rectangle : public Shape
    {
    protected:
        Point LeftBottom, RightTop;

    public:
        Rectangle(int l_x, int l_y, int r_x, int r_y);
        ~Rectangle();

        // ------------------------

        int x() const
        {
            return LeftBottom.x_;
        }
        int y() const
        {
            return LeftBottom.y_;
        }
        int xTo() const
        {
            return RightTop.x_;
        }
        int yTo() const
        {
            return RightTop.y_;
        }
        // ------------------------

        bool isIn(int x_to_check, int y_to_check) const;
    };
}

#endif // RECTANGLE_H