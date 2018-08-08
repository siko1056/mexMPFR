function res = eq(a, b)
% EQ  Elementwise equality comparison 'a == b' for MPFR objects.
%

% written  07.11.2011     T.Xu

sizetest(a,b);
EQ_NR = 4;

if ~isa (a, 'mpfr')
  a = mpfr(a);
end
if ~isa (b, 'mpfr')
  b = mpfr(b);
end

r = mx_mpfr_compare(a,b,EQ_NR);
res = abs(sign(r));

end
