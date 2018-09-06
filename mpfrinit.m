function mpfrinit ()
% MPFRINIT Compilation of the MPFR MEX-interface.
%
%    This function requires INTLAB to be started.
%
% See also startintlab.

% written  07/11/2011     T. Xu
% modified 14/06/2018     K.T. Ohlhus  overhaul the compiling process
% modified 06/09/2018     K.T. Ohlhus  specialize for INTLAB

global INTLAB_CONST
MPFR_PATH = [INTLAB_CONST.INTLABPATH, 'mpfr', filesep];

if ispc()
  mex_compile = @(f) eval (['mex -I"', MPFR_PATH, 'vendor" ', f, ...
    '  "', MPFR_PATH, 'vendor', filesep, 'mpfr.lib"']);
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
mex_compile ('mx_mpfr_sample.c');

warning (warn_state);

cd (old_dir);
addpath (MPFR_PATH, [MPFR_PATH, filesep, 'test']);

end
