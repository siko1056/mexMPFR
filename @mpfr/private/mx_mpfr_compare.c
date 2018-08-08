/* mex-file for blocked calling of the MPFR-function
 *
 * int mpfr_add (mpfr_t rop, mpfr_t op1, mpfr_t op2, mpfr_rnd_t rnd)
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
  /* function pointer to a comparsion function*/
  int (*fp)(mpfr_srcptr op1, mpfr_srcptr op2) = NULL;
  double *pres;
  
  
  mex_prhs_get(pmxa[0], pa[0], prhs[0]);
  mex_prhs_get(pmxa[1], pa[1], prhs[1]);
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
  }
  
  /* mpfr_inits(op1, op2, rop); */ /* <-- produces Segmentation violation */
  mpfr_init(op1);
  mpfr_init(op2);
  /* get number of elements */
  numel_0 = (mwIndex)mxGetNumberOfElements(pmxa[0][SIGN_NR]);
  numel_1 = (mwIndex)mxGetNumberOfElements(pmxa[1][SIGN_NR]);
  numel_max = max(numel_0, numel_1);
  
  /*create output-array*/
  if (numel_0 >= numel_1) {
    i_max = 0;
    i_min = 1;
  } else {
    i_max = 1;
    i_min = 0;
  }
  ndims = mxGetNumberOfDimensions(pmxa[i_max][SIGN_NR]);
  dims = (mwSize*)mxGetDimensions(pmxa[i_max][SIGN_NR]);
  plhs[0] = mxCreateNumericArray(ndims, dims, mxDOUBLE_CLASS, mxREAL);
  pres = mxGetPr(plhs[0]);
  if(numel_0 == numel_1){
    for(idx=0;idx<numel_max;++idx){
      mx_to_mpfr(op1, pa[0], idx);
      mx_to_mpfr(op2, pa[1], idx);
      pres[idx] = (double)((*fp)(op1, op2)); /*  result = op1 cmp_op op2 */
    }
  }else{
    /* The input parameter corresponding to the index i_min is a single number and
     * the input parameter corresponding to the index i_max is an array with more than one value. */
    mx_to_mpfr(op2, pa[i_min], 0);
    for(idx=0;idx<numel_max;++idx){
      mx_to_mpfr(op1, pa[i_max], idx);
      pres[idx] = (*fp)(op1, op2); /*  result = op1 cmp_op op2 */
    }
  }
  
  /* mpfr_clears(op1, op2, rop);*/
  mpfr_clear(op1);
  mpfr_clear(op2);
  
  return;
}