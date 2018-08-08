function startup (op)
% STARTUP Compilation of all MEX-functions of the Matlab-MPFR interface.

% written  07/11/2011     T. Xu
% modified 14/06/2018     K.T. Ohlhus  overhaul the compiling process

if (exist ('isintval', 'file') ~= 2)
  INTLAB_STARTUP = [pwd(), filesep(), 'vendor', filesep(), 'intlab', ...
    filesep(), 'startintlab.m'];
  if (exist (INTLAB_STARTUP, 'file') == 2)
    run(INTLAB_STARTUP)
  else
    error('MEXMPFR:startup:startintlab', ...
      'Unable to find and start INTLAB.');
  end
end

% Optionally format source code using "astyle" with Linux
if (isunix () && (nargin > 0) && strcmpi (op, 'format'))
  system (['find @mpfr/private/ -name "*.h" -or -name "*.c" ', ...
    '| xargs astyle --style=google --indent=spaces=2 --max-code-length=80', ...
    '--verbose --convert-tabs && rm -f *.orig *.mexa64']);
end

if ispc()
  mex_compile = @(f) eval (['mex -I"..\..\vendor" ', f, ...
    ' ..\..\vendor\mpfr.lib']);
elseif isunix()
  mex_compile = @(f) eval (['mex CFLAGS=''$CFLAGS -Wall -Wextra'' ', f, ...
    ' -lmpfr']);
else
  error('MEXMPFR:startup:badSystem', 'Your system is not supported.');
end

old_dir = cd (['@mpfr', filesep(), 'private']);
warn_state = warning ('off', 'MATLAB:mex:GccVersion_link');

% rounding
mex_compile ('mx_mpfr_getround.c');

% get defaults
mex_compile ('mx_mpfr_get_default_prec.c');
mex_compile ('mx_mpfr_get_default_rounding_mode.c');

% mathematical constants
mex_compile ('mx_mpfr_constants.c mexmpfr.c');

% set
mex_compile ('mx_mpfr_set_d.c mexmpfr.c');
mex_compile ('mx_mpfr_set_string.c mexmpfr.c');

% display
mex_compile ('mx_display.c mexmpfr.c');

% basic operations
mex_compile ('mx_mpfr_elementals.c mexmpfr.c');

% matrix mul
mex_compile ('mx_mpfr_mmul.c mexmpfr.c');

% comparsion operations
mex_compile ('mx_mpfr_compare.c mexmpfr.c');

% conversion
mex_compile ('mx_mpfr_to_double.c mexmpfr.c');

cd (old_dir);
old_dir = cd ('test');

% version info
mex_compile ('mx_mpfr_version_info.c');

warning (warn_state);

cd (old_dir);
addpath(pwd(), [pwd(), filesep(), 'test']);

end
