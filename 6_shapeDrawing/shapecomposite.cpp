#include "shapecomposite.h"
namespace Shapes
{
    ShapeComposite::ShapeComposite(std::shared_ptr<Shape> temp_shape_1, std::shared_ptr<Shape> temp_shape_2, ShapeOperation temp_operation)
        : shape_1(temp_shape_1),
          shape_2(temp_shape_2),
          operation(temp_operation)
    {
    }

    ShapeComposite::~ShapeComposite()
    {
    }

    // ------------------------

    bool ShapeComposite::isIn(int x_to_check, int y_to_check) const
    {
        switch (operation)
            switch (operation)
            {
            case ShapeOperation::INTERSECTION:
                return shape_1->isIn(x_to_check, y_to_check) && shape_2->isIn(x_to_check, y_to_check);
            case ShapeOperation::SUM:
                return shape_1->isIn(x_to_check, y_to_check) || shape_2->isIn(x_to_check, y_to_check);
            case ShapeOperation::DIFFERENCE:
                return shape_1->isIn(x_to_check, y_to_check) && !shape_2->isIn(x_to_check, y_to_check);
            }
    }
}
