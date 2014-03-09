# GNU Radio sink block for the DATV-Express hardware

The block requires GNU Radio 3.7.2 or later and can be used in C++, Python
and GRC applications.

## Installation

    git clone https://github.com/csete/gr-datvexpress.git
    cd gr-datvexpress
    mkdir build
    cd build
    cmake ..
    make
    make install

Keep the build directory around; you may need it if you want to uninstall
later.

## Usage

You can test the DATV-Express sink block in the gnuradio-companion. The block
is located under Sinks. There is a simple tone generator example in
PREFIX/share/gr-datvexpress/examples/ where PREFIX is where gr-datvexpress got
installed (/usr/local by default).

Note that the firmware files (datvexpress.ihx and datvexpress.rbf) must be
located in the working directory. You can create symlinks if you already have
them installed elsewhere.

Feel free to submit other examples or applications if you want them included
in this package.

## Terms and conditions

The gr-datvexpress block was written by Alexandru Csete OZ9AEC and is licensed
under the GNU General Public license v# or later (same license as GNU Radio).

The library includes code from the official DATV-Express software. This code
is located in lib/hw/ and was written by Charles Brain G4GUO. It is licensed
under the  Simplified BSD License.
