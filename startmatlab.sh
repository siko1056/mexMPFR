export LD_LIBRARY_PATH=MPFRDIR/mpfr/lib:MPFRDIR/gmp/lib
export LIBRARY_PATH=MPFRDIR/mpfr/lib:MPFRDIR/gmp/lib
export C_INCLUDE_PATH=MPFRDIR/mpfr/include:MPFRDIR/gmp/include
matlab -r "addpath(genpath('MATLABMPFRDIR/')); cd MATLABMPFRDIR/mpfr; startup;"
