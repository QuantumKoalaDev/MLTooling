#ifndef MLTOOLING_STATUS_H
#define MLTOOLING_STATUS_H

/**
 * @file core.h
 * @brief Defines basic stuff which is used for every api function.
 *
 * General API rules:
 *
 * - All functions return a status code of type `mltStatus`.
 * - Objects returned via `**out` are owned by the caller and must be destroyed with the appropriate destroy function.
 * - Output parameters must not be NULL unless explicitly stated.
 * - On failure, output parameters are left unmodified.
 *
 * All C++ exceptions are caught inside the wrapper and converted to `mltStatus` values.
 * 
 */

#ifdef _WIN32
    #ifdef MLTOOLING_CWRAPPER_EXPORTS
        #define MLTOOLING_CWRAPPER __declspec(dllexport)
    #else
        #define MLTOOLING_CWRAPPER __declspec(dllimport)
    #endif
#else
    #define MLTOOLING_CWRAPPER __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        MLT_STATUS_SUCCESS = 0,
        MLT_STATUS_ERR_NULL_PTR,
        MLT_STATUS_INTERNAL_ERROR,
        MLT_STATUS_ALLOCATION_FAILED,
        MLT_STATUS_ALLOCATION_TOO_LARGE,
        MLT_STATUS_OUT_OF_BOUNDS,
        MLT_STATUS_SHAPE_MISMATCH
    } mltStatus;

#ifdef __cplusplus
}
#endif

#endif
