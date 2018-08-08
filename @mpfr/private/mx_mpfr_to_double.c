/* mex-file for blocked calling of the MPFR-function
 *
 * double mpfr_get_d (mpfr t op, mpfr rnd t rnd)
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

  mex_prhs_get(pmxa[0], pa[0], prhs[0]);
  rnd = (mpfr_rnd_t)mxGetScalar(prhs[1]);

  mpfr_init(op);
  /* get number of elements */
  numel = (mwIndex)mxGetNumberOfElements(pmxa[0][SIGN_NR]);
  /*create output-array*/
  ndims = mxGetNumberOfDimensions(pmxa[0][SIGN_NR]);
  dims = (mwSize*)mxGetDimensions(pmxa[0][SIGN_NR]);
  plhs[0] = mxCreateNumericArray(ndims, dims, mxDOUBLE_CLASS, mxREAL);
  pd = mxGetPr(plhs[0]);

  for(idx=0; idx<numel; ++idx) {
    mx_to_mpfr(op, pa[0], idx);
    pd[idx] = mpfr_get_d(op, rnd); /* x:= double(op)*/
  }
  return;
}
