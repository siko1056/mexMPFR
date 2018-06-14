function res = ge(a,b)
%GE           Implements  a >= b  elementwise for mpfr variables a and b
%
%  if true,  a  is definitely greater than or equal to  b
%

% written  07.11.2011     T.Xu

sizetest(a,b);
GE_NR = 3 ;

if ~isa(a,'mpfr')
    a = mpfr(a);
end
if ~isa(b,'mpfr')
    b = mpfr(b);
end

r = mx_mpfr_compare(a,b,GE_NR); 
res = abs(sign(r));
