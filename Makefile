MAIN=main

pdf: include.tex
	latexmk -halt-on-error -pdf $(MAIN)

all: pdf
	make -C code/programs

check:
	chktex -n1 -n2 -n8 -n11 -n12 -n13 -n14 -n26 -n34 -n33 -n36 -n40 main
	biber --tool -V bibliography/biblio.bib
	rm -f bibliography/biblio_bibertool.bib

lint:
	biber --tool bibliography/biblio.bib --output-fieldcase=lower --isbn-normalise
	mv bibliography/biblio_bibertool.bib bibliography/biblio.bib

#For compatibility with Authorea.com
include.tex: layout.md
	cut -f1 -d. layout.md | sed 's/^/\\input\{/' | sed 's/$$/\}/' > include.tex

clean:
	rm -vf *.bbl *.blg *.aux *.fls *.fdb_latexmk *.log *.out *.toc $(MAIN).pdf include.tex

