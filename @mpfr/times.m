function c = times(a,b)
% TIMES  Elementwise multiplication 'a .* b'.
%

% written  07.11.2011     T.Xu

MUL = 2;
MUL_D = 6;

sizetest(a,b);
rnd = mx_mpfr_getround(getround());
if isa(a,'double')
  c = mx_mpfr_elementals(b,a,rnd, MUL_D); % c := b .* a
elseif isa(b,'double')
  c = mx_mpfr_elementals(a,b,rnd, MUL_D); % c := a .* b
else
  if  ~isa(a,'mpfr')
    a = mpfr(a);
  elseif ~isa(b,'mpfr')
    b = mpfr(b);
  end
  c = mx_mpfr_elementals(a,b,rnd, MUL); % c := a .* b
end
c = class(c,'mpfr');

end
