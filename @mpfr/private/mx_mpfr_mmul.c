/**
 * MPFR matrix-matrix multiplication.
 *
 * Usage:
 *        c = mx_mpfr_mmul(a, b, rnd)
 *
 * Input:
 *          'a'  MPFR operand
 *          'b'  MPFR operand
 *        'rnd'  rounding mode (for 'c')
 *
 * written  07.11.2011    T.Xu
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
  mpfr_t *op1, *op2, rop, tmp;
  int ternary;
  mpfr_rnd_t rnd;
  mwIndex idx, numel_0, numel_1, idx_a, idx_b, k;
  mwSize ndims, *dims, *dims_a, *dims_b, dimk, dima, dimb;
  mx_mpfr_arr pmxa[3];
  mx_mpfr_ptr pa[3];

  if (nrhs != 3) {
    mexErrMsgIdAndTxt("MEXMPFR:mx_mpfr_mmul:rhs",
                      "mx_mpfr_mmul: Function requires three inputs.");
  }

  /* Get first MPFR operand */
  mex_prhs_get(pmxa[0], pa[0], prhs[0]);
  /* Get second MPFR operand */
  mex_prhs_get(pmxa[1], pa[1], prhs[1]);
  /* Get rounding mode */
  rnd = (mpfr_rnd_t)mxGetScalar(prhs[2]);

  /* TODO: mpfr_inits(op1, op2, rop); segfault? */
  mpfr_init(rop);
  mpfr_init(tmp);

  /* Fet number of elements */
  numel_0 = (mwIndex)mxGetNumberOfElements(pmxa[0][SIGN_NR]);
  numel_1 = (mwIndex)mxGetNumberOfElements(pmxa[1][SIGN_NR]);

  op1 = (mpfr_t*) malloc(numel_0*sizeof(mpfr_t));
  for (idx=0; idx < numel_0; idx ++) {
    mpfr_init(op1[idx]);
    mx_to_mpfr(op1[idx], pa[0], idx);
  }

  op2 = (mpfr_t*) malloc(numel_1*sizeof(mpfr_t));
  for (idx=0; idx < numel_1; idx ++) {
    mpfr_init(op2[idx]);
    mx_to_mpfr(op2[idx], pa[1], idx);
  }

  /* Get dimensions */
  ndims = mxGetNumberOfDimensions(pmxa[0][SIGN_NR]);
  dims_a = (mwSize*)mxGetDimensions(pmxa[0][SIGN_NR]);
  dims_b = (mwSize*)mxGetDimensions(pmxa[1][SIGN_NR]);
  dims   = (mwSize*)mxGetDimensions(pmxa[1][SIGN_NR]);

  dimk = dims_b[0];
  dima = dims_a[1];
  dimb = dims_b[1];
  dims[0] = dima;
  dims[1] = dimb;

  /* Create output array */
  mex_mpfr_init(pmxa[2], pa[2], ndims, dims);
  for (idx_b = 0; idx_b < dimb; idx_b++) {
    for (idx_a = 0; idx_a < dima; idx_a++) {
      mpfr_set_ui(rop, 0, rnd);
      for (k = 0; k < dimk; k++) {
        mpfr_set_prec(tmp, max(mpfr_get_prec(op1[idx_a*dimk+k]),
                               mpfr_get_prec(op2[idx_b*dimk+k])));
        ternary = mpfr_mul(tmp, op1[idx_a * dimk + k],
                           op2[idx_b * dimk + k], rnd);
        if (ternary != 0) {
          mexPrintf("\n mx_mpfr_mmul: mul (b = %d,a = %d,k = %d) = %d\n",
                    idx_b, idx_a, k, ternary);
        }
        ternary = mpfr_add(rop, tmp, rop, rnd);
        if (ternary != 0) {
          mexPrintf("\n mx_mpfr_mmul: add (b = %d,a = %d,k = %d) = %d\n",
                    idx_b, idx_a, k, ternary);
        }
      }
      mpfr_to_mx(pmxa[2], pa[2], idx_b*dima + idx_a, rop);
    }
  }

  plhs[0] = mxCreateStructMatrix(1, 1, NFIELDS, field_names);
  mex_plhs_set(plhs[0], pmxa[2], pa[2]);

  for (idx=0; idx < numel_0; idx ++) {
    mpfr_clear(op1[idx]);
  }
  free(op1);

  for (idx=0; idx < numel_1; idx ++) {
    mpfr_clear(op2[idx]);
  }
  free(op2);

  mpfr_clear(rop);
  mpfr_clear(tmp);
}
