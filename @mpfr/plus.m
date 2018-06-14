function c = plus(a,b)
%PLUS         Implements  a + b  for mpfr
%
% written  07.11.2011     T.Xu

% MPFR-functions for addition
%
% mpfr+mpfr:   int mpfr_add (mpfr_t rop, mpfr_t op1, mpfr_t op2, mpfr_rnd_t rnd)
% mpfr+double: int mpfr_add_d (mpfr_t rop, mpfr_t op1, double op2, mpfr_rnd_t rnd)
%
% result: rop = rop1 + rop2 

ADD = 0;
ADD_D = 4;

sizetest(a,b);
rnd = mx_mpfr_getround(getround());
if isa(a,'double')     
    c = mx_mpfr_elementals(b,a,rnd, ADD_D); % c := b + a 
elseif isa(b,'double')
    c = mx_mpfr_elementals(a,b,rnd, ADD_D); % c := a + b   
else
	if  ~isa(a,'mpfr')
		a = mpfr(a);
	elseif ~isa(b,'mpfr')
		b = mpfr(b);
	end
    c = mx_mpfr_elementals(a,b,rnd, ADD); % c := a + b 
end
c = class(c,'mpfr');