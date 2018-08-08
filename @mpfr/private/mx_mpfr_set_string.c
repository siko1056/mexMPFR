/* mex-file for blocked calling of the MPFR-function
 *
 *  int mpfr_set_str (mpfr_t rop, const char *s, int base, mpfr_rnd_t rnd)
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
  int base,ternary;
  mpfr_rnd_t rnd;
  mpfr_prec_t prec;
  char *str = NULL;
  mwSize strlen;
  mwIndex idx,idx_max = 0;
  mwSize ndims,*dims;
  mxArray *pidx;
  mx_mpfr_arr pmxa;
  mx_mpfr_ptr pa;

  /* get input parameters base, rnd, prec */
  base = (int)mxGetScalar(prhs[1]); /*prhs[0].2 contains the base*/
  rnd = (mpfr_rnd_t)mxGetScalar(
          prhs[2]); /* get second input parameter rounding mode */
  prec = (mpfr_prec_t)mxGetScalar(
           prhs[3]); /* get third input parameter precision */

  mpfr_init2(rop,prec); /* initialize rop with given precision */

  /* create a CellArray for output that has the same size like the input-Array
     prhs[0] of doubles which shall be converted to multiple precision format mpfr_t */
  ndims = mxGetNumberOfDimensions(prhs[0]);
  dims = (mwSize*)mxGetDimensions(prhs[0]);


  ndims = mxGetNumberOfDimensions(prhs[0]);
  dims = (mwSize*)mxGetDimensions(prhs[0]);
  mex_mpfr_init(pmxa,pa,ndims,dims);


  /* convert all string entries prhs[0](i_1,i_2,....,i_ndims) to mpfr-format */
  idx_max=(mwIndex)mxGetNumberOfElements(prhs[0])-1;
  for(idx=0; idx<=idx_max; ++idx) {
    pidx = mxGetCell(prhs[0],idx);
    strlen = mxGetN(pidx)*sizeof(mxChar)+1;
    str = mxMalloc(strlen);
    if(str==NULL) mexErrMsgTxt("mxMalloc error return value NULL");
    ternary = mxGetString(pidx,str,strlen); /* Copy the string data into buf. */
    if(ternary!=0) mexErrMsgTxt("mxGetString error return value");
    /* convert string to mpfr-format */
    ternary = mpfr_set_str(rop,str,base,
                           rnd); /* convert numeric string to mpfr-format */

    /*if(ternary!=0) mexPrintf("mpfr_set_str return value = %d",ternary);*/
    mpfr_to_mx(pmxa,pa,idx,rop);
    mxFree(str);
    str = NULL;
  }
  plhs[0] = mxCreateStructMatrix(1,1,NFIELDS,field_names);
  mex_plhs_set(plhs[0],pmxa,pa);
  mpfr_clear(rop);
  return;
}
