#include <cmath>
#include "circle.h"
namespace Shapes
{
    Circle::Circle(int temp_x, int temp_y, int temp_r)
        : S(temp_x, temp_y),
          radius(temp_r)
    {
    }

    Circle::~Circle() {}

    // ------------------------

    bool Circle::isIn(int x_to_check, int y_to_check) const
    {

        if ((S.x_ - x_to_check) * (S.x_ - x_to_check) + (S.y_ - y_to_check) * (S.y_ - y_to_check) <= radius * radius)
            return true;
        else
            return false;
    }

}