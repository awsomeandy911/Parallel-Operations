# NOTE: you must have rubber installed to run this makefile

TEX = writeup.tex
PLOTS = charts.py

all: plots writeup movepdf clean ## Compile write up, move it, and remove output files

plots: $(PLOTS)
	python3 $(PLOTS)

writeup: $(TEX) ## Generate writeup pdf using LaTeX and move it to deliverables directory
	rubber --pdf $(TEX)

movepdf: ## Moves the output pdf to the /deliverables/ directory.
	mv writeup.pdf ../DELIVERABLES/writeup.pdf

clean: ## Remove output files (not including final PDF)
	rubber --clean $(TEX)
	rm *.png