/**
 * mexMPFR interface
 *
 * written  20.05.2011     F. Buenger
 */

#define MX_BASE  2 /* storage base: binary*/

/* fieldnames for the MATLAB structure */
#define PREC_STR  "prec"  /* precision field */
#define SIGN_STR  "sign"  /* sign field */
#define EXP_STR   "exp"   /* exponent field */
#define D_END_STR "d_end" /* field for storing the end index of the limb array */
#define D_STR     "d"     /* limbs field */

/* ordering/numbering of the fieldnames for the MATLAB structure */
#define PREC_NR   0 /* precision field number */
#define SIGN_NR   1 /* sign field number*/
#define EXP_NR    2 /* exponent field number*/
#define D_END_NR  3 /* limb begin number */
#define D_NR      4 /* limbs field number*/
#define NFIELDS   5 /* number of fields in the mpfr structure*/

/* base for display: decimal */
#define B_DISP 10
/* number of significands to be displayed, 0 means all significands */
#define SIZE_DISP 0
/*
 * Using a precision of 53 bits, MPFR is able to exactly reproduce all
 * computations with double-precision machine floating-point numbers
 */
#define DOUBLE_PREC 53

#define MANTISSA_STR "mantissa" /* limbs field */
#define DISP_NFIELDS  2 /* number of fields in the mpfr structure*/

/* enumeration of comparsion operators */
#define LT_NR 0 /* <  */
#define GT_NR 1 /* >  */
#define LE_NR 2 /* <= */
#define GE_NR 3 /* >= */
#define EQ_NR 4 /* == */

/* enumeration of elemental operators */
#define ADD   0 /* mpfr + mpfr */
#define SUB   1 /* mpfr - mpfr */
#define MUL   2 /* mpfr .* mpfr */
#define DIV   3 /* mpfr ./ mpfr */
#define ADD_D 4 /* mpfr + double && double + mpfr */
#define SUB_D 5 /* mpfr - double */
#define MUL_D 6 /* mpfr .* double && double .* mpfr */
#define DIV_D 7 /* mpfr ./ double */
#define D_SUB 8 /* double - mpfr */
#define D_DIV 9 /* double ./ mpfr */

/* enumeration of mathematical constants*/
#define CONST_LOG2_NR    0 /* ln(2) */
#define CONST_PI_NR      1 /* pi */
#define CONST_EULER_NR   2 /* Euler constant */
#define CONST_CATALAN_NR 3 /* Catalan constant */

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

typedef double*  mx_mpfr_ptr[NFIELDS];
typedef mxArray* mx_mpfr_arr[NFIELDS];

extern const char *field_names[];
extern const char *disp_field_names[];

/*
 * Convert MATLAB mxArray to mpfr_t-Format.
 */
void mx_to_mpfr(mpfr_t x, mx_mpfr_ptr pa, int idx);

/*
 * Convert mpfr_t-Format to MATLAB mxArray.
 */
void mpfr_to_mx(mx_mpfr_arr pmxa, mx_mpfr_ptr pa, int idx,mpfr_t x);

/*
 * Initialize mx_mpfr return structure.
 */
void mex_mpfr_init(mx_mpfr_arr pmxa, mx_mpfr_ptr pa, mwSize ndim,
                   const mwSize *dims);
/*
 * Initialize mx_mpfr output structure.
 */
void mex_plhs_set(mxArray* pl, mx_mpfr_arr pmxa, mx_mpfr_ptr pa);

/*
 * Initialize mx_mpfr input structure.
 */
void mex_prhs_get(mx_mpfr_arr pmxa, mx_mpfr_ptr pa, const mxArray* pr);

/*
 * Computes the end index of the preceeding limb array.
 *
 * For `idx <= 0* the function returns "-1".
 */
int d_end_pred(mx_mpfr_ptr pa, int idx);
