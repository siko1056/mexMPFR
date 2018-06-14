function test1(n,prec)
A=2*(rand(n,1)-0.5);
for i=1:n
	if nargin == 2
		diff=A(i)-double(mpfr(A(i),prec));
	else 
		diff=A(i)-double(mpfr(A(i)));
	end
    if(diff~=0)
        error('difference not null.');
    end
end
str = fprintf('all transformations were correct.\n');
end