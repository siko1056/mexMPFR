/**
 * Implementation of the mexMPFR interface.
 *
 * written  19.05.2011     F. Buenger
 */

#include <stdio.h>
#include <stdarg.h>

#include <math.h>
#include "gmp.h"
#include "mpfr.h"
#include "mex.h"
#include "mexmpfr.h"
#include "matrix.h"

const char *field_names[] = {PREC_STR, SIGN_STR, EXP_STR, D_END_STR, D_STR};
const char *disp_field_names[] = {MANTISSA_STR, EXP_STR};

/*  */

/**
 * Convert a MATLAB mxArray to MPFR mpfr_t
 *
 * The definition of the main MPFR-structure (a.k.a mpfr_t) is
 *
 * typedef struct {
 *   mpfr_prec_t  _mpfr_prec;
 *   mpfr_sign_t  _mpfr_sign;
 *   mpfr_exp_t   _mpfr_exp;
 *   mp_limb_t   *_mpfr_d;
 * } __mpfr_struct;
 *
 * The represented number is
 *
 *    _sign * (_d[k-1]/B + _d[k-2]/B^2 + ... +_d[0]/B^k) * 2^_exp
 *
 * where `k = ceil(_mp_prec/GMP_NUMB_BITS)` and `B = 2^GMP_NUMB_BITS`.
 *
 * For the msb (most significant bit) normalized representation, we must have
 * `_d[k-1] >= B/2`, unless the number is singular.
 *
 * We must also have the last `k*GMP_NUMB_BITS - _prec bits` set to zero.
 *
 * In Matlab a number of this format is stored in a structure of class
 * mpfr_t with the following components:
 *
 *   .prec        : Precision (int)
 *   .sign        : Sign      (int)
 *   .exp         : Exponent  (int)
 *   .d_begin     : begin index of limb array  (int)
 *   .d_end       : end index of limb array  (int)
 *   .d           : significands  (Array of limbs/int)
 */

void mx_to_mpfr(mpfr_t x, mx_mpfr_ptr pa, int idx) {
  int i, i_max;
  /* set precision */
  mpfr_set_prec(x, (mpfr_prec_t)pa[PREC_NR][idx]);
  /*
   * Before we set bits, we first make a clean MPFR initialization with "1.0".
   * Otherwise the hacks below will not work!
   */
  mpfr_set_d(x, 1.0, MPFR_RNDN);
  /* set sign, rounding mode MPFR_RNDN is irrelevant */
  mpfr_setsign(x, x, (mpfr_sign_t)pa[SIGN_NR][idx], MPFR_RNDN);
  /* set exponent */
  mpfr_set_exp(x, (mpfr_exp_t)pa[EXP_NR][idx]);
  /*
   * Dirty direct setting of limbs since there is no standard mpfr-function
   * for doing this.
   */
  /* i_max is the length of the limb array -1 */
  i_max = (int)(pa[D_END_NR][idx]) - d_end_pred(pa, idx) - 1;
  for (i = 0; i <= i_max; ++i) {
    (x->_mpfr_d)[i] = (mp_limb_t)pa[D_NR][((int)pa[D_END_NR][idx])-i_max+i];
    /*mexPrintf("\n (x->_mpfr_d)[%d] = %d \n", i, (x->_mpfr_d)[i]);*/
  }
}


/**
 * Inverse operation of mx_to_mpfr.
 */

void mpfr_to_mx(mx_mpfr_arr pmxa, mx_mpfr_ptr pa, int idx, mpfr_t x) {

  mpfr_prec_t prec;
  int i, k, d_end_pre;

  prec = mpfr_get_prec(x);
  /* number of limbs */
  k = ceil(((double)prec) / GMP_NUMB_BITS);

  pa[PREC_NR][idx] = (double)prec;
  pa[SIGN_NR][idx] = (double)mpfr_signbit(x);
  pa[EXP_NR][idx]  = (double)mpfr_get_exp(x);
  d_end_pre = d_end_pred(pa, idx);
  pa[D_END_NR][idx] = (double)(d_end_pre + k);

  if ((pa[D_END_NR][idx] + 1) > mxGetNumberOfElements(pmxa[D_NR])) {
    /* allocate additional memory for new limb array */
    pa[D_NR] = (double*)mxRealloc(pa[D_NR],
                                  (pa[D_END_NR][idx] + 1) * sizeof(double));
    mxSetPr(pmxa[D_NR], pa[D_NR]);
  }
  for (i = 0; i < k; ++i) {
    pa[D_NR][d_end_pre + 1 + i] = (double)((x->_mpfr_d)[i]);
  }
}

