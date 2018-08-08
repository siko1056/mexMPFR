/* [rop,ternary] = mx_mpfr_get_default_rounding_mode()
    mex-file for reading the MPFR default rounding mode by calling the
    MPFR function

    mpfr_rnd_t mpfr_get_default_rounding_mode (void)


    written  16.05.1011     F. Buenger
 */

#include <stdio.h>
#include <math.h>
#include "gmp.h"
#include "mpfr.h"
#include "mex.h"

void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[] ) {
  plhs[0] = mxCreateDoubleScalar(mpfr_get_default_rounding_mode());
  return;
}







