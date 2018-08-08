function c = rdivide(a,b)
% RDIVIDE  Elementwise right division 'a ./ b'.
%

% written  07.11.2011     T.Xu

DIV = 3;
DIV_D = 7;
D_DIV = 9;

sizetest(a,b);
rnd = mx_mpfr_getround(getround());
if isa(a,'double')
  c = mx_mpfr_elementals(b,a,rnd, D_DIV); % c := a ./ b
elseif isa(b,'double')
  c = mx_mpfr_elementals(a,b,rnd, DIV_D); % c := a ./ b
else
  if  ~isa(a,'mpfr')
    a = mpfr(a);
  elseif ~isa(b,'mpfr')
    b = mpfr(b);
  end
  c = mx_mpfr_elementals(a,b,rnd, DIV); % c := a ./ b
end
c = class(c,'mpfr');

end
