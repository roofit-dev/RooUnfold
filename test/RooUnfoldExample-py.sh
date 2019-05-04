#!/bin/bash
outfile=RooUnfoldExample.py.ref
python -u examples/RooUnfoldExample.py > $outfile
bash ref/cleanup.sh $outfile
diff $outfile ref/$outfile
