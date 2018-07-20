/* s_asinhf.c -- float version of s_asinh.c.
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

#include "gmath.h"
#include "math_private.h"

static const float
one =  1.0000000000e+00f, /* 0x3F800000 */
ln2 =  6.9314718246e-01f, /* 0x3f317218 */
huge=  1.0000000000e+30f;

float
gm_asinhf(float x)
{
	float t,w;
	int32_t hx,ix;
	GET_FLOAT_WORD(hx,x);
	ix = hx&0x7fffffff;
	if(ix>=0x7f800000) return x+x;	/* x is inf or NaN */
	if(ix< 0x31800000) {	/* |x|<2**-28 */
	    if(huge+x>one) return x;	/* return x inexact except 0 */
	}
	if(ix>0x4d800000) {	/* |x| > 2**28 */
	    w = __ieee754_logf(gm_fabsf(x))+ln2;
	} else if (ix>0x40000000) {	/* 2**28 > |x| > 2.0 */
	    t = gm_fabsf(x);
	    w = __ieee754_logf((float)2.0*t+one/(__ieee754_sqrtf(x*x+one)+t));
	} else {		/* 2.0 > |x| > 2**-28 */
	    t = x*x;
	    w =gm_log1pf(gm_fabsf(x)+t/(one+__ieee754_sqrtf(one+t)));
	}
	if(hx>0) return w; else return -w;
}
