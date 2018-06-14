function res = lin2cellarray( a )
% lin2cellarray      implements a conversion of a linear array of limbs
%                    to a multilinear cell array

% written  08.06.2011     F. Buenger

l = 1;
u = a.d_end(1)+1;
r = cell(size(a.prec));
r(1)={a.d(l:u)};
for k=2:numel(a.d_end)  
  l = u+1;
  u = a.d_end(k)+1;
  r(k)={a.d(l:u)};    
end
res = r;
