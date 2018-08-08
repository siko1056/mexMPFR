/*  mex-interface for MPFR-functions
 *  int mpfr_const_<constname> (mpfr_t rop, mpfr_rnd_t rnd)
 *
 * written  10.06.2011     F. Buenger
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
  int ternary, const_nr;
  mx_mpfr_arr pmxa;
  mx_mpfr_ptr pa;
  int (*fp)(mpfr_t rop, mpfr_rnd_t rnd) =
    NULL;   /* function pointer to a comparsion function*/

  rnd = (mpfr_rnd_t)mxGetScalar(
          prhs[0]); /* get first input parameter rounding mode */
  prec = (mpfr_prec_t)mxGetScalar(
           prhs[1]); /* get second input parameter precision */
  const_nr = (int)mxGetScalar(
               prhs[2]); /* get third input parameter identifier of the constant */

  mpfr_init2(rop,prec); /* initialize rop with given precision */
  switch(const_nr) {
  case CONST_LOG2_NR:
    fp = mpfr_const_log2;
    break;
  case CONST_PI_NR:
    fp = mpfr_const_pi;
    break;
  case CONST_EULER_NR:
    fp = mpfr_const_euler;
    break;
  case CONST_CATALAN_NR:
    fp = mpfr_const_catalan;
    break;
  }

  ternary = (*fp)(rop,rnd); /* MPFR call */
  /*if(ternary!=0) mexPrintf("\n mpfr_const_... return value = %d \n",ternary);*/

  mex_mpfr_init(pmxa,pa,1,mxGetDimensions(mxCreateDoubleScalar(1)));
  mpfr_to_mx(pmxa,pa,0,rop);
  plhs[0] = mxCreateStructMatrix(1,1,NFIELDS,field_names);
  mex_plhs_set(plhs[0],pmxa,pa);

  mpfr_clear(rop);
  return;
}
