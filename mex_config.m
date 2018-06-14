% compilation of all mex-functions of the Matlab-MPFR interface

% written  07.11.2011     T. Xu

cd ./@mpfr/private
% The local mexoptionsfile mexopts.sh must be located in this directory
% so that the mex command automatically uses it.
% The name must be exactly mexopts.sh. If you want to rename it and/or
% move it to another directory the full path must be given using the -f
% option.
% Example:  mex -f <path>/mpfr_mexopts.sh mx_mpfr_set_string.c mexmpfr.c

% rounding
mex mx_mpfr_getround.c

% get defaults
mex mx_mpfr_get_default_prec.c
mex mx_mpfr_get_default_rounding_mode.c

% mathematical constants
mex mx_mpfr_constants.c mexmpfr.c

% set
mex mx_mpfr_set_d.c mexmpfr.c
mex mx_mpfr_set_string.c mexmpfr.c
 
% display
mex mx_display.c mexmpfr.c

% basic operations
mex mx_mpfr_elementals.c mexmpfr.c
mex mx_mpfr_add.c mexmpfr.c
mex mx_mpfr_add_d.c mexmpfr.c

% matrix mul
mex mx_mpfr_mmul.c mexmpfr.c

% comparsion operations
mex mx_mpfr_compare.c mexmpfr.c

% conversion
mex mx_mpfr_to_double.c mexmpfr.c


cd ../..