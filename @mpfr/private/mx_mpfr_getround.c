/*

 * determine mpfr rounding mode from intlab rounding mode
 *
  Intlab rounding mode | MPFR rounding mode |  description
   ---------------------------------------------------------------------------------
        -1             | MPFR_RNDD          |  round downwards (towards -inf)
         0             | MPFR_RNDN          |  round to nearest
         1             | MPFR_RNDU          |  round upwards (towards inf)
         2             | MPFR_RNDZ          |  round towards zero (chop)
         -             | MPFR_RNDA          |  round away from zero (experimental)


 * written  24.05.2011     F. Buenger
 *
 */
#include <stdio.h>
#include <math.h>
#include "gmp.h"
#include "mpfr.h"
#include "mex.h"
#include "matrix.h"


void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[] ) {
  int rnd_intlab;
  mpfr_rnd_t rnd_mpfr;

  rnd_intlab = (int)mxGetScalar(prhs[0]);
  switch(rnd_intlab) {
  case -1:
    rnd_mpfr = MPFR_RNDD;
    break;
  case 0:
    rnd_mpfr = MPFR_RNDN;
    break;
  case 1:
    rnd_mpfr = MPFR_RNDU;
    break;
  case 2:
    rnd_mpfr = MPFR_RNDZ;
    break;
  default:
    mexErrMsgTxt("mx_mpfr_get_round error: unknown rounding mode");
  }
  plhs[0] = mxCreateDoubleScalar((double)rnd_mpfr);
  return;
}







