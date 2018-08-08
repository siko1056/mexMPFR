function a = uminus(a)
% UMINUS  Unary minus '-a'.
%

% written  07.11.2011     T.Xu

if mod(a.sign,2) == 1 %a is negative
  
  a.sign = a.sign - 1;
  
else %a is positive
  
  a.sign = a.sign + 1;
  
end

end
