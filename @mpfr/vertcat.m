function c = vertcat(varargin)
%VERTCAT      Implements  [a(1) ; a(2) ...]  for mpfr

% written  07.11.2011     T.Xu

  c = mpfr(varargin{1});
  c_d = lin2cellarray(c);    
  d_len = length(c.d);
  
  for i=2:length(varargin)
    a = mpfr(varargin{i});    
    
    c.prec = [ c.prec ; a.prec ];
    c.sign = [ c.sign ; a.sign ];
    c.exp = [ c.exp ; a.exp ];
    c_d = [c_d; lin2cellarray(a)];
    d_len = d_len + length(a.d);
  end
  [c.d,c.d_end] = cell2linarray(c_d,d_len);      
