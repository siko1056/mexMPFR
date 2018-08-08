/* mex-file for reading the MPFR default precision

    mpfr_prec_t mpfr_get_default_prec (void)

    Return the current default MPFR precision in bits.


    written  16.05.2011     F. Buenger
 */

#include <stdio.h>
#include <math.h>
#include "gmp.h"
#include "mpfr.h"
#include "mex.h"

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[]) {
  plhs[0] = mxCreateDoubleScalar(mpfr_get_default_prec());
  return;
}







