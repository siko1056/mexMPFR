function c = mpfr(x, prec, base)
% MPFR Constructor.
%
% The definition of the main mpfr-structure is
%
% typedef struct {
%   mpfr_prec_t  _mpfr_prec; /* */
%   mpfr_sign_t  _mpfr_sign;
%   mpfr_exp_t   _mpfr_exp;
%   mp_limb_t   *_mpfr_d;
% } __mpfr_struct;
%
% The represented number is
%
%    _sign * (_d[k-1]/B + _d[k-2]/B^2 + ... +_d[0]/B^k) * 2^_exp
%
% where `k = ceil(_mp_prec/GMP_NUMB_BITS)` and `B = 2^GMP_NUMB_BITS`.
%
% For the msb (most significant bit) normalized representation, we must have
% `_d[k-1] >= B/2`, unless the number is singular.
%
% We must also have the last `k*GMP_NUMB_BITS - _prec bits` set to zero.
%
%
% In Matlab a number of this format is stored in a structure of class
% mpfr_t with the following components
%   .prec   : Precision (int)
%   .sign   : Sign      (int)
%   .exp    : Exponent  (int)
%   .d      : significands  (Array of limbs/int)
%

% written  07.11.2011     T.Xu

if ((nargin > 3) || isempty(x))
  error('invalid call of mpfr constructor')
end
rnd = mx_mpfr_getround(getround());

switch (nargin)
  case 1 % prec, base not specified
    prec = mx_mpfr_get_default_prec();
    base = 10; % default base is 10 => decimal representation
  case 2 % base not specified
    base = 10;
  case 3
    if isempty(prec)
      prec = mx_mpfr_get_default_prec();
    end
    if ~isnumeric(base) || round(base)~=base || base<2 || base>62
      error(['invalid call of mpfr constructor with wrong format of ', ...
        'struct input. Base must be an integer from the interval [2,62]. ']);
    end
  otherwise
    error('invalid call of mpfr constructor')
end

if (islogical (x))
  x = double(x);
end

switch class(x)
  case 'mpfr'      % 1 parameter, interval
    c = x;
    return
  case 'double'
    if isreal(x)
      c = mx_mpfr_set_d(x,rnd,prec);
    else
      error('invalid call of mpfr constructor with non-real number input')
    end
  case 'char'
    % predefined math constants
    switch lower(x)
      case 'log2'
        % 0.693147180559945309417232121458176568075500134360 ...
        const_nr = 0;
      case 'pi'
        % 3.1415926535897932384626433832795028841971693993751058209749445 ...
        const_nr = 1;
      case 'euler' % Euler-Mascheroni-Konstante
        % 0.57721 56649 01532 86060 65120 90082 40243 10421 59335 93992 35988
        %   05767 23488 48677 26777 66467 09369 47063 29174 67495.
        const_nr = 2;
      case 'catalan'
        % 0.915965594177219015054603514932384110774 ...
        const_nr = 3;
      otherwise
        error('invalid call of mpfr constructor with unknown character input.')
    end
    c = mx_mpfr_constants(rnd, prec, const_nr);
  case 'cell'
    % Input in form of numeric strings.
    % Example:
    %
    %  x = {'1.1587898', '1.2', '1.3'; '2.1', '2.2', '2.385693456'}
    %
    %  produces the 2x3 Matrix
    %
    %        1.1587898    1.2     1.3
    %        2.1          2.2     2.385693456
    
    for i=1:numel(x)
      if ~ischar(x{i})
        error(['invalid call of mpfr constructor: %d-th component of ', ...
          'input is not a string.'], i);
      end
    end
    c = mx_mpfr_set_string(x,base,rnd,prec);
  otherwise
    error('invalid call of mpfr constructor')
end
c = class(c,'mpfr');

end
