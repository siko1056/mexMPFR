function c = minus(a, b)
% MINUS  Elementwise subtraction.
%
% written  07.11.2011     T.Xu

SUB = 1;
SUB_D = 5;
D_SUB = 8;

sizetest(a, b);
rnd = mx_mpfr_getround(getround());
if isa(a,'double')     
    c = mx_mpfr_elementals(b, a, rnd, D_SUB); % c := a - b 
elseif isa(b,'double')
    c = mx_mpfr_elementals(a, b, rnd, SUB_D); % c := a - b    
else
	if ~isa(a,'mpfr')
		a = mpfr(a);
	elseif ~isa(b,'mpfr')
		b = mpfr(b);
	end
    c = mx_mpfr_elementals(a, b, rnd, SUB); % c := a - b 
end
c = class(c,'mpfr');

end
