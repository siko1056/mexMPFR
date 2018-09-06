classdef mpfrArray < handle
  % MPFRARRAY create data for MPFR computations
  %
  %     M = mpfrArray( X ) copies the numeric data X to a MPFR object.  This
  %     data can be operated on using any function that supports mpfrArray
  %     objects.  See the INTLAB MPFR Toolbox documentation for a list of
  %     functions supported by mpfrArray.
  %
  %     The data X must be numeric (for example: single, double, int8, etc.)
  %     or logical, and your system must have sufficient free memory to store
  %     the data.  X must be full.
  %
  %     Use GATHER to copy mpfrArray data back to the local workspace.
  %
  %     Example:
  %     X = rand( 10, 'single' );
  %     M = mpfrArray( X );
  %     isequal( gather( M ), X )  % returns true
  %     M2 = M .* M                % use "times" method for mpfrArray objects
  %
  %     See also gather
  
  properties
    Property1
  end
  
  methods
    function obj = mpfrArray(X)
      %MPFRARRAY Constructor
      obj.Property1 = X;
    end
    
    function delete(obj)
      %DELETE Destructor
      disp('clear MPFR');
    end
  end
end

