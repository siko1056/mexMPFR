/* MEX-Test Programm * mex_test.c */
#include <stdio.h>
#include <math.h>
#include "mex.h"
void mexFunction( int nlhs, mxArray *plhs[], 
		  int nrhs, const mxArray *prhs[] )
{
	mexPrintf("Hallo Mex\n");
	return;
}
