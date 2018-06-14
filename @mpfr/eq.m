function res = eq(a,b)
%EQ           Implements  a == b  elementwise for mpfr variables
%

% written  07.11.2011     T.Xu

sizetest(a,b);
EQ_NR = 4;

if ~isa(a,'mpfr')
    a = mpfr(a);
end
if ~isa(b,'mpfr')
    b = mpfr(b);
end

r = mx_mpfr_compare(a,b,EQ_NR);
res = abs(sign(r));
