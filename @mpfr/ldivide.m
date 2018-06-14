function c = ldivide(a,b)
%LDIVIDE      elementwise left division a .\ b for mpfr
% written  07.11.2011     T.Xu

% entspricht b./a

c=rdivide(b,a);