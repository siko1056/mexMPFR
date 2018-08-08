/* rop = mx_mpfr_set_d(x,rnd,prec)
 * mex-file for calling the MPFR-function
 *
 *  int mpfr_set_d (mpfr_t rop, double op, mpfr_rnd_t rnd)
 *
 * Set the value of rop from op, rounded toward the given direction rnd.
 *
 * mex-input:
 *   x: double variable
 *  rnd: rounding mode
 * prec: precision (of rop)
 *
 * written  16.05.2011     F. Buenger
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
  mpfr_rnd_t rnd;
  mpfr_prec_t prec;
  int ternary;
  mwIndex idx,idx_max = 0;
  mwSize ndims,*dims;
  double *pind;
  mx_mpfr_arr pmxa;
  mx_mpfr_ptr pa;

  char* s;

  rnd = (mpfr_rnd_t)mxGetScalar(
          prhs[1]); /* get second input parameter rounding mode */
  prec = (mpfr_prec_t)mxGetScalar(
           prhs[2]); /* get third input parameter precision */
  mpfr_init2(rop,prec); /* initialize rop with given precision */

  ndims = mxGetNumberOfDimensions(prhs[0]);
  dims = (mwSize*)mxGetDimensions(prhs[0]);
  mex_mpfr_init(pmxa,pa,ndims,dims);

  /* convert all double entries prhs[0](i_1,i_2,....,i_ndims) to mpfr-format */
  idx_max=(mwIndex)mxGetNumberOfElements(prhs[0])
          -1;  /* idx_max := prod(dims)-1 */
  pind = mxGetPr(prhs[0]);
  for(idx=0; idx<=idx_max; ++idx) {
    ternary = mpfr_set_d(rop,(double)(pind[idx]),
                         rnd); /* store double value x in rop */
    /*if(ternary!=0) mexPrintf("mpfr_set_d return value = %d",ternary);*/
    mpfr_to_mx(pmxa,pa,idx,rop);
  }

  plhs[0] = mxCreateStructMatrix(1,1,NFIELDS,field_names);
  mex_plhs_set(plhs[0],pmxa,pa);

  mpfr_clear(rop);
  return;
}







