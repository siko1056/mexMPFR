function c = double(a)
% DOUBLE implements the conversion from mpfr to double

% written  07.11.2011     T.Xu

rnd = mx_mpfr_getround(getround());
c = mx_mpfr_to_double(a,rnd); % c := double(a)





