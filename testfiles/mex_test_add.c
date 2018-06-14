/* MEX-Test Programm * mex_test_add.c */
#include <stdio.h>
#include <math.h>
#include "mex.h"
void mexFunction( int nlhs, mxArray *plhs[], 
		  int nrhs, const mxArray*prhs[] )
{
	int a = (int)mxGetScalar(prhs[0]);
	int b = (int)mxGetScalar(prhs[1]);
	int c = a + b;
	plhs[0] = mxCreateDoubleScalar(c);
	nlhs = 1;
	mexPrintf("%d given parameters: %d, %d\n", nrhs, a, b);
	mexPrintf("returning parameter: %d\n", c);
	return;
}
