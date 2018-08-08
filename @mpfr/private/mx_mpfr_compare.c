/**
 * Elementwise arithmetic operations on MPFR data.
 *
 * Usage:
 *        c = mx_mpfr_compare(a, b, op)
 *
 * Input:
 *        'a'  MPFR operand
 *        'b'  MPFR operand
 *       'op'  Comparision operation
 *               LT_NR  <
 *               GT_NR  >
 *               LE_NR  <=
 *               GE_NR  >=
 *               EQ_NR  ==
 *
 * written  27.05.2011     F. Buenger
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
  mpfr_t op1, op2;
  int cmp_op;
  mwIndex idx, numel_0, numel_1, numel_max, i_max, i_min;
  mwSize ndims, *dims;
  mx_mpfr_arr pmxa[2];
  mx_mpfr_ptr pa[2];
  int (*fp)(mpfr_srcptr op1, mpfr_srcptr op2) = NULL;
  double *pres;

  if (nrhs != 3) {
    mexErrMsgIdAndTxt("MEXMPFR:mx_mpfr_elementals:rhs",
                      "mx_mpfr_elementals: Function requires four inputs.");
  }

  /* Get first MPFR operand */
  mex_prhs_get(pmxa[0], pa[0], prhs[0]);
  /* Get second MPFR operand */
  mex_prhs_get(pmxa[1], pa[1], prhs[1]);
  /* Get comparision operation */
  cmp_op = (int)mxGetScalar(prhs[2]);
  switch (cmp_op) {
  case LT_NR:
    fp = mpfr_less_p;
    break;
  case GT_NR:
    fp = mpfr_greater_p;
    break;
  case LE_NR:
    fp = mpfr_lessequal_p;
    break;
  case GE_NR:
    fp = mpfr_greaterequal_p;
    break;
  case EQ_NR:
    fp = mpfr_equal_p;
    break;
  default:
    mexErrMsgIdAndTxt("MEXMPFR:mx_mpfr_compare:unsupportedOperation",
                      "mx_mpfr_compare: Operation not supported.");
  }

  /* TODO: mpfr_inits(op1, op2, rop); segfault ? */
  mpfr_init(op1);
  mpfr_init(op2);

  /* Get number of elements */
  numel_0 = (mwIndex)mxGetNumberOfElements(pmxa[0][SIGN_NR]);
  numel_1 = (mwIndex)mxGetNumberOfElements(pmxa[1][SIGN_NR]);
  numel_max = max(numel_0, numel_1);

  /* Get the index of the MPFR variable with the most elements 'i_max' */
  if (numel_0 >= numel_1) {
    i_max = 0;
    i_min = 1;
  } else {
    i_max = 1;
    i_min = 0;
  }

  /* Create output array */
  ndims = mxGetNumberOfDimensions(pmxa[i_max][SIGN_NR]);
  dims = (mwSize*)mxGetDimensions(pmxa[i_max][SIGN_NR]);
  plhs[0] = mxCreateNumericArray(ndims, dims, mxDOUBLE_CLASS, mxREAL);
  pres = mxGetPr(plhs[0]);
  if (numel_0 == numel_1) {
    /* Elementwise comparision of equal sized operands */
    for (idx = 0; idx < numel_max; ++idx) {
      mx_to_mpfr(op1, pa[0], idx);
      mx_to_mpfr(op2, pa[1], idx);
      pres[idx] = (double)((*fp)(op1, op2)); /*  result = op1 cmp_op op2 */
    }
  } else if ((numel_0 == 1) || (numel_1 == 1)) {
    /* Elementwise comparision of vector with scalar operand */
    mx_to_mpfr(op2, pa[i_min], 0);
    for (idx=0; idx<numel_max; ++idx) {
      mx_to_mpfr(op1, pa[i_max], idx);
      pres[idx] = (*fp)(op1, op2); /*  result = op1 cmp_op op2 */
    }
  } else {
    mexErrMsgIdAndTxt("MEXMPFR:mx_mpfr_compare:unsupportedOperation",
                      "mx_mpfr_compare: Operation not supported.");
  }

  /* TODO: mpfr_clears(op1, op2, rop);*/
  mpfr_clear(op1);
  mpfr_clear(op2);
}
