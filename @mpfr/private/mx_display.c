/* mex-file for blocked call of the MPFR-function
 *
 * char *mpfr_get_str(char *str,mpfr_exp_t *expptr,int b,size_t n,mpfr_t op,mpfr_rnd_t rnd)
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
  mpfr_t x;
  mpfr_rnd_t rnd;
  mpfr_prec_t prec;
  int ternary;
  mwIndex idx,idx_max = 1;
  mwSize ndims,*dims;
  char * str=NULL; /* output string */
  mpfr_exp_t exponent;
  mx_mpfr_arr pmxa;
  mx_mpfr_ptr pa;

  rnd = (mpfr_rnd_t)mxGetScalar(prhs[1]); /* get rounding mode */
  /* create an Array for output that has the same size like the input-Array
     prhs[0] of doubles which shall be converted to multiple precision format mpfr_t */

  mex_prhs_get(pmxa,pa,prhs[0]);
  ndims = mxGetNumberOfDimensions(pmxa[PREC_NR]);
  dims = (mwSize*)mxGetDimensions(pmxa[PREC_NR]);

  plhs[0] = mxCreateStructArray(ndims,dims,DISP_NFIELDS,disp_field_names);
  /* convert all double entries prhs[0](i_1,i_2,....,i_ndims) to mpfr-format */
  idx_max = (mwIndex)mxGetNumberOfElements(pmxa[PREC_NR])-1;
  mpfr_init(x); /* init x */
  for(idx=0; idx<=idx_max; ++idx) {
    mx_to_mpfr(x,pa,idx);  /* transfer data from mx- to mpfr-format */

    str = mpfr_get_str(str,&exponent,B_DISP,SIZE_DISP,x,rnd);

    if(str==NULL) mexErrMsgTxt("mpfr_get_sring returned NULL-pointer");
    /*mexPrintf("str = %s , exponent = %d \n",str,exponent);*/
    mxSetField(plhs[0],idx,MANTISSA_STR,mxCreateString(str));
    mxSetField(plhs[0],idx,EXP_STR,mxCreateDoubleScalar(exponent));
    mpfr_free_str(str);
    str = NULL;
  }
  mpfr_clear(x);
  return;
}







