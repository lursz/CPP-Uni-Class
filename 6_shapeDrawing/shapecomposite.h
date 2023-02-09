#include <memory>
#ifndef SHAPECOMPOSITE_H
#define SHAPECOMPOSITE_H
#include "shape.h"

namespace Shapes
{
    enum class ShapeOperation
    {
        INTERSECTION,
        SUM,
        DIFFERENCE
    };

    class ShapeComposite : public Shape
    {
    protected:
        std::shared_ptr<Shape> shape_1, shape_2;
        ShapeOperation operation;

    public:
        ShapeComposite(std::shared_ptr <Shape> temp_shape_1, std::shared_ptr <Shape> temp_shape_2, ShapeOperation temp_operation);
        ~ShapeComposite();

        // ------------------------

        bool isIn(int x_to_check, int y_to_check) const;
    };
}

#endif // RECTANGLE_H