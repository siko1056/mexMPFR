function res = gt(a,b)
%GT           Implements  a > b  elementwise for mpfr variables
%
%  if true,  a  is definitely greater than  b.
%

% written  07.11.2011     T.Xu

sizetest(a,b);
GT_NR = 1;

if ~isa(a,'mpfr')
    a = mpfr(a);
end
if ~isa(b,'mpfr')
    b = mpfr(b);
end

r = mx_mpfr_compare(a,b,GT_NR);
res = abs(sign(r));
  