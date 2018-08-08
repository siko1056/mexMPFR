
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
  int as_op;
  mpfr_rnd_t rnd;
  mwIndex idx, numel_0, numel_1, numel_max, i_max, i_min;
  mwSize ndims, *dims;
  mpfr_prec_t prec;
  double *pop;
  mx_mpfr_arr pmxa[3];
  mx_mpfr_ptr pa[3];
  int hasDouble = 0;
  int subDouble = 0;
  int (* fp) (mpfr_ptr rop, mpfr_srcptr op1, mpfr_srcptr op2, mpfr_rnd_t rnd) = NULL;
  int	(* fpd)(mpfr_ptr rop, mpfr_srcptr op1, double pop,      mpfr_rnd_t rnd) = NULL;
  int	(*dfp) (mpfr_ptr rop, double pop,      mpfr_srcptr op1, mpfr_rnd_t rnd) = NULL;
  
  as_op = (int)mxGetScalar(prhs[3]);
  
  if (as_op >= ADD_D)
    hasDouble = 1;
  if (as_op >= D_SUB)
    subDouble = 1;
  
  switch(as_op){
    case ADD:
      fp = mpfr_add;
      break;
    case SUB:
      fp = mpfr_sub;
      break;
    case MUL:
      fp = mpfr_mul;
      break;
    case DIV:
      fp = mpfr_div;
      break;
    case ADD_D:
      fpd = mpfr_add_d;
      break;
    case SUB_D:
      fpd = mpfr_sub_d;
      break;
    case MUL_D:
      fpd = mpfr_mul_d;
      break;
    case DIV_D:
      fpd = mpfr_div_d;
      break;
    case D_SUB:
      dfp = mpfr_d_sub;
      break;
    case D_DIV:
      dfp = mpfr_d_div;
      break;
  }
  
  mex_prhs_get(pmxa[0], pa[0], prhs[0]);
  
  if (as_op >= ADD_D) {
    pop = mxGetPr(prhs[1]); /* get pointer to double array */
  } else {
    mex_prhs_get(pmxa[1], pa[1], prhs[1]);
  }
  rnd = (mpfr_rnd_t)mxGetScalar(prhs[2]);
  
  if (hasDouble) {
    
    mpfr_init(op1);
    mpfr_init(rop);
    
    /* get number of elements */
    numel_0 = (mwIndex)mxGetNumberOfElements(pmxa[0][SIGN_NR]);
    numel_1 = (mwIndex)mxGetNumberOfElements(prhs[1]);
    
    if(numel_0 > numel_1){ /* => mumel_1 = 1: */
      ndims = mxGetNumberOfDimensions(pmxa[0][SIGN_NR]);
      dims = (mwSize*)mxGetDimensions(pmxa[0][SIGN_NR]);
      mex_mpfr_init(pmxa[1], pa[1], ndims, dims);
      
      for(idx=0;idx<numel_0;++idx){
        mx_to_mpfr(op1, pa[0], idx);
        /* prec(rop):=max(prec(op1),prec(op2))*/
        mpfr_set_prec(rop, max(mpfr_get_prec(op1), DOUBLE_PREC));
        if (subDouble)
          ternary = (*dfp)(rop, pop[0], op1, rnd);
        else
          ternary = (*fpd)(rop, op1, pop[0], rnd); /* rop:=op1+op2 */
        /*if(ternary!=0) mexPrintf("\n mpfr_add return value = %d \n", ternary);*/
        mpfr_to_mx(pmxa[1], pa[1], idx, rop);
      }
      
    }else{ /* numel_0 <= numel_1 */
      ndims = mxGetNumberOfDimensions(prhs[1]);
      dims = (mwSize*)mxGetDimensions(prhs[1]);
      mex_mpfr_init(pmxa[1], pa[1], ndims, dims); /* init pointer array for mpfr output array*/
      if(numel_0 < numel_1){ /* => mumel_0 = 1: */
        mx_to_mpfr(op1, pa[0], 0); /* get first input parameter */
        prec = mpfr_get_prec(op1);
        for(idx=0;idx<numel_1;++idx){
          /* prec(rop):=max(prec(op1),prec(op2))*/
          mpfr_set_prec(rop, max(prec, DOUBLE_PREC));
          if (subDouble)
            ternary = (*dfp)(rop, pop[idx], op1, rnd);
          else
            ternary = (*fpd)(rop, op1, pop[idx], rnd); /* rop:=op1+op2 */
          /*if(ternary!=0) mexPrintf("\n mpfr_add return value = %d \n", ternary);*/
          mpfr_to_mx(pmxa[1], pa[1], idx, rop);
        }
      }else{ /* mumel_0 = numel_1 */
        for(idx=0;idx<numel_1;++idx){
          mx_to_mpfr(op1, pa[0], idx); /* get first input parameter */
          /* prec(rop):=max(prec(op1),prec(op2))*/
          mpfr_set_prec(rop, max(mpfr_get_prec(op1), DOUBLE_PREC));
          if (subDouble)
            ternary = (*dfp)(rop, pop[idx], op1, rnd);
          else
            ternary = (*fpd)(rop, op1, pop[idx], rnd); /* rop:=op1+op2 */
          /*if(ternary!=0) mexPrintf("\n mpfr_add return value = %d \n", ternary);*/
          mpfr_to_mx(pmxa[1], pa[1], idx, rop);
        }
      }
    }
    plhs[0] = mxCreateStructMatrix(1, 1, NFIELDS, field_names);
    mex_plhs_set(plhs[0], pmxa[1], pa[1]);
    mpfr_clear(op1);
    mpfr_clear(rop);
    
  } else {
    
    /* mpfr_inits(op1, op2, rop); */ /* <-- produces Segmentation violation */
    mpfr_init(op1);
    mpfr_init(op2);
    mpfr_init(rop);
    /* get number of elements */
    numel_0 = (mwIndex)mxGetNumberOfElements(pmxa[0][SIGN_NR]);
    numel_1 = (mwIndex)mxGetNumberOfElements(pmxa[1][SIGN_NR]);
    numel_max = max(numel_0, numel_1);
    
    /*create output-array*/
    if(numel_0 >= numel_1){
      i_max = 0;
      i_min = 1;
    }else{
      i_max = 1;
      i_min = 0;
    }
    
    ndims = mxGetNumberOfDimensions(pmxa[i_max][SIGN_NR]);
    dims = (mwSize*)mxGetDimensions(pmxa[i_max][SIGN_NR]);
    mex_mpfr_init(pmxa[2], pa[2], ndims, dims);
    
    if(numel_0 == numel_1){
      for(idx=0;idx<numel_max;++idx){
        mx_to_mpfr(op1, pa[0], idx);
        mx_to_mpfr(op2, pa[1], idx);
        mpfr_set_prec(rop, max(mpfr_get_prec(op1), mpfr_get_prec(op2)));
        ternary = (*fp)(rop, op1, op2, rnd); /* rop:=op1+op2 */
        /*if(ternary!=0) mexPrintf("\n mpfr_add return value = %d \n", ternary);*/
        mpfr_to_mx(pmxa[2], pa[2], idx, rop);
        
      }
    }else{
      /* The input parameter corresponding to the index i_min is a single number and
       * the input parameter corresponding to the index i_max is an array with more than one value. */
      mx_to_mpfr(op2, pa[i_min], 0);
      prec = mpfr_get_prec(op2);
      for(idx=0;idx<numel_max;++idx){
        mx_to_mpfr(op1, pa[i_max], idx);
        /* prec(rop):=max(prec(op1),prec(op2))*/
        mpfr_set_prec(rop, max(mpfr_get_prec(op1), prec));
        ternary = (*fp)(rop, op1, op2, rnd); /* rop:=op1+op2 */
        
        mpfr_to_mx(pmxa[2], pa[2], idx, rop);
      }
    }
    
    plhs[0] = mxCreateStructMatrix(1, 1, NFIELDS, field_names);
    mex_plhs_set(plhs[0], pmxa[2], pa[2]);
    
    /* mpfr_clears(op1, op2, rop);*/
    mpfr_clear(op1);
    mpfr_clear(op2);
    mpfr_clear(rop);
  }
  
  return;
}