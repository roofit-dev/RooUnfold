RooUnfold
=========

RooUnfold is a framework for unfolding (AKA "deconvolution" or
"unsmearing").  It currently implements several methods: iterative
(Bayes), singular value decomposition (SVD), unregularised matrix
inversion, bin-by-bin (simple correction factors), and an interface to
ROOT's TUnfold.  It can be used from the ROOT prompt, or linked
against the ROOT libraries. It can also be used from pyROOT.

For more documentation, consult the [webpage](http://hepunx.rl.ac.uk/~adye/software/unfold/RooUnfold.html).

RooUnfold was written by Tim Adye, Kerstin Tackmann, and Fergus Wilson.

Building
--------

Use GNU `make`. Just type

    make

to build the RooUnfold shared library.

Alternatively, you can use `cmake`

    mkdir build
    cd build
    cmake ..
    make -j4

Running
--------

In an interactive ROOT shell, `RooUnfoldExample.cxx` makes a simple test of RooUnfold.

    % root
    root [0] .L examples/RooUnfoldExample.cxx
    root [1] RooUnfoldExample()

You can also use python

    % python examples/RooUnfoldExample.py
  

See the web page for more examples and documentation.
