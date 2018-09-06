#include "mex.h"
#include "mpfr.h"

static uint64_t counter = 0;
static mpfr_t* mpfr_values = NULL;

void cleanup(void) {
  mexPrintf("MEX file is terminating, destroy all MPFR arrays.\n");
  mpfr_clear(*mpfr_values);
  mpfr_free_cache();
  mxFree(mpfr_values);
}

void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[]) {
  char buf[200];  /* Display buffer */
  
  /* Make sure the first argument is the MPFR function to process */
  if ((nrhs < 1) || (!mxIsChar(prhs[0]))) {
    mexErrMsgIdAndTxt("MEXMPFR:mpfr_:invalidField",
      "First argument must be a string.");
  }
  
  if (strcmp ("set_d", mxArrayToString(prhs[0])) == 0) {
    mexPrintf("  Do mpfr_set_d.\n");
  }
  
  if (counter == 0) {
    mexPrintf("MEX file initializing, create first MPFR array.\n");
    
    /* Create persistent array and register its cleanup. */
    mpfr_values = (mpfr_t*) mxMalloc(sizeof(mpfr_t));
    mexMakeMemoryPersistent(mpfr_values);
    mexAtExit(cleanup);
    counter = 1;
    
    /* Set the data of the array to some interesting value. */
    mpfr_init2 (*mpfr_values, 200);
    mpfr_set_d (*mpfr_values, 0.000000000001, MPFR_RNDD);
  } else {
    mpfr_sprintf (buf, "%.16Rf", *mpfr_values);
    mexPrintf("MEX file executing; mpfr_values(1) = %s\n", buf);
  }
}