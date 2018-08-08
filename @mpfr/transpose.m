function a = transpose(a)
% TRANSPOSE  a.'
%
%  c = a.'
%

% written  07.11.2011     T.Xu

a_d = lin2cellarray(a).';
[a.d,a.d_end] = cell2linarray(a_d, []);

a.prec = a.prec.';
a.sign = a.sign.';
a.exp = a.exp.';

end
