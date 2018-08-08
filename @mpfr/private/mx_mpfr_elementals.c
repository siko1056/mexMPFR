/**
 * Elementwise arithmetic operations on MPFR data.
 *
 * Usage:
 *        c = mx_mpfr_elementals(a, b, rnd, op)
 *
 * Input:
 *          'a'  MPFR operand (also for 'D_SUB' and 'D_DIV'!)
 *          'b'  MPFR or double operand (depends on 'op')
 *        'rnd'  rounding mode (for 'c')
 *         'op'  Operation
 *                 ADD
 *                 SUB     mpfr - mpfr
 *                 MUL     mpfr .* mpfr
 *                 DIV     mpfr ./ mpfr
 *                 ADD_D   mpfr + double && double + mpfr
 *                 SUB_D   mpfr - double
 *                 MUL_D   mpfr .* double && double .* mpfr
 *                 DIV_D   mpfr ./ double
 *                 D_SUB   double - mpfr
 *                 D_DIV   double ./ mpfr
 *
 * written  19.05.2011     F. Buenger
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
  int operation;
  mpfr_rnd_t rnd;
  mwIndex idx, numel_0, numel_1, numel_max, i_max, i_min;
  mwSize ndims, *dims;
  mpfr_prec_t prec;
  double *pop;
  mx_mpfr_arr pmxa[3];
  mx_mpfr_ptr pa[3];
  int op1_is_double = 0;
  int (*fp )(mpfr_ptr rop,
             mpfr_srcptr op1, mpfr_srcptr op2,
             mpfr_rnd_t rnd) = NULL;
  int (*fpd)(mpfr_ptr rop,
             mpfr_srcptr op1, double pop,
             mpfr_rnd_t rnd) = NULL;
  int (*dfp)(mpfr_ptr rop,
             double pop, mpfr_srcptr op1,
             mpfr_rnd_t rnd) = NULL;

  if (nrhs != 4) {
    mexErrMsgIdAndTxt("MEXMPFR:mx_mpfr_elementals:rhs",
                      "mx_mpfr_elementals: Function requires four inputs.");
  }

  /* Get first  input: MPFR variable */
  mex_prhs_get(pmxa[0], pa[0], prhs[0]);
  /* Get third  input: Rounding mode */
  rnd = (mpfr_rnd_t)mxGetScalar(prhs[2]);
  /* Get fourth input: Operation */
  operation = (int)mxGetScalar(prhs[3]);

  if (operation >= D_SUB)
    op1_is_double = 1;

  /* Assign operation */
  switch (operation) {
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
  default:
    mexErrMsgIdAndTxt("MEXMPFR:mx_mpfr_elementals:unsupportedOperation",
                      "mx_mpfr_elementals: Operation not supported.");
  }

  switch (operation) {
  case ADD:
  case SUB:
  case MUL:
  case DIV:
    /* Get second input: MPFR variable */
    mex_prhs_get(pmxa[1], pa[1], prhs[1]);

    /* TODO: mpfr_inits(op1, op2, rop); segfault? */
    mpfr_init(op1);
    mpfr_init(op2);
    mpfr_init(rop);

    /* Get number of elements */
    numel_0 = (mwIndex)mxGetNumberOfElements(pmxa[0][SIGN_NR]);
    numel_1 = (mwIndex)mxGetNumberOfElements(pmxa[1][SIGN_NR]);
    numel_max = max(numel_0, numel_1);

    /* Get the index of the MPFR variable with the most elements 'i_max' */
    if (numel_0 >= numel_1) {
      i_max = 0;
      i_min = 1;
    } else {
      i_max = 1;
      i_min = 0;
    }

    /* Create output array */
    ndims = mxGetNumberOfDimensions(pmxa[i_max][SIGN_NR]);
    dims = (mwSize*)mxGetDimensions(pmxa[i_max][SIGN_NR]);
    mex_mpfr_init(pmxa[2], pa[2], ndims, dims);

    if (numel_0 == numel_1) {
      /* MPFR vector - vector operation of same length */
      for (idx = 0; idx < numel_max; ++idx) {
        mx_to_mpfr(op1, pa[0], idx);
        mx_to_mpfr(op2, pa[1], idx);
        mpfr_set_prec(rop, max(mpfr_get_prec(op1), mpfr_get_prec(op2)));
        ternary = (*fp)(rop, op1, op2, rnd);
        if (ternary != 0) {
          mexPrintf("\n mx_mpfr_elementals: MPFR returned = %d\n", ternary);
        }
        mpfr_to_mx(pmxa[2], pa[2], idx, rop);
      }
    } else if ((numel_0 == 1) || (numel_1 == 1)) {
      /* MPFR vector - scalar operation */
      mx_to_mpfr(op2, pa[i_min], 0); /* op2: scalar operand */
      prec = mpfr_get_prec(op2);
      for (idx = 0; idx < numel_max; ++idx) {
        mx_to_mpfr(op1, pa[i_max], idx);
        mpfr_set_prec(rop, max(mpfr_get_prec(op1), prec));
        ternary = (*fp)(rop, op1, op2, rnd); /* rop:=op1+op2 */
        if (ternary != 0) {
          mexPrintf("\n mx_mpfr_elementals: MPFR returned = %d\n", ternary);
        }
        mpfr_to_mx(pmxa[2], pa[2], idx, rop);
      }
    } else {
    }

    plhs[0] = mxCreateStructMatrix(1, 1, NFIELDS, field_names);
    mex_plhs_set(plhs[0], pmxa[2], pa[2]);

    /* TODO: mpfr_clears(op1, op2, rop);*/
    mpfr_clear(op1);
    mpfr_clear(op2);
    mpfr_clear(rop);
    break;

  case ADD_D:
  case SUB_D:
  case MUL_D:
  case DIV_D:
  case D_SUB:
  case D_DIV:

    /* Get second input: double array */
    pop = mxGetPr(prhs[1]);

    mpfr_init(op1);
    mpfr_init(rop);

    /* Get number of elements */
    numel_0 = (mwIndex)mxGetNumberOfElements(pmxa[0][SIGN_NR]);
    numel_1 = (mwIndex)mxGetNumberOfElements(prhs[1]);

    if (numel_1 == 1) {
      /* Scalar double operand */
      ndims = mxGetNumberOfDimensions(pmxa[0][SIGN_NR]);
      dims = (mwSize*)mxGetDimensions(pmxa[0][SIGN_NR]);
      mex_mpfr_init(pmxa[1], pa[1], ndims, dims);

      for (idx = 0; idx < numel_0; ++idx) {
        mx_to_mpfr(op1, pa[0], idx);
        /* prec(rop):=max(prec(op1),prec(op2))*/
        mpfr_set_prec(rop, max(mpfr_get_prec(op1), DOUBLE_PREC));
        if (op1_is_double) {
          ternary = (*dfp)(rop, pop[0], op1, rnd);
        } else {
          ternary = (*fpd)(rop, op1, pop[0], rnd);
        }
        if (ternary != 0) {
          mexPrintf("\n mx_mpfr_elementals: MPFR returned = %d\n", ternary);
        }
        mpfr_to_mx(pmxa[1], pa[1], idx, rop);
      }
    } else if (numel_0 == 1) {
      /* Scalar MPFR operand */
      ndims = mxGetNumberOfDimensions(prhs[1]);
      dims = (mwSize*)mxGetDimensions(prhs[1]);
      mex_mpfr_init(pmxa[1], pa[1], ndims, dims);
      mx_to_mpfr(op1, pa[0], 0); /* op1: scalar MPFR operand */
      prec = mpfr_get_prec(op1);
      for (idx = 0; idx < numel_1; ++idx) {
        mpfr_set_prec(rop, max(prec, DOUBLE_PREC));
        if (op1_is_double) {
          ternary = (*dfp)(rop, pop[idx], op1, rnd);
        } else {
          ternary = (*fpd)(rop, op1, pop[idx], rnd);
        }
        if (ternary != 0) {
          mexPrintf("\n mx_mpfr_elementals: MPFR returned = %d\n", ternary);
        }
        mpfr_to_mx(pmxa[1], pa[1], idx, rop);
      }
    } else if (numel_0 == numel_1) {
      /* MPFR vector - double vector operation of same length */
      for (idx = 0; idx < numel_1; ++idx) {
        mx_to_mpfr(op1, pa[0], idx);
        mpfr_set_prec(rop, max(mpfr_get_prec(op1), DOUBLE_PREC));
        if (op1_is_double) {
          ternary = (*dfp)(rop, pop[idx], op1, rnd);
        } else {
          ternary = (*fpd)(rop, op1, pop[idx], rnd);
        }
        if (ternary != 0) {
          mexPrintf("\n mx_mpfr_elementals: MPFR returned = %d\n", ternary);
        }
        mpfr_to_mx(pmxa[1], pa[1], idx, rop);
      }
    } else {
      mexErrMsgIdAndTxt("MEXMPFR:mx_mpfr_elementals:unsupportedOperation",
                        "mx_mpfr_elementals: Operation not supported.");
    }
    plhs[0] = mxCreateStructMatrix(1, 1, NFIELDS, field_names);
    mex_plhs_set(plhs[0], pmxa[1], pa[1]);
    mpfr_clear(op1);
    mpfr_clear(rop);
    break;

  default:
    mexErrMsgIdAndTxt("MEXMPFR:mx_mpfr_elementals:unsupportedOperation",
                      "mx_mpfr_elementals: Operation not supported.");
  }
}
