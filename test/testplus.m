function testplus(m,n,prec)
t=zeros(3,1);
for i=1:n
	A1=rand(m)-0.5; A2=rand(m)-0.5; B1=sym(A1); B2=sym(A2);
	if (nargin==3)
		C1=mpfr(A1,prec); C2=mpfr(A2,prec);
	else 
		C1=mpfr(A1); C2=mpfr(A2);
	end
	tic; Ap=A1+A2; t(1)=t(1)+toc*1000;
	tic; Bp=B1+B2; t(2)=t(2)+toc*1000;
	tic; Cp=C1+C2; t(3)=t(3)+toc*1000;
end
t = t./n;
fprintf('(ms) matlab\t symb  \t mpfr  \t mpfr:matlab\t mpfr:symb\n');
fprintf(' +   %.3f  \t %.3f  \t %.3f  \t %.0f:1  \t 1:%.0f \n', t(1),t(2),t(3),t(3)/t(1),t(2)/t(3));
end

