/* mex-file for blocked calling of the MPFR-function
 *
 * int mpfr_add (mpfr_t rop, mpfr_t op1, mpfr_t op2, mpfr_rnd_t rnd)
 *
 * written  27.05.2011     F. Buenger
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
    mpfr_t op1, op2, rop;
    int ternary;
    mpfr_rnd_t rnd;
    mwIndex idx, numel_0, numel_1, numel_max, i_max, i_min;
    mwSize ndims, *dims;
    mpfr_prec_t prec;
    mx_mpfr_arr pmxa[3];
    mx_mpfr_ptr pa[3];
    
    mex_prhs_get(pmxa[0], pa[0], prhs[0]);
    mex_prhs_get(pmxa[1], pa[1], prhs[1]);
    rnd = (mpfr_rnd_t)mxGetScalar(prhs[2]);
    
    /* mpfr_inits(op1, op2, rop); */ /* <-- produces Segmentation violation */
    mpfr_init(op1);
    mpfr_init(op2);
    mpfr_init(rop);
    /* get number of elements */
    numel_0 = (mwIndex)mxGetNumberOfElements(pmxa[0][SIGN_NR]);
    numel_1 = (mwIndex)mxGetNumberOfElements(pmxa[1][SIGN_NR]);
    numel_max = max(numel_0, numel_1);
    
    
    /*create output-array*/
    if(numel_0 >= numel_1){i_max = 0; i_min = 1;}else{i_max = 1; i_min = 0;}
    ndims = mxGetNumberOfDimensions(pmxa[i_max][SIGN_NR]);
    dims = (mwSize*)mxGetDimensions(pmxa[i_max][SIGN_NR]);
    mex_mpfr_init(pmxa[2], pa[2], ndims, dims);
    
    if(numel_0 == numel_1){
        for(idx=0;idx<numel_max;++idx){
            mx_to_mpfr(op1, pa[0], idx);
            mx_to_mpfr(op2, pa[1], idx);
            /* prec(rop):=max(prec(op1),prec(op2))*/
            mpfr_set_prec(rop, max(mpfr_get_prec(op1), mpfr_get_prec(op2)));
            ternary = mpfr_add(rop, op1, op2, rnd); /* rop:=op1+op2 */
            /*if(ternary!=0) mexPrintf("\n mpfr_add return value = %d \n", ternary);*/
            mpfr_to_mx(pmxa[2], pa[2], idx, rop);
           /* mpfr_to_mx(pmxa[2], pa[2], idx, op1); *//* only for performance tests */
        }
    }else{
        /* The addend corresponding to the index i_min is a single number and
         * the addend corresponding to the index i_max is an array with more than one value. */
        mx_to_mpfr(op2, pa[i_min], 0);
        prec = mpfr_get_prec(op2);
        for(idx=0;idx<numel_max;++idx){
            mx_to_mpfr(op1, pa[i_max], idx);
            /* prec(rop):=max(prec(op1),prec(op2))*/
            mpfr_set_prec(rop, max(mpfr_get_prec(op1), prec));
            ternary = mpfr_add(rop, op1, op2, rnd); /* rop:=op1+op2 */
            /*if(ternary!=0) mexPrintf("\n mpfr_add return value = %d \n", ternary);*/
            mpfr_to_mx(pmxa[2], pa[2], idx, rop);
        }
    }
    plhs[0] = mxCreateStructMatrix(1, 1, NFIELDS, field_names);
    mex_plhs_set(plhs[0], pmxa[2], pa[2]);
    
    /* mpfr_clears(op1, op2, rop);*/
    mpfr_clear(op1);
    mpfr_clear(op2);
    mpfr_clear(rop);
        
    return;
}
