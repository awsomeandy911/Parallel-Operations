This is the directory where the source for our write up will live.

Make sure you have rubber installed by running the following in your linux shell:

> sudo apt-get update
> sudo apt install rubber

The makefile will automatically generate the PDF using the TEX source file
and any additional files within this source_writeup directory.

Do so by running the following from within the /source_writeup/ directory:

> make



Construct just the plots (and do not remove them automatically, like above) by running:

> make plots

This will put the plots into this directory as png files for downloading or importing into latex.
NOTE: The main 'make' must have already been run to generate the output CSV files, which are parsed by 'charts.py'