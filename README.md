# mexMPFR

A [MATLAB][] [MEX-Interface][] for the [GNU MPFR][] Library.

This work and all included libraries are licensed under the terms of the [LGPLv3][].


## Build requirements

The Matlab/Octave toolbox [INTLAB][] is required and in order to build
MEX-files in [MATLAB][], a [supported compiler][MATLAB compiler]:

- Microsoft Windows:
  - [Microsoft Visual C++ 2017][MSVC] (Community, Professional, or Enterprise)
  - The [GNU MPFR][] and [MPIR][] libraries are accessible by the precompiled
    static library file `mpfr.lib` by [Brian Gladman][], located in the
    `vendor` directory.

- GNU/Linux:
  - [GNU GCC][] and the development libraries [libgmp-dev][] and
    [libmpfr-dev][].

    For the [Ubuntu][] or [Debian][] Linux distribution, all dependencies
    are easily obtained by running the command:

        sudo apt-get install gcc libgmp-dev libmpfr-dev

    For other Linux distributions the installation command and the package
    names might be slightly different.

After the compiler installation verify from the [MATLAB][] command prompt,
that the compiler is recognized correctly:

    mex -setup



## Building the MEX-Interface for GNU MPFR

In [MATLAB][] one has to set the current directory to the root directory of
this project.  Then in the command prompt execute

    startup

to invoke the compilation process.


[MATLAB]: https://www.mathworks.com/products/matlab.html
[MEX-Interface]: https://www.mathworks.com/help/matlab/mex-library.html
[MATLAB compiler]: https://www.mathworks.com/support/compilers.html

[Debian]: https://www.debian.org/
[Ubuntu]: https://www.ubuntu.com/
[GNU GCC]: https://gcc.gnu.org/
[libgmp-dev]: https://packages.debian.org/stretch/libgmp-dev
[libmpfr-dev]: https://packages.debian.org/stretch/libmpfr-dev

[MPIR]: http://mpir.org/
[GNU GMP]: https://gmplib.org/
[GNU MPFR]: https://www.mpfr.org/

[INTLAB]: http://www.ti3.tu-harburg.de/rump/intlab/

[Brian Gladman]: http://brg.a2hosted.com//oldsite/computing/gmp4win.php

[MSVC]: https://www.visualstudio.com/downloads/

[LGPLv3]: https://www.gnu.org/licenses/lgpl-3.0.en.html
