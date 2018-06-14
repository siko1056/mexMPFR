function compares(a,b)
disp('comparing: ');display(a); disp(' and ');display(b); disp('-')
if eq(a,b) % a == b
	disp('a is equal to b');
end
if ne(a,b) % a ~= b
	disp('a is not equal to b');
end
if gt(a,b) % a > b
	disp('a is greater than b');
end
if lt(a,b) % a < b
	disp('a is lesser than b');
end
if ge(a,b) % a >= b
	disp('a is greater or equal to b');
end
if le(a,b) % a <= b
	disp('a is lesser or equal to b');
end