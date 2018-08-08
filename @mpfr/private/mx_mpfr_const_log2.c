/*  mex-interface for MPFR-functions
 *  int mpfr_const_log2(mpfr_t rop, mpfr_rnd_t rnd)
 *
 * written  19/05/1011     F. Bünger
 *
 */

#include <stdio.h>
#include <math.h>
#include "gmp.h"
#include "mpfr.h"
#include "mex.h"
#include "mexmpfr.h"

void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[] ) {
  mpfr_t rop;
  mpfr_rnd_t rnd;
  mpfr_prec_t prec;
  int ternary;
  mx_mpfr_arr pmxa;
  mx_mpfr_ptr pa;

  rnd = (mpfr_rnd_t)mxGetScalar(
          prhs[0]); /* get second input parameter rounding mode */
  prec = (mpfr_prec_t)mxGetScalar(
           prhs[1]); /* get third input parameter precision */
  mpfr_init2(rop,prec); /* initialize rop with given precision */
  ternary = mpfr_const_log2(rop,rnd); /* MPFR call */
  if(ternary!=0) mexPrintf("\n mpfr_const_log2 return value = %d \n",ternary);

  mex_mpfr_init(pmxa,pa,1,mxGetDimensions(mxCreateDoubleScalar(1)));
  mpfr_to_mx(pmxa,pa,0,rop);
  plhs[0] = mxCreateStructMatrix(1,1,NFIELDS,field_names);
  mex_plhs_set(plhs[0],pmxa,pa);

  mpfr_clear(rop);
  return;
}
