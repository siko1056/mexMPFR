function c = mtimes(a, b)
% MTIMES  Matrix multiplication 'a * b'.
%

if ~isa(a,'mpfr')
  s_a = size(a); n_a = numel(a);
else
  s_a = size(a.sign); n_a = numel(a.sign);
end

if ~isa(b,'mpfr')
  s_b = size(b); n_b = numel(b);
else
  s_b = size(b.sign); n_b = numel(b.sign);
end

if n_a~=1 && n_b~=1 && s_a(2)~=s_b(1)
  error(['inner dimensions of ', inputname(1), ' and ', inputname(2), ...
    ' do not fit to each other.']);
end

if (n_a == 1 || n_b == 1)
  c = times(a, b);
else
  % converting matrices to mpfr if they are not
  % - TODO: implement mpfr * double and double * mpfr
  if isa(a,'mpfr') && isa(b,'mpfr')
    a=a.';
  elseif isa (a, 'double')
    a=mpfr(a');
  elseif isa (b, 'double')
    a=a.';
    b=mpfr(b);
  else
    error ('multiplication  %s .* %s  is not supported.', class(a), class(b));
  end
  
  rnd = mx_mpfr_getround(getround());
  
  c = mx_mpfr_mmul(a,b,rnd);
end

c = class (c, 'mpfr');

end
