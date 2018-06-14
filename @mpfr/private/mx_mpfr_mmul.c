/* mex-file for blocked calling of the MPFR-function
 *
 * written  07.11.2011    T.Xu
 */

#include <stdio.h>
#include <math.h>
#include "gmp.h"
#include "mpfr.h"
#include "mex.h"
#include "matrix.h"
#include "mexmpfr.h"

void mexFunction( int nlhs, mxArray *plhs[],
        int nrhs, const mxArray *prhs[] ) {
    mpfr_t *op1, *op2, rop, tmp, *pop1, *pop2;
    int ternary;
    mpfr_rnd_t rnd;
    mwIndex idx, numel_0, numel_1, numel_max, idx_a, idx_b, k;
    mwSize ndims, *dims, *dims_a, *dims_b, dimk, dima, dimb;
    mpfr_prec_t prec;
    mx_mpfr_arr pmxa[3];
    mx_mpfr_ptr pa[3];
	
    mex_prhs_get(pmxa[0], pa[0], prhs[0]);
    mex_prhs_get(pmxa[1], pa[1], prhs[1]);
    rnd = (mpfr_rnd_t)mxGetScalar(prhs[2]);
    
    /* mpfr_inits(op1, op2, rop); */ /* <-- produces Segmentation violation */
    mpfr_init(rop);
	mpfr_init(tmp);
	
    /* get number of elements */
    numel_0 = (mwIndex)mxGetNumberOfElements(pmxa[0][SIGN_NR]);
    numel_1 = (mwIndex)mxGetNumberOfElements(pmxa[1][SIGN_NR]);
	
	/*mex_mpfr_get_array(op1, pa[0], numel_0);*/
	
	op1 = (mpfr_t*) malloc(numel_0*sizeof(mpfr_t));
	for (idx=0; idx < numel_0; idx ++) {
		mpfr_init(op1[idx]);
		mx_to_mpfr(op1[idx], pa[0], idx);
	}
	
	/*mex_mpfr_get_array(op2, pa[1], numel_1);*/
	
	op2 = (mpfr_t*) malloc(numel_1*sizeof(mpfr_t));
	for (idx=0; idx < numel_1; idx ++) {
		mpfr_init(op2[idx]);
		mx_to_mpfr(op2[idx], pa[1], idx);
	}
	
    /*get dimensions*/
    ndims = mxGetNumberOfDimensions(pmxa[0][SIGN_NR]);
	dims_a = (mwSize*)mxGetDimensions(pmxa[0][SIGN_NR]);
    dims_b = (mwSize*)mxGetDimensions(pmxa[1][SIGN_NR]);
	dims   = (mwSize*)mxGetDimensions(pmxa[1][SIGN_NR]);
	
	dimk = dims_b[0];
	dima = dims_a[1];
	dimb = dims_b[1];
	dims[0] = dima;
	dims[1] = dimb; 
    /*create output-array*/
    mex_mpfr_init(pmxa[2], pa[2], ndims, dims);
	for (idx_b=0; idx_b < dimb; idx_b ++) {
		for (idx_a=0; idx_a < dima; idx_a ++) {
			mpfr_set_ui(rop, 0, rnd);
			
			for (k=0; k < dimk; k++) {
				
				mpfr_set_prec(tmp, max(mpfr_get_prec(op1[idx_a*dimk+k]), mpfr_get_prec(op2[idx_b*dimk+k])));
				ternary = mpfr_mul(tmp, op1[idx_a*dimk+k], op2[idx_b*dimk+k], rnd);
				ternary = mpfr_add(rop, tmp, rop, rnd);
			}
			idx=idx_b*dima+idx_a;
			mpfr_to_mx(pmxa[2], pa[2],idx,rop);
		}
	}    
    
    plhs[0] = mxCreateStructMatrix(1, 1, NFIELDS, field_names);
    mex_plhs_set(plhs[0], pmxa[2], pa[2]);
    
    /* mpfr_clears(op1, op2, rop);*/
    /*mex_mpfr_free_array(op1,numel_0);*/
	for (idx=0; idx < numel_0; idx ++) {
		mpfr_clear(op1[idx]);
	}
	free(op1);
    /*mex_mpfr_free_array(op2,numel_1);*/
	for (idx=0; idx < numel_1; idx ++) {
		mpfr_clear(op2[idx]);
	}
	free(op2);
	
    mpfr_clear(rop);
    mpfr_clear(tmp);
        
    return;
}
