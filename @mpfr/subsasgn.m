function a = subsasgn(a,s,b)
%SUBSASGN     Implements subscripted assignments for mpfr

% written  07.11.2011     T.Xus

a = mpfr(a);
b = mpfr(b);

a_d = lin2cellarray(a);
b_d = lin2cellarray(b);
a_d = subsasgn(a_d,s,b_d);
[a.d,a.d_end] = cell2linarray(a_d,[]); 

a.prec = subsasgn(a.prec,s,b.prec);
a.sign = subsasgn(a.sign,s,b.sign);
a.exp = subsasgn(a.exp,s,b.exp);

