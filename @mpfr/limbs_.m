function res = limbs_(x)
% LIMBS_  Return the 'limbs' field of MPFR object.
%

% written  07.11.2011     T.Xu

res = cell(size(x.sign));
limb = x.d; %limb array
idx = x.d_end; % limb indices
l = 1;
u = idx(1)+1;
res{1} = limb(l:u)';
for k = 2:numel(x.sign)
  l = idx(k-1)+2;
  u = idx(k)+1;
  res{k} = limb(l:u)';
end

end
