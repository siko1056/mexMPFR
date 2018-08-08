function testMPFR_conversion (testCase)
A = 2 * (rand (200, 1) - 0.5);
verifyEqual(testCase, double (mpfr (A)), A)
verifyEqual(testCase, double (mpfr (A, 54)), A)
end
