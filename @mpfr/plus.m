function c = plus(a,b)
% PLUS  Addition 'a + b'.
%

% written  07.11.2011     T.Xu

ADD = 0;
ADD_D = 4;

sizetest(a,b);
rnd = mx_mpfr_getround(getround());
if isa(a,'double')
  c = mx_mpfr_elementals(b,a,rnd, ADD_D); % c := b + a
elseif isa(b,'double')
  c = mx_mpfr_elementals(a,b,rnd, ADD_D); % c := a + b
else
  if ~isa(a,'mpfr')
    a = mpfr(a);
  elseif ~isa(b,'mpfr')
    b = mpfr(b);
  end
  c = mx_mpfr_elementals(a,b,rnd, ADD); % c := a + b
end
c = class(c,'mpfr');

end
