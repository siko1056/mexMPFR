function a = subsref(a,s)
% SUBSREF  Subscripted reference.
%

% written  07.11.2011     T.Xu

a_d = lin2cellarray(a);
a_d = subsref(a_d,s);
[a.d,a.d_end] = cell2linarray(a_d, []);
a.prec = subsref(a.prec,s);
a.sign = subsref(a.sign,s);
a.exp = subsref(a.exp,s);

end
