function c = sub(a,b)
%MINUS         Implements  a + b  for mpfr
%
% written  07.11.2011     T.Xu

% MPFR-functions for subtraction
%
% mpfr-mpfr:   int mpfr_sub (mpfr_t rop, mpfr_t op1, mpfr_t op2, mpfr_rnd_t rnd)
% mpfr-double: int mpfr_sub_d (mpfr_t rop, mpfr_t op1, double op2, mpfr_rnd_t rnd)
% double-mpfr: int mpfr_d_sub (mpfr_t rop, double op1, mpfr_t op2, mpfr_rnd_t rnd)
%
% result: rop = rop1 - rop2 

SUB = 1;
SUB_D = 5;
D_SUB = 8;

sizetest(a,b);
rnd = mx_mpfr_getround(getround());
if isa(a,'double')     
    c = mx_mpfr_elementals(b,a,rnd, D_SUB); % c := a - b 
elseif isa(b,'double')
    c = mx_mpfr_elementals(a,b,rnd, SUB_D); % c := a - b    
else
	if  ~isa(a,'mpfr')
		a = mpfr(a);
	elseif ~isa(b,'mpfr')
		b = mpfr(b);
	end
    c = mx_mpfr_elementals(a,b,rnd, SUB); % c := a - b 
end
c = class(c,'mpfr');



