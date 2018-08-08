function tests = testMEXMPFR()
% TESTVSDP  Runs a testsuite for mexMPFR.
%
%   Example:
%
%       clc; table (runtests ('testMEXMPFR'))
%
%   See also mpfr.

% Copyright 2018 Kai T. Ohlhus (kai.ohlhus@tuhh.de)

tests = functiontests (localfunctions);
end

function testCONVERSION (testCase)
testMPFR_conversion (testCase);
end
