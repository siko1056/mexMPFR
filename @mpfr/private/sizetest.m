function [ output_args ] = sizetest( a,b )
%SIZETEST compares the sizes of arrays a, b, where one of rhem has mpfr
% class and the other mpfr or double class. If the sizes do not agree, then
% an error message is shown. 


% written  19.05.2011     F. Bünger 

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

if n_a~=1 && n_b~=1 && any(s_a~=s_b)
    error(['inner dimensions of ', inputname(1),' and ',inputname(2),' do not fit to each other.']);
end


