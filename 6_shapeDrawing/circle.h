#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"

namespace Shapes
{
    class Circle : public Shape
    {
    protected:
        Point S;
        int radius;

    public:
        Circle(int temp_x, int temp_y, int temp_r);
        ~Circle();

        // ------------------------

        int x() const
        {
            return S.x_;
        }
        int y() const
        {
            return S.y_;
        }
        int getRadius() const
        {
            return radius;
        }
        // ------------------------
        bool isIn(int x_to_check, int y_to_check) const;
    };
}

#endif // CIRCLE_H