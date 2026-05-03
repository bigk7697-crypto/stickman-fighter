#ifndef __khrplatform_h_
#define __khrplatform_h_

/*
** Copyright (c) 2008-2018 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

/* Khronos platform-specific types and definitions.
 *
 * The master copy of khrplatform.h is maintained in the Khronos EGL
 * Registry repository at https://github.com/KhronosGroup/EGL-Registry
 * The last semantic modification to khrplatform.h was at commit ID:
 *      67a3e0864c2d75ea5287b9f3d2eb74a745936693
 *
 * Adopters may modify this file to suit their platform. Adopters are
 * encouraged to submit platform specific modifications to the Khronos
 * group so that they can be included in future versions of this file.
 * Please submit changes by filing pull requests or issues on
 * the EGL Registry repository linked above.
 *
 *
 * See the Implementer's Guidelines for information about where this file
 * should be headed on specific systems:
 *    http://www.khronos.org/registry/implementers_guide.pdf
 *
 * This file should be included as
 *        #include <KHR/khrplatform.h>
 * by Khronos client API header files that use its interfaces and types.
 *
 * Do not #include this file directly: instead #include the target API's headers.
 */

#if defined(_WIN32)
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN 1
#   endif
#   include <windows.h>
#endif

#if defined(__ANDROID__) && defined(__ANDROID_API__)
#   include <android/api-level.h>
#endif

/*
 * Detect whether the compiler has C99's stdint.h header.
 */
#if defined(__STDC__)
#   if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#       define KHRONOS_USE_STDINT_H 1
#   elif defined(__GNUC__) && (__GNUC__ >= 3)
#       define KHRONOS_USE_STDINT_H 1
#   elif defined(_MSC_VER) && (_MSC_VER >= 1600)
#       define KHRONOS_USE_STDINT_H 1
#   endif
#endif

#if defined(KHRONOS_USE_STDINT_H)
#   include <stdint.h>
    typedef int32_t                 khronos_int32_t;
    typedef uint32_t                khronos_uint32_t;
    typedef int64_t                 khronos_int64_t;
    typedef uint64_t                khronos_uint64_t;
#else
    typedef signed   int            khronos_int32_t;
    typedef unsigned int            khronos_uint32_t;
    typedef long long               khronos_int64_t;
    typedef unsigned long long      khronos_uint64_t;
#endif

typedef signed   char          khronos_int8_t;
typedef unsigned char          khronos_uint8_t;
typedef signed   short int     khronos_int16_t;
typedef unsigned short int     khronos_uint16_t;

/*
 * Types that differ between LLP64 and LP64 architectures
 */
#if defined(_WIN64)
    typedef signed   long long int khronos_intptr_t;
    typedef unsigned long long int khronos_uintptr_t;
    typedef signed   long long int khronos_ssize_t;
    typedef unsigned long long int khronos_usize_t;
#else
    typedef signed   long  int     khronos_intptr_t;
    typedef unsigned long  int     khronos_uintptr_t;
    typedef signed   long  int     khronos_ssize_t;
    typedef unsigned long  int     khronos_usize_t;
#endif

#if KHRONOS_SUPPORT_FLOAT
    typedef          float         khronos_float_t;
#endif

#if KHRONOS_SUPPORT_INT64
    typedef khronos_uint64_t       khronos_utime_nanoseconds_t;
    typedef khronos_int64_t        khronos_stime_nanoseconds_t;
#endif

/*
 * Types that are (so far) the same on all platforms
 */
typedef khronos_uint64_t       khronos_uint64_t;
typedef khronos_int64_t        khronos_int64_t;

/*
 * Time value.  All time values are in nanoseconds.
 */
typedef khronos_int64_t khronos_time_nanoseconds_t;

/*
 * Boolean type.  Values are KHRONOS_TRUE and KHRONOS_FALSE.
 */
typedef enum {
    KHRONOS_FALSE = 0,
    KHRONOS_TRUE  = 1,
    KHRONOS_BOOLEAN_ENUM_FORCE_SIZE = KHRONOS_MAX_ENUM
} khronos_boolean_enum_t;

/*
 * Dummy value used to pad enum types to 32 bits.
 */
#ifndef KHRONOS_MAX_ENUM
#define KHRONOS_MAX_ENUM 0x7FFFFFFF
#endif

#ifndef KHRONOS_ATTRIBUTE_FORMAT
#   if defined(__GNUC__) && (__GNUC__ >= 4)
#       define KHRONOS_ATTRIBUTE_FORMAT(pos) __attribute__((format(printf, pos, pos + 1)))
#   else
#       define KHRONOS_ATTRIBUTE_FORMAT(pos)
#   endif
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/*
 * Types of fences and surfaces.
 */
typedef void*               EGLSync;
typedef intptr_t            EGLAttrib;
typedef khronos_utime_nanoseconds_t EGLTime;
typedef void*               EGLImage;

/* EGLSync typedefs */
typedef khronos_utime_nanoseconds_t EGLTimeKHR;
typedef void*               EGLSyncKHR;
typedef void*               EGLImageKHR;

/* EGLImage typedefs */
typedef void*               EGLImageOES;

#if defined(__cplusplus)
}
#endif

/*
 * Cleanup
 */
#undef KHRONOS_USE_STDINT_H

#endif /* __khrplatform_h_ */
