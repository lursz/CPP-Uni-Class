#include "rectangle.h"
namespace Shapes
{
    Rectangle::Rectangle(int left_x, int left_y, int right_x, int right_y)
        : LeftBottom(left_x, left_y),
          RightTop(right_x, right_y)
    {
    }

    Rectangle::~Rectangle() {}

    // ------------------------

    bool Rectangle::isIn(int x_to_check, int y_to_check) const
    {
        if (x_to_check >= LeftBottom.x_ && x_to_check <= RightTop.x_ && y_to_check >= LeftBottom.y_ && y_to_check <= RightTop.y_)
            return true;
        else
            return false;
    }

}