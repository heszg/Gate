#pragma once

#ifdef _MSC_VER

#define srandom srand
#define random rand

// Copyright 2011 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Extra POSIX/ANSI routines for Win32 when using Visual Studio C++. Please
// refer to The Open Group Base Specification for specification of the correct
// semantics for these functions.
// (http://www.opengroup.org/onlinepubs/000095399/)

//#ifndef V8_BASE_WIN32_MATH_H_
//#define V8_BASE_WIN32_MATH_H_

// MSVC 2013+ provides implementations of all standard math functions.
#if (_MSC_VER < 1800)
enum {
  FP_NAN,
  FP_INFINITE,
  FP_ZERO,
  FP_SUBNORMAL,
  FP_NORMAL
};


namespace std {

int isfinite(double x);
int isinf(double x);
int isnan(double x);
int isless(double x, double y);
int isgreater(double x, double y);
int fpclassify(double x);
int signbit(double x);

}  // namespace std

#endif  // _MSC_VER < 1800


// int strncasecmp(const char* s1, const char* s2, int n);
#	define snprintf _snprintf


#if !defined(__MATH_FUNCTIONS_H__)
/////////////////////////////////////////////////////////////////////////////
#if _MSC_VER < 1800
// MSVC 11 or earlier does not define a C99 compliant math.h header.
// Missing functions are included here for compatibility.
#include <float.h>
#include <math.h>
static __inline double acosh(double x){
    return log(x + sqrt((x * x) - 1.0));
}
static __inline float acoshf(float x){
    return logf(x + sqrtf((x * x) - 1.0f));
}
#   define acoshl(x) acosh(x)
static __inline double asinh(double x){
    return log(x + sqrt((x * x) + 1.0));
}
static __inline float asinhf(float x){
    return logf(x + sqrtf((x * x) + 1.0f));
}
#   define asinhl(x) asinh(x)
static __inline double atanh(double x){
    return (log(1.0 + x) - log(1.0 - x)) / 2;
}
static __inline float atanhf(float x){
    return (logf(1.0f + x) - logf(1.0f - x)) / 2.0f;
}
#define atanhl(x) atanh(x)
static __inline double cbrt(double x){
    return (x > 0.0) ? pow(x, 1.0 / 3.0) : -pow(-x, 1.0 / 3.0);
}
static __inline float cbrtf(float x){
    return (x > 0.0f) ? powf(x, 1.0f / 3.0f) : -powf(-x, 1.0f / 3.0f);
}
#define cbrtl(x) cbrt(x)
#define copysign(x,s) _copysign(x,s)
#define copysignf(x,s) _copysign(x,s)
#define copysignl(x,s) _copysignl(x,s)
static __inline double erf(double x){
    double a1 = 0.254829592, a2 = -0.284496736, a3 = 1.421413741;
    double a4 = -1.453152027, a5 = 1.061405429, p = 0.3275911;
    double t, y;
    int sign = (x >= 0) ? 1 : -1;
    x = fabs(x);
    t = 1.0 / (1.0 + p*x);
    y = 1.0 - (((((a5 * t + a4 ) * t) + a3) * t + a2) * t + a1) * t * exp(-x * x);
    return sign*y;
}
static __inline float erff(float x){
    return erf((float)x);
}
#define erfl(x) erf(x)
// erfc
static __inline double exp2(double x){
    return pow(2.0, x);
}
static __inline float exp2f(float x){
    return powf(2.0f, x);
}
#define exp2l(x) exp2(x)
static __inline double expm1(double x){
    if(fabs(x) < 1e-5)
        return x + 0.5 * x * x;
    else
        return exp(x) - 1.0;
}
static __inline float expm1f(float x){
    if(fabsf(x) < 1e-5f)
        return x + 0.5f * x * x;
    else
        return expf(x) - 1.0f;
}
#define expm1l(x) expm1(x)
static __inline double fdim(double x, double y){
    return (x > y) ? x - y : 0.0;
}
static __inline float fdimf(float x, float y){
    return (x > y) ? x - y : 0.0f;
}
#define fdiml(x,y) fdim(x,y)
static __inline double fma(double x, double y, double z){
    return ((x * y) + z);
}
static __inline float fmaf(float x, float y, float z){
    return ((x * y) + z);
}
#define fmal(x,y,z) fma(x,y,z)
static __inline double fmax(double x, double y){
    return (x > y) ? x : y;
}
static __inline float fmaxf(float x, float y){
    return (x > y) ? x : y;
}
#define fmaxl(x,y) fmax(x,y)
static __inline double fmin(double x, double y){
    return (x < y) ? x : y;
}
static __inline float fminf(float x, float y){
    return (x < y) ? x : y;
}
#define fminl(x,y) fmin(x,y)
#ifndef _HUGE_ENUF
#    define _HUGE_ENUF 1e+300
#endif   
#define INFINITY   ((float)(_HUGE_ENUF * _HUGE_ENUF))  /* causes warning C4756: overflow in constant arithmetic (by design) */
#define NAN        ((float)(INFINITY * 0.0F))
#define FP_INFINITE  1
#define FP_NAN       2
#define FP_NORMAL    (-1)
#define FP_SUBNORMAL (-2)
#define FP_ZERO      0
#define fpclassify(x) ((_fpclass(x)==_FPCLASS_SNAN)?FP_NAN:((_fpclass(x)==_FPCLASS_QNAN)?FP_NAN:((_fpclass(x)==_FPCLASS_QNAN)?FP_NAN: \
 ((_fpclass(x)==_FPCLASS_NINF)?FP_INFINITE:((_fpclass(x)==_FPCLASS_PINF)?FP_INFINITE: \
 ((_fpclass(x)==_FPCLASS_NN)?FP_NORMAL:((_fpclass(x)==_FPCLASS_PN)?FP_NORMAL: \
 ((_fpclass(x)==_FPCLASS_ND)?FP_SUBNORMAL:((_fpclass(x)==_FPCLASS_PD)?FP_SUBNORMAL: \
 FP_ZERO)))))))))
#define hypot(x,y) _hypot(x,y)
#define hypotf(x,y) _hypotf(x,y)
 // ilogb
#define isfinite(x) _finite(x)
//#define isnan(x) (!!_isnan(x))
#define isinf(x) (!_finite(x) && !_isnan(x))
#define isnormal(x) ((_fpclass(x) == _FPCLASS_NN) || (_fpclass(x) == _FPCLASS_PN))
#define isgreater(x,y)      ((x) > (y))
#define isgreaterequal(x,y) ((x) >= (y))
#define isless(x,y)         ((x) < (y))
#define islessequal(x,y)    ((x) <= (y))
#define islessgreater(x,y)  (((x) < (y)) || ((x) > (y)))
#define isunordered(x,y)    (_isnan(x) || _isnan(y))
#define j0(x) _j0(x)
#define j1(x) _j1(x)
#define jn(x,y) _jn(x,y)
// lgamma
static __inline double log1p(double x){
    if(fabs(x) > 1e-4){
        return log(1.0 + x);
    }
    return (-0.5 * x + 1.0) * x;
}
static __inline float log1pf(float x){
    if(fabsf(x) > 1e-4f){
        return logf(1.0f + x);
    }
    return (-0.5f * x + 1.0f) * x;
}
#define log1pl(x) log1p(x)
static __inline double log2(double x) {
    return log(x) * M_LOG2E;
}
static __inline float log2f(float x) {
    return logf(x) * (float)M_LOG2E;
}
#define log2l(x) log2(x)
#define logb(x) _logb(x)
#define logbf(x) _logb(x)
#define logbl(x) _logb(x)
// nearbyint
#define nextafter(x,y) _nextafter(x,y)
#define nextafterf(x,y) _nextafter(x,y)
// nexttoward
static __inline double rint(double x){
    const double two_to_52 = 4.5035996273704960e+15;
    double fa = fabs(x);
    if(fa >= two_to_52){
        return x;
    } else{
        return copysign(two_to_52 + fa - two_to_52, x);
    }
}
static __inline float rintf(float x){
    const double two_to_52 = 4.5035996273704960e+15f;
    double fa = fabsf(x);
    if(fa >= two_to_52){
        return x;
    } else{
        return copysignf(two_to_52 + fa - two_to_52, x);
    }
}
#define rintl(x) rint(x)
static __inline double remainder(double x, double y){
	return (x - ( rint(x / y) * y ));
}

static __inline float remainderf(float x, float y){
	return (x - ( rintf(x / y) * y ));
}


#define remainderl(x) remainder(x)
static __inline double remquo(double x, double y, int* q){
    double d = rint(x / y);
    *q = (int)d;
    return (x - (d * y));
}

static __inline float remquof(float x, float y, int* q){
	float f = rintf(x / y);
	*q = (int)f;
	return (x - (f * y));
}

#define remquo(x) remquo(x)
static __inline double round(double x){
    return ((x > 0.0) ? floor(x + 0.5) : ceil(x - 0.5));
}
static __inline float roundf(float x){
    return ((x > 0.0f) ? floorf(x + 0.5f) : ceilf(x - 0.5f));
}
#define roundl(x) round(x)
// scalbn
#define signbit(x) (_copysign(1.0, x) < 0)
// tgamma
static __inline double trunc(double x){
    return (x > 0.0) ? floor(x) : ceil(x);
}
static __inline float truncf(float x){
    return (x > 0.0f) ? floorf(x) : ceilf(x);
}
#define truncl(x) trunc(x)
#define y0(x) _y0(x)
#define y1(x) _y1(x)
#define yn(x,y) _yn(x,y)
static __inline long lrint(double x){
    return (long)rint(x);
}
static __inline long lrintf(float x){
    return (long)rintf(x);
}
#define lrintl(x) lrint(x)
static __inline long lround(double x){
    return (long)round(x);
}
static __inline long lroundf(float x){
    return (long)roundf(x); 
}
#define lroundl(x) lround(x)
static __inline long long llrint(double x){
    return (long long)rint(x);
}
static __inline long long llrintf(float x){
    return (long long)rintf(x);
}
#define llrintl(x) llrint(x)
static __inline long long llround(double x){
    return (long long)round(x);
}
static __inline long long llroundf(float x){
    return (long long)roundf(x);
}
#define llroundl(x) llround(x)
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// Portable endian

