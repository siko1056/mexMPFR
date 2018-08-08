/**
 * Determine mpfr rounding mode from INTLAB rounding mode.
 *
 * Intlab rounding mode | MPFR rounding mode |  description
 * ---------------------------------------------------------------------------------
 *      -1              | MPFR_RNDD          |  round downwards (towards -inf)
 *       0              | MPFR_RNDN          |  round to nearest
 *       1              | MPFR_RNDU          |  round upwards (towards inf)
 *       2              | MPFR_RNDZ          |  round towards zero (chop)
 *       -              | MPFR_RNDA          |  round away from zero (experimental)
 *
 * written  24.05.2011     F. Buenger
 */

#include <stdio.h>
#include <math.h>
#include "gmp.h"
#include "mpfr.h"
#include "mex.h"
#include "matrix.h"

void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[] ) {
  if (nrhs != 1) {
    mexErrMsgIdAndTxt("MEXMPFR:mx_mpfr_get_round:rhs",
                      "mx_mpfr_get_round: This function requires one input.");
  }

  /* Default: round to nearest */
  int rnd_intlab = 0;
  mpfr_rnd_t rnd_mpfr = MPFR_RNDN;

  rnd_intlab = (int)mxGetScalar(prhs[0]);
  switch (rnd_intlab) {
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
    mexErrMsgIdAndTxt("MEXMPFR:mx_mpfr_get_round:unknownRoundingMode",
                      "mx_mpfr_get_round: unknown rounding mode");
  }
  plhs[0] = mxCreateDoubleScalar((double)rnd_mpfr);
}
