function res = le(a,b)
% LE  Elementwise 'a <= b' for MPFR objects.
%

% written  07.11.2011     T.Xu

sizetest(a,b);
LE_NR = 2;

if ~isa(a,'mpfr')
  a = mpfr(a);
end
if ~isa(b,'mpfr')
  b = mpfr(b);
end

r = mx_mpfr_compare(a, b, LE_NR);
res = abs(sign(r));

end
