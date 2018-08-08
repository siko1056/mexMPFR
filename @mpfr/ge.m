function res = ge(a,b)
% GE  Elementwise 'a >= b' for MPFR objects.
%

% written  07.11.2011     T.Xu

sizetest(a,b);
GE_NR = 3;

if ~isa (a, 'mpfr')
  a = mpfr(a);
end
if ~isa (b, 'mpfr')
  b = mpfr(b);
end

r = mx_mpfr_compare(a, b, GE_NR);
res = abs(sign(r));

end
