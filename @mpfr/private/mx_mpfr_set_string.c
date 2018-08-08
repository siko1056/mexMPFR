/**
 * Create MPFR variable 'rop' initialized with string values given in 'cstr'.
 *
 * Usage:
 *        rop = mx_mpfr_set_str (cstr, base, rnd, prec)
 *
 * Input:
 *       'cstr'  cell array of strings
 *       'base'  base of the string values
 *        'rnd'  rounding mode (of 'rop')
 *       'prec'  precision (of 'rop')
 *
 * written  19.05.2011     F. Buenger
 *
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
  int base, ternary;
  mpfr_rnd_t rnd;
  mpfr_prec_t prec;
  char *str = NULL;
  mwSize strlen;
  mwIndex idx,idx_max = 0;
  mwSize ndims,*dims;
  mxArray *pidx;
  mx_mpfr_arr pmxa;
  mx_mpfr_ptr pa;

  if (nrhs != 4) {
    mexErrMsgIdAndTxt("MEXMPFR:mx_mpfr_set_str:rhs",
                      "mx_mpfr_set_str: This function requires four inputs.");
  }

  /* Get second input: base */
  base = (int)mxGetScalar(prhs[1]);
  /* Get third  input: rounding mode */
  rnd = (mpfr_rnd_t)mxGetScalar(prhs[2]);
  /* Get fourth input: precision */
  prec = (mpfr_prec_t)mxGetScalar(prhs[3]);

  /* initialize rop with given precision */
  mpfr_init2(rop, prec);

  /* create a CellArray for output that has the same size like the input-Array
     prhs[0] of doubles which shall be converted to multiple precision format mpfr_t */
  ndims = mxGetNumberOfDimensions(prhs[0]);
  dims = (mwSize*)mxGetDimensions(prhs[0]);
  mex_mpfr_init(pmxa, pa, ndims, dims);

  /* Convert all string entries inside the cell array to MPFR-format */
  idx_max = (mwIndex)mxGetNumberOfElements(prhs[0]) - 1;
  for (idx = 0; idx <= idx_max; ++idx) {
    pidx = mxGetCell(prhs[0],idx);
    strlen = mxGetN(pidx) * sizeof(mxChar) + 1;
    str = (char*) mxMalloc(strlen);
    if (str == NULL) {
      mexErrMsgIdAndTxt("MEXMPFR:mx_mpfr_set_str:mxMalloc",
                        "mx_mpfr_set_str: cstr(%d) mxMalloc failed.",
                        idx);
    }
    /* Copy the string data into buffer 'str'. */
    ternary = mxGetString (pidx, str, strlen);
    if (ternary != 0) {
      mexErrMsgIdAndTxt("MEXMPFR:mx_mpfr_set_str:mxGetString",
                        "mx_mpfr_set_str: cstr(%d) mxGetString failed.",
                        idx);
    }
    /* Convert numeric string to MPFR-format */
    ternary = mpfr_set_str(rop, str, base, rnd);
    if (ternary != 0) {
      mexErrMsgIdAndTxt("MEXMPFR:mx_mpfr_set_str:mpfr_set_str",
                        "mx_mpfr_set_str: cstr(%d) mpfr_set_str failed.",
                        idx);
    }
    mpfr_to_mx(pmxa, pa, idx, rop);
    mxFree(str);
    str = NULL;
  }
  plhs[0] = mxCreateStructMatrix(1, 1, NFIELDS, field_names);
  mex_plhs_set(plhs[0], pmxa, pa);
  mpfr_clear(rop);
}
