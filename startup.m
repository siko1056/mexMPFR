%STARTUP      Dummy routine to call mex_config 
%
%

% written  07.11.2011   T.Xu
try 
	mex_config;
catch 
    cd ../..
end