// "License": Public Domain
// I, Mathias Panzenbaeck, place this file hereby into the public domain. Use it at your own risk for whatever you like.
 
#ifndef PORTABLE_ENDIAN_H__
#define PORTABLE_ENDIAN_H__
 
#if (defined(_WIN16) || defined(_WIN32) || defined(_WIN64)) && !defined(__WINDOWS__)
 
#	define __WINDOWS__
 
#endif
 
#if defined(__linux__) || defined(__CYGWIN__)
 
#	include <endian.h>
 
#elif defined(__APPLE__)
 
#	include <libkern/OSByteOrder.h>
 
#	define htobe16(x) OSSwapHostToBigInt16(x)
#	define htole16(x) OSSwapHostToLittleInt16(x)
#	define be16toh(x) OSSwapBigToHostInt16(x)
#	define le16toh(x) OSSwapLittleToHostInt16(x)
 
#	define htobe32(x) OSSwapHostToBigInt32(x)
#	define htole32(x) OSSwapHostToLittleInt32(x)
#	define be32toh(x) OSSwapBigToHostInt32(x)
#	define le32toh(x) OSSwapLittleToHostInt32(x)
 
#	define htobe64(x) OSSwapHostToBigInt64(x)
#	define htole64(x) OSSwapHostToLittleInt64(x)
#	define be64toh(x) OSSwapBigToHostInt64(x)
#	define le64toh(x) OSSwapLittleToHostInt64(x)
 
#	define __BYTE_ORDER    BYTE_ORDER
#	define __BIG_ENDIAN    BIG_ENDIAN
#	define __LITTLE_ENDIAN LITTLE_ENDIAN
#	define __PDP_ENDIAN    PDP_ENDIAN
 
#elif defined(__OpenBSD__)
 
#	include <sys/endian.h>
 
#elif defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__)
 
#	include <sys/endian.h>
 
#	define be16toh(x) betoh16(x)
#	define le16toh(x) letoh16(x)
 
#	define be32toh(x) betoh32(x)
#	define le32toh(x) letoh32(x)
 
#	define be64toh(x) betoh64(x)
#	define le64toh(x) letoh64(x)
 
#elif defined(__WINDOWS__)
 
#	include <winsock2.h>
 
#ifndef LITTLE_ENDIAN
#	define LITTLE_ENDIAN 1
#	define BIG_ENDIAN 2
#	define PDP_ENDIAN 3
#endif
#ifndef BYTE_ORDER
#	define BYTE_ORDER LITTLE_ENDIAN
#endif
#	if BYTE_ORDER == LITTLE_ENDIAN
 
#		define htobe16(x) htons(x)
#		define htole16(x) (x)
#		define be16toh(x) ntohs(x)
#		define le16toh(x) (x)
 
#		define htobe32(x) htonl(x)
#		define htole32(x) (x)
#		define be32toh(x) ntohl(x)
#		define le32toh(x) (x)
 
#		define htobe64(x) htonll(x)
#		define htole64(x) (x)
#		define be64toh(x) ntohll(x)
#		define le64toh(x) (x)
 
#	elif BYTE_ORDER == BIG_ENDIAN
 
		/* that would be xbox 360 */
#		define htobe16(x) (x)
#		define htole16(x) __builtin_bswap16(x)
#		define be16toh(x) (x)
#		define le16toh(x) __builtin_bswap16(x)
 
#		define htobe32(x) (x)
#		define htole32(x) __builtin_bswap32(x)
#		define be32toh(x) (x)
#		define le32toh(x) __builtin_bswap32(x)
 
#		define htobe64(x) (x)
#		define htole64(x) __builtin_bswap64(x)
#		define be64toh(x) (x)
#		define le64toh(x) __builtin_bswap64(x)
 
#	else
 
#		error byte order not supported
 
#	endif
 
#	define __BYTE_ORDER    BYTE_ORDER
#	define __BIG_ENDIAN    BIG_ENDIAN
#	define __LITTLE_ENDIAN LITTLE_ENDIAN
#	define __PDP_ENDIAN    PDP_ENDIAN
 
#else
 
#	error platform not supported
 
#endif
 
#endif
#endif  // _MSC_VER
