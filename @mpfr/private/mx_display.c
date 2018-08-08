/**
 * Create human readable string from double variables.
 *
 * char *mpfr_get_str(char *str,mpfr_exp_t *expptr,int b,size_t n,mpfr_t op,mpfr_rnd_t rnd)
 *
 *
 * Usage:
 *        str = mx_display(x, rnd)
 *
 * Input:
 *          'x'  double array
 *        'rnd'  rounding mode (for output)
 *
 * written  19.05.2011     F. Buenger
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
  mpfr_t x;
  mpfr_rnd_t rnd;
  mwIndex idx, idx_max = 1;
  mwSize ndims, *dims;
  char* str = NULL;
  mpfr_exp_t exponent;
  mx_mpfr_arr pmxa;
  mx_mpfr_ptr pa;

  if (nrhs != 2) {
    mexErrMsgIdAndTxt("MEXMPFR:mx_display:rhs",
                      "mx_display: This function requires two inputs.");
  }

  /* Get rounding mode */
  rnd = (mpfr_rnd_t)mxGetScalar(prhs[1]);

  /* Create an output array of the same size as the input array of doubles */
  mex_prhs_get(pmxa, pa, prhs[0]);
  ndims = mxGetNumberOfDimensions(pmxa[PREC_NR]);
  dims = (mwSize*)mxGetDimensions(pmxa[PREC_NR]);
  plhs[0] = mxCreateStructArray(ndims,dims,DISP_NFIELDS,disp_field_names);

  /* Convert all double entries to MPFR-format */
  idx_max = (mwIndex)mxGetNumberOfElements(pmxa[PREC_NR]) - 1;
  mpfr_init(x);
  for(idx = 0; idx <= idx_max; ++idx) {
    mx_to_mpfr(x, pa, idx);
    str = mpfr_get_str(str, &exponent, B_DISP, SIZE_DISP, x, rnd);
    if (str == NULL) {
      mexErrMsgIdAndTxt("MEXMPFR:mx_display:mpfr_get_str",
                        "mx_display: String creation failed for x(%d).", idx);
    }
    mxSetField(plhs[0], idx, MANTISSA_STR, mxCreateString(str));
    mxSetField(plhs[0], idx, EXP_STR, mxCreateDoubleScalar(exponent));
    mpfr_free_str(str);
    str = NULL;
  }
  mpfr_clear(x);
}
