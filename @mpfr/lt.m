function res = lt(a,b)
%LT           Implements  a < b  elementwise for mpfr variables
%
%  if true,  a  is definitely less than  b
%

% written  07.11.2011     T.Xu

LT_NR = 0;

sizetest(a,b);

if ~isa(a,'mpfr')
    a = mpfr(a);
end
if ~isa(b,'mpfr')
    b = mpfr(b);
end

r = mx_mpfr_compare(a,b,LT_NR); 
res = abs(sign(r));
