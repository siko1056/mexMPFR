/**
 * Convert MPFR matrix to double matrix.
 *
 * Usage:
 *        c = mx_mpfr_to_double(a, rnd)
 *
 * Input:
 *          'a'  MPFR operand
 *        'rnd'  rounding mode (for 'c')
 *
 * written  10.06.2011     F. Buenger
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
  mpfr_t op;
  mpfr_rnd_t rnd;
  mwIndex idx, numel;
  mwSize ndims, *dims;
  mx_mpfr_arr pmxa[1];
  mx_mpfr_ptr pa[1];
  double *pd;

  if (nrhs != 2) {
    mexErrMsgIdAndTxt("MEXMPFR:mx_mpfr_to_double:rhs",
                      "mx_mpfr_to_double: Function requires two inputs.");
  }

  mex_prhs_get(pmxa[0], pa[0], prhs[0]);
  rnd = (mpfr_rnd_t)mxGetScalar(prhs[1]);

  mpfr_init(op);

  /* Get number of elements */
  numel = (mwIndex)mxGetNumberOfElements(pmxa[0][SIGN_NR]);

  /* Create output array */
  ndims = mxGetNumberOfDimensions(pmxa[0][SIGN_NR]);
  dims = (mwSize*)mxGetDimensions(pmxa[0][SIGN_NR]);
  plhs[0] = mxCreateNumericArray(ndims, dims, mxDOUBLE_CLASS, mxREAL);
  pd = mxGetPr(plhs[0]);

  for (idx = 0; idx < numel; ++idx) {
    mx_to_mpfr(op, pa[0], idx);
    pd[idx] = mpfr_get_d(op, rnd);
  }
}
