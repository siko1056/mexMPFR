/* mex-file for blocked calling of the MPFR-function
 *
 * int mpfr_add_d (mpfr_t rop, mpfr_t op1, double op2, mpfr_rnd_t rnd)
 *
 * written  30.05.2011     F. Buenger
 */

#include <stdio.h>
#include <math.h>
#include "gmp.h"
#include "mpfr.h"
#include "mex.h"
#include "matrix.h"
#include "mexmpfr.h"

void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[] ) {
  mpfr_t op1, rop;
  int ternary;
  mpfr_rnd_t rnd;
  mwIndex idx, numel_0, numel_1;
  mwSize ndims, *dims;
  mpfr_prec_t prec;
  double *pop2;
  mx_mpfr_arr pmxa[2];
  mx_mpfr_ptr pa[2];

  mex_prhs_get(pmxa[0], pa[0], prhs[0]); /* get pointer array to mpfr array*/
  pop2 = mxGetPr(prhs[1]); /* get pointer to double array */
  rnd = (mpfr_rnd_t)mxGetScalar(prhs[2]);

  mpfr_init(op1);
  mpfr_init(rop);

  /* get number of elements */
  numel_0 = (mwIndex)mxGetNumberOfElements(pmxa[0][SIGN_NR]);
  numel_1 = (mwIndex)mxGetNumberOfElements(prhs[1]);

  if(numel_0 > numel_1) { /* => mumel_1 = 1: */
    ndims = mxGetNumberOfDimensions(pmxa[0][SIGN_NR]);
    dims = (mwSize*)mxGetDimensions(pmxa[0][SIGN_NR]);
    mex_mpfr_init(pmxa[1], pa[1], ndims,
                  dims); /* init pointer array for mpfr output array*/
    for(idx=0; idx<numel_0; ++idx) {
      mx_to_mpfr(op1, pa[0], idx);
      /* prec(rop):=max(prec(op1),prec(op2))*/
      mpfr_set_prec(rop, max(mpfr_get_prec(op1), DOUBLE_PREC));
      ternary = mpfr_add_d(rop, op1, pop2[0], rnd); /* rop:=op1+op2 */
      /*if(ternary!=0) mexPrintf("\n mpfr_add return value = %d \n", ternary);*/
      mpfr_to_mx(pmxa[1], pa[1], idx, rop);
    }
  } else { /* numel_0 <= numel_1 */
    ndims = mxGetNumberOfDimensions(prhs[1]);
    dims = (mwSize*)mxGetDimensions(prhs[1]);
    mex_mpfr_init(pmxa[1], pa[1], ndims,
                  dims); /* init pointer array for mpfr output array*/
    if(numel_0 < numel_1) { /* => mumel_0 = 1: */
      mx_to_mpfr(op1, pa[0], 0); /* get first input parameter */
      prec = mpfr_get_prec(op1);
      for(idx=0; idx<numel_1; ++idx) {
        /* prec(rop):=max(prec(op1),prec(op2))*/
        mpfr_set_prec(rop, max(prec, DOUBLE_PREC));
        ternary = mpfr_add_d(rop, op1, pop2[idx], rnd); /* rop:=op1+op2 */
        /*if(ternary!=0) mexPrintf("\n mpfr_add return value = %d \n", ternary);*/
        mpfr_to_mx(pmxa[1], pa[1], idx, rop);
      }
    } else { /* mumel_0 = numel_1 */
      for(idx=0; idx<numel_1; ++idx) {
        mx_to_mpfr(op1, pa[0], idx); /* get first input parameter */
        /* prec(rop):=max(prec(op1),prec(op2))*/
        mpfr_set_prec(rop, max(mpfr_get_prec(op1), DOUBLE_PREC));
        ternary = mpfr_add_d(rop, op1, pop2[idx], rnd); /* rop:=op1+op2 */
        /*if(ternary!=0) mexPrintf("\n mpfr_add return value = %d \n", ternary);*/
        mpfr_to_mx(pmxa[1], pa[1], idx, rop);
      }
    }
  }
  plhs[0] = mxCreateStructMatrix(1, 1, NFIELDS, field_names);
  mex_plhs_set(plhs[0], pmxa[1], pa[1]);
  mpfr_clear(op1);
  mpfr_clear(rop);
  return;
}
