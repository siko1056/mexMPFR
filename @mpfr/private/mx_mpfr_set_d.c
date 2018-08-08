/**
 * Create MPFR variable 'rop' from double array 'x'.
 *
 * Usage:
 *        rop = mx_mpfr_set_d (x, rnd, prec)
 *
 * Input:
 *          'x'  double scalar or array
 *        'rnd'  rounding mode (for 'x')
 *       'prec'  precision (of 'rop')
 *
 * written  16.05.2011     F. Buenger
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
  mpfr_t rop;
  mpfr_rnd_t rnd;
  mpfr_prec_t prec;
  int ternary;
  mwIndex idx,idx_max = 0;
  mwSize ndims,*dims;
  double *pind;
  mx_mpfr_arr pmxa;
  mx_mpfr_ptr pa;

  if (nrhs != 3) {
    mexErrMsgIdAndTxt("MEXMPFR:mx_mpfr_set_d:rhs",
                      "mx_mpfr_set_d: This function requires three inputs.");
  }

  /* Get second input: rounding mode */
  rnd = (mpfr_rnd_t)mxGetScalar(prhs[1]);
  /* Get third  input: precision */
  prec = (mpfr_prec_t)mxGetScalar(prhs[2]);
  if ((prec < MPFR_PREC_MIN) || (prec > MPFR_PREC_MAX)) {
    mexErrMsgIdAndTxt("MEXMPFR:mx_mpfr_set_d:rhs",
                      "mx_mpfr_set_d: precision exceeds allowed interval "
                       "[%u, %u].", MPFR_PREC_MIN, MPFR_PREC_MAX);
  }
  
  /* Initialize output rop with given precision */
  mpfr_init2(rop, prec);

  ndims = mxGetNumberOfDimensions(prhs[0]);
  dims = (mwSize*)mxGetDimensions(prhs[0]);
  mex_mpfr_init(pmxa, pa, ndims, dims);

  /* Convert all double entries to MPFR-format */
  idx_max = (mwIndex)mxGetNumberOfElements(prhs[0]) - 1; /* == prod(dims)-1 */
  pind = mxGetPr(prhs[0]);
  for (idx = 0; idx <= idx_max; ++idx) {
    /* store double value x in rop */
    ternary = mpfr_set_d(rop, (double)(pind[idx]), rnd);
    if (ternary != 0) {
      mexPrintf("mx_mpfr_set_d: Bad return value for x(%d): %d", idx, ternary);
    }
    mpfr_to_mx(pmxa, pa, idx, rop);
  }

  plhs[0] = mxCreateStructMatrix(1, 1, NFIELDS, field_names);
  mex_plhs_set(plhs[0], pmxa, pa);

  mpfr_clear(rop);
}
