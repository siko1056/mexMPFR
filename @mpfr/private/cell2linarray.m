function [d,d_end] = cell2linarray( a,n )
% cell2linarray      implements a conversion of a a multilinear cell array of limbs
%                    to a linear array of length n.

% written  08.06.2011     F. Buenger

d_end = zeros(size(a));
if ~isempty(n)
    d = zeros(n,1); 
end
d_end(1) = numel(a{1})-1; % decrement of 1, since the C-index is stored
l = 1;
u = d_end(1)+1;
d(l:u) = a{1};
for k = 2:numel(a)  
  d_end(k) = d_end(k-1)+numel(a{k});
  l = d_end(k-1)+2;
  u = d_end(k)+1;
  d(l:u) = a{k};    
end

% In Matlab adressing colum vectors is faster then adressing row vectors.
% In C it is the other way round.

d = d'; 

