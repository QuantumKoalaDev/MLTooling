#include <mlt/math/Vector.hpp>

#include <mlt/math/vector.h>
#include <mlt/math/Exceptions.hpp>

#include "mlt/core/core.h"
#include "vectorInternal.hpp"

#include <cstddef>
#include <sys/types.h>

mltStatus mltVectorFCreate(size_t size, mltVectorF** out)
{
    if (!out)
        return MLT_STATUS_ERR_NULL_PTR;
    
    try 
    {
        *out = new mltVectorF(size);
    
    }
    catch (const mlt::math::AllocationFailedException&) 
    {
        return MLT_STATUS_ALLOCATION_FAILED;
    }
    catch(const mlt::math::AllocationTooLargeException&)
    {
        return MLT_STATUS_ALLOCATION_TOO_LARGE;
    }
    catch(...)
    {
        return MLT_STATUS_INTERNAL_ERROR;
    }
    
    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFCreateFromBuff(size_t size, const float *buff, mltVectorF **out)
{
    if (!out || !buff)
        return MLT_STATUS_ERR_NULL_PTR;

    try
    {
        *out = new mltVectorF(std::span<const float>(buff, size));
    }
    catch(const mlt::math::AllocationFailedException&)
    {
        return MLT_STATUS_ALLOCATION_FAILED;
    }
    catch(const mlt::math::AllocationTooLargeException&)
    {
        return MLT_STATUS_ALLOCATION_TOO_LARGE;
    }
    catch(...)
    {
        return MLT_STATUS_INTERNAL_ERROR;
    }

    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFDestroy(mltVectorF *vec)
{
    if (!vec)
        return MLT_STATUS_ERR_NULL_PTR;
    
    delete vec;

    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFSet(mltVectorF *vec, size_t pos, float newVal)
{
    if (!vec)
        return MLT_STATUS_ERR_NULL_PTR;

    try
    {
        vec->implVec[pos] = newVal;
    }
    catch (const mlt::math::OutOfBoundsException&)
    {
        return MLT_STATUS_OUT_OF_BOUNDS;
    }
    catch(...)
    {
        return MLT_STATUS_INTERNAL_ERROR;
    }

    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFGet(const mltVectorF *vec, size_t pos, float *out)
{
    if (!vec || !out)
        return MLT_STATUS_ERR_NULL_PTR;

    try
    {
        float val = vec->implVec[pos];
        *out = val;
    }
    catch(const mlt::math::OutOfBoundsException&)
    {
        return MLT_STATUS_OUT_OF_BOUNDS;
    }
    catch(...)
    {
        return MLT_STATUS_INTERNAL_ERROR;
    }

    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFLength(mltVectorF *vec, size_t *out)
{
    if (!vec || !out)
        return MLT_STATUS_ERR_NULL_PTR;

    *out = vec->implVec.getLen();

    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFIsTransposed(mltVectorF *vec, int *out)
{
    if (!vec || !out)
        return MLT_STATUS_ERR_NULL_PTR;

    bool isTransposed =  vec->implVec.isTransposed();

    if (isTransposed)
        *out = 1;
    else
        *out = 0;

    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFTranspose(mltVectorF *vec)
{
    if (!vec)
        return MLT_STATUS_ERR_NULL_PTR;

    vec->implVec.transpose();


    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFAdd(const mltVectorF *a, const mltVectorF *b, mltVectorF **out)
{
    if (!out || !a || !b)
        return MLT_STATUS_ERR_NULL_PTR;

    try
    {
        mlt::math::datastructures::Vector<float> c = a->implVec.add(b->implVec);
        *out = new mltVectorF(std::move(c));
    }
    catch(const mlt::math::AllocationFailedException&)
    {
        return MLT_STATUS_ALLOCATION_FAILED;
    }
    catch(const mlt::math::AllocationTooLargeException&)
    {
        return MLT_STATUS_ALLOCATION_TOO_LARGE;
    }
    catch(const mlt::math::ShapeMismatchException&)
    {
        return MLT_STATUS_SHAPE_MISMATCH;
    }
    catch(...)
    {
        return MLT_STATUS_INTERNAL_ERROR;
    }

    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFAddInPlace(mltVectorF *a, const mltVectorF *b)
{
    if (!a || !b)
        return MLT_STATUS_ERR_NULL_PTR;

    try 
    {
        a->implVec.addInPlace(b->implVec);
    }
    catch (const mlt::math::ShapeMismatchException&) 
    {
        return MLT_STATUS_SHAPE_MISMATCH;
    }
    catch (...)
    {
        return MLT_STATUS_INTERNAL_ERROR;
    }

    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFSubtract(const mltVectorF *a, const mltVectorF *b, mltVectorF **out)
{
    if (!a || !b || !out)
        return MLT_STATUS_ERR_NULL_PTR;
    
    try
    {
        mlt::math::datastructures::Vector<float> c = a->implVec.subtract(b->implVec);
        *out = new mltVectorF(std::move(c));
    }
    catch (const mlt::math::AllocationFailedException&)
    {
        return MLT_STATUS_ALLOCATION_FAILED;
    }
    catch (const mlt::math::AllocationTooLargeException&)
    {
        return MLT_STATUS_ALLOCATION_TOO_LARGE;
    }
    catch (const mlt::math::ShapeMismatchException&)
    {
        return MLT_STATUS_SHAPE_MISMATCH;
    }
    catch (...)
    {
        return MLT_STATUS_INTERNAL_ERROR;
    }

    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFSubtractInPlace(mltVectorF *a, const mltVectorF *b)
{
    if (!a || !b)
        return MLT_STATUS_ERR_NULL_PTR;
    
    try
    {
        a->implVec.subtractInPlace(b->implVec);
    }
    catch(const mlt::math::ShapeMismatchException&)
    {
        return MLT_STATUS_SHAPE_MISMATCH;
    }
    catch (...)
    {
        return MLT_STATUS_INTERNAL_ERROR;
    }

    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFMulScalar(const mltVectorF *vec, float scalar, mltVectorF** out)
{
    if (!vec || !out)
        return MLT_STATUS_ERR_NULL_PTR;

    try
    {
        mlt::math::datastructures::Vector<float> b = vec->implVec.mulScalar(scalar);
        *out = new mltVectorF(std::move(b));
    }
    catch (const mlt::math::AllocationFailedException&)
    {
        return MLT_STATUS_ALLOCATION_FAILED;
    }
    catch (const mlt::math::AllocationTooLargeException&)
    {
        return MLT_STATUS_ALLOCATION_TOO_LARGE;
    }
    catch (...)
    {
        return MLT_STATUS_INTERNAL_ERROR;
    }

    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFMulScalarInPlace(mltVectorF *vec, float scalar)
{
    if (!vec)
        return MLT_STATUS_ERR_NULL_PTR;
    
    try
    {
        vec->implVec.mulScalarInPlace(scalar);
    }
    catch (...)
    {
        return MLT_STATUS_INTERNAL_ERROR;
    }
 
    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFDot(const mltVectorF *a, const mltVectorF* b, float* out)
{
    if (!a || !b || !out)
        return MLT_STATUS_ERR_NULL_PTR;

    try
    {
        *out = a->implVec.dot(b->implVec);
    }
    catch (const mlt::math::ShapeMismatchException&)
    {
        return MLT_STATUS_SHAPE_MISMATCH;
    }
    catch (...)
    {
        return MLT_STATUS_INTERNAL_ERROR;
    }

    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFHadamard(const mltVectorF *a, const mltVectorF *b, mltVectorF **out)
{
    if (!a || !b || !out)
        return MLT_STATUS_ERR_NULL_PTR;
    
    try
    {
        mlt::math::datastructures::Vector<float> c = a->implVec.hadamard(b->implVec);
        *out = new mltVectorF(std::move(c));
    }
    catch (const mlt::math::AllocationFailedException&)
    {
        return MLT_STATUS_ALLOCATION_FAILED;
    }
    catch (const mlt::math::ShapeMismatchException&)
    {
        return MLT_STATUS_SHAPE_MISMATCH;
    }
    catch (...)
    {
        return MLT_STATUS_INTERNAL_ERROR;
    }

    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFCopy(const mltVectorF *vec, mltVectorF **out)
{
    if (!vec || !out)
        return MLT_STATUS_ERR_NULL_PTR;
    
    try
    {
        mlt::math::datastructures::Vector<float> copyVec = mlt::math::datastructures::Vector(vec->implVec);
        *out = new mltVectorF(std::move(copyVec));
    }
    catch (const mlt::math::AllocationFailedException&)
    {
        return MLT_STATUS_ALLOCATION_FAILED;
    }
    catch (const mlt::math::AllocationTooLargeException&)
    {
        return MLT_STATUS_ALLOCATION_TOO_LARGE;
    }
    catch (...)
    {
        return MLT_STATUS_INTERNAL_ERROR;
    }

    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFClone(const mltVectorF *vec, mltVectorF **out)
{
    if (!vec || !out)
        return MLT_STATUS_ERR_NULL_PTR;
    
    try
    {
        mlt::math::datastructures::Vector<float> cloneVec = vec->implVec.clone();
        *out = new mltVectorF(std::move(cloneVec));
    }
    catch (const mlt::math::AllocationFailedException&)
    {
        return MLT_STATUS_ALLOCATION_FAILED;
    }
    catch (const mlt::math::AllocationTooLargeException&)
    {
        return MLT_STATUS_ALLOCATION_TOO_LARGE;
    }
    catch (...)
    {
        return MLT_STATUS_INTERNAL_ERROR;
    }
    
    return MLT_STATUS_SUCCESS;
}

mltStatus mltVectorFSubvector(const mltVectorF *vec, size_t pos, size_t length, mltVectorF **out)
{
    if (!vec || !out)
        return MLT_STATUS_ERR_NULL_PTR;
    
    try
    {
        mlt::math::datastructures::Vector<float> subvec = vec->implVec.subvector(pos, length);
        *out = new mltVectorF(std::move(subvec));
    }
    catch (const mlt::math::OutOfBoundsException&)
    {
        return MLT_STATUS_OUT_OF_BOUNDS;
    }
    catch (...)
    {
        return MLT_STATUS_INTERNAL_ERROR;
    }
    
    return MLT_STATUS_SUCCESS;
}
