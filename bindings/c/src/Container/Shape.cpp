#include "Container/Shape.h"
#include "Container/Shape.hpp"

#ifdef __cplusplus
extern "C" {
#endif

struct Shape {
	Container::Shape impl;
};

MLTOOLING_CAPI Shape* ct_shape_create(unsigned long rows, unsigned long cols) {
	return new Shape(Container::Shape(rows, cols));
}

MLTOOLING_CAPI void ct_shape_destroy(Shape* shape) {
	delete shape;
}
MLTOOLING_CAPI unsigned long ct_shape_getRows(Shape* shape) {
	return shape->impl.rows;
}

MLTOOLING_CAPI unsigned long ct_shape_getCols(Shape* shape) {
	return shape->impl.cols;
}

#ifdef __cplusplus
}
#endif