function tests(m,n,prec)

t=zeros(12,1);
for i=1:n
	A1=rand(m)-.5;
	A2=rand(m)-.5;
if (n <=200)
	B1=sym(A1);
	B2=sym(A2);
end
	if (nargin==3)
		C1=mpfr(A1,prec);
		C2=mpfr(A2,prec);
	else 
		C1=mpfr(A1);
		C2=mpfr(A2);
	end

	j=1;

	% addition
	tic; 
	Ap=A1+A2; 
	t(j)=t(j)+toc*1000; 
	j = j+1;
	tic; 
	if (n <=200)
		Bp=B1+B2; 
		t(j)=t(j)+toc*1000; 
	end
	j = j+1;
	tic; 
	Cp=C1+C2; 
	t(j)=t(j)+toc*1000; 
	j = j+1;

	% subtraktion
	tic; 
	Am=A1-A2; 
	t(j)=t(j)+toc*1000; 
	j = j+1; 
	tic; 
	if (n <=200)
		Bm=B1-B2; 
		t(j)=t(j)+toc*1000; 
		j = j+1;
	end
	tic; 
	Cm=C1-C2; 
	t(j)=t(j)+toc*1000; 
	j = j+1;

	% punktweise multiplikation
	tic; 
	At=A1.*A2; 
	t(j)=t(j)+toc*1000; 
	j = j+1;
	tic; 
	if (n <=200)
		Bt=B1.*B2; 
		t(j)=t(j)+toc*1000; 
	end
	j = j+1;
	tic; 
	Ct=C1.*C2; 
	t(j)=t(j)+toc*1000; 
	j = j+1;

	%punktweise division
	tic; 
	Ad=A1./A2; 
	t(j)=t(j)+toc*1000; 
	j = j+1;
	tic; 
	if (n <=200)
		Bd=B1./B2; 
		t(j)=t(j)+toc*1000; 
	end
	j = j+1;
	tic; 
	Cd=C1./C2; 
	t(j)=t(j)+toc*1000; 
	j = j+1;
end

t=t./n;
if (n <=200)
	fprintf('(ms) matlab \t symb   \t mpfr   \t mpfr:matlab\t mpfr:symb  \n');
	fprintf(' +   %.3f   \t %.3f   \t %.3f   \t %.0f : 1  \t 1 : %.0f \n',t(1),t(2),t(3),t(3)/t(1),t(2)/t(3));
	fprintf(' -   %.3f   \t %.3f   \t %.3f   \t %.0f : 1  \t 1 : %.0f \n',t(4),t(5),t(6),t(6)/t(4),t(5)/t(6));
	fprintf(' .*  %.3f   \t %.3f   \t %.3f   \t %.0f : 1  \t 1 : %.0f \n',t(7),t(8),t(9),t(9)/t(7),t(8)/t(9));
	fprintf(' ./  %.3f   \t %.3f   \t %.3f   \t %.0f : 1  \t 1 : %.0f \n',t(10),t(11),t(12),t(12)/t(10),t(11)/t(12));
else
	fprint('symbolisch wird nicht mehr berechnet\n');
	fprintf('(ms) matlab \t mpfr   \t mpfr:matlab\n');
	fprintf(' +   %.3f   \t %.3f   \t %.0f : 1  \n',t(1),t(3),t(3)/t(1));
	fprintf(' -   %.3f   \t %.3f   \t %.0f : 1  \n',t(4),t(6),t(6)/t(4));
	fprintf(' .*  %.3f   \t %.3f   \t %.0f : 1  \n',t(7),t(9),t(9)/t(7));
	fprintf(' ./  %.3f   \t %.3f   \t %.0f : 1  \n',t(10),t(12),t(12)/t(10));
end
end