void mex_mpfr_init(mx_mpfr_arr pmxa, mx_mpfr_ptr pa,
                   mwSize ndim, const mwSize *dims) {
  int nlimbs;
  mpfr_prec_t default_prec;

  pmxa[PREC_NR]  = mxCreateNumericArray(ndim, dims, mxDOUBLE_CLASS, mxREAL);
  pmxa[SIGN_NR]  = mxCreateNumericArray(ndim, dims, mxDOUBLE_CLASS, mxREAL);
  pmxa[EXP_NR]   = mxCreateNumericArray(ndim, dims, mxDOUBLE_CLASS, mxREAL);
  pmxa[D_END_NR] = mxCreateNumericArray(ndim, dims, mxDOUBLE_CLASS, mxREAL);

  default_prec = mpfr_get_default_prec();
  /* default number of limbs times the number of elements */
  nlimbs = ceil(((double) default_prec) / GMP_NUMB_BITS)
           * mxGetNumberOfElements(pmxa[PREC_NR]);
  pmxa[D_NR]   = mxCreateDoubleMatrix(1, nlimbs, mxREAL);
  pa[PREC_NR]  = mxGetPr(pmxa[PREC_NR]);
  pa[SIGN_NR]  = mxGetPr(pmxa[SIGN_NR]);
  pa[EXP_NR]   = mxGetPr(pmxa[EXP_NR]);
  pa[D_END_NR] = mxGetPr(pmxa[D_END_NR]);
  pa[D_NR]     = mxGetPr(pmxa[D_NR]);;
}


/*
 * Initialize mx_mpfr output structure.
 */

void mex_plhs_set(mxArray* pl, mx_mpfr_arr pmxa, mx_mpfr_ptr pa) {
  unsigned long int nel, nlimbs;
  nel = mxGetNumberOfElements(pmxa[D_END_NR]);
  /* total number of limbs */
  nlimbs = pa[D_END_NR][nel-1] + 1;
  if (nlimbs < mxGetNumberOfElements(pmxa[D_NR])) {
    /* shrink memory for limb array to the needed amount */
    pa[D_NR] = (double*)mxRealloc(pa[D_NR], nlimbs * sizeof(double));
    mxSetPr(pmxa[D_NR], pa[D_NR]);
  }
  mxSetField(pl, 0, PREC_STR,  pmxa[PREC_NR]);
  mxSetField(pl, 0, SIGN_STR,  pmxa[SIGN_NR]);
  mxSetField(pl, 0, EXP_STR,   pmxa[EXP_NR]);
  mxSetField(pl, 0, D_END_STR, pmxa[D_END_NR]);
  mxSetField(pl, 0, D_STR,     pmxa[D_NR]);
}


/*
 * Initialize mx_mpfr input structure.
 */

void mex_prhs_get(mx_mpfr_arr pmxa, mx_mpfr_ptr pa, const mxArray* pr) {
  pmxa[PREC_NR]  = mxGetField(pr, 0, PREC_STR);
  pmxa[SIGN_NR]  = mxGetField(pr, 0, SIGN_STR);
  pmxa[EXP_NR]   = mxGetField(pr, 0, EXP_STR);
  pmxa[D_END_NR] = mxGetField(pr, 0, D_END_STR);
  pmxa[D_NR]     = mxGetField(pr, 0, D_STR);

  pa[PREC_NR]  = mxGetPr(pmxa[PREC_NR]);
  pa[SIGN_NR]  = mxGetPr(pmxa[SIGN_NR]);
  pa[EXP_NR]   = mxGetPr(pmxa[EXP_NR]);
  pa[D_END_NR] = mxGetPr(pmxa[D_END_NR]);
  pa[D_NR]     = mxGetPr(pmxa[D_NR]);
}


/*
 * Computes the end index of the preceeding limb array.
 *
 * For `idx <= 0* the function returns "-1".
 */
int d_end_pred(mx_mpfr_ptr pa, int idx) {
  return (idx <= 0) ? -1 : pa[D_END_NR][(idx) - 1];
}

