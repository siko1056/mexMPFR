/* 
 * Kompilieren in Matlab mit
 *   mex -f mexopts.sh mex_mpfr.c
 *
 * Ausführen aus Matlab 
 *   mex_mpfr
 */
#include <stdio.h>
#include "gmp.h"
#include "mpfr.h"
#include "mex.h"
void mexFunction( int nlhs, mxArray *plhs[], 
		  int nrhs, const mxArray*prhs[] )
{
	mexPrintf ("MPFR library: %-12s\nMPFR header: %s (based on %d.%d.%d)\n",
		mpfr_get_version(), MPFR_VERSION_STRING, MPFR_VERSION_MAJOR,
		MPFR_VERSION_MINOR, MPFR_VERSION_PATCHLEVEL);
	return;
}