function res = ne(a,b)
%NE           Implements  a ~= b  elementwise for mpfr variables
%
% a and b must be either both real or both complex
%

% written  07.11.2011     T.Xu

res = ~(a==b);


