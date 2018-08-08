/**
 * mex_mpfr_sample  Sample MPFR usage from https://www.mpfr.org/sample.html.
 */

#include "gmp.h"
#include "mpfr.h"
#include "mex.h"

void mexFunction( int nlhs, mxArray *plhs[], 
		              int nrhs, const mxArray*prhs[] ) {
	unsigned int i;
  mpfr_t s, t, u;
  char buf[200];

  mpfr_init2 (t, 200);
  mpfr_set_d (t, 1.0, MPFR_RNDD);
  mpfr_init2 (s, 200);
  mpfr_set_d (s, 1.0, MPFR_RNDD);
  mpfr_init2 (u, 200);
  for (i = 1; i <= 100; i++)
    {
      mpfr_mul_ui (t, t, i, MPFR_RNDU);
      mpfr_set_d (u, 1.0, MPFR_RNDD);
      mpfr_div (u, u, t, MPFR_RNDD);
      mpfr_add (s, s, u, MPFR_RNDD);
    }
  mpfr_sprintf (buf, "s = %.16Rf", s);
  mexPrintf ("%s\n", buf);
  mpfr_clear (s);
  mpfr_clear (t);
  mpfr_clear (u);
  mpfr_free_cache ();
}
