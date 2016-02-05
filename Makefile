MAIN=main

pdf: include.tex
	latexmk -pdf $(MAIN)

all: pdf
	make -C code/programs

check:
	biber --tool -V bibliography/*.bib

lint:
	biber --tool bibliography/biblio.bib --output-fieldcase=lower --isbn-normalise
	mv bibliography/biblio_bibertool.bib bibliography/biblio.bib

#For compatibility with Authorea.com
include.tex: layout.md
	cut -f1 -d. layout.md | sed 's/^/\\input\{/' | sed 's/$$/\}/' > include.tex

clean:
	rm -vf *.bbl *.blg *.aux *.fls *.fdb_latexmk *.log *.out *.toc $(MAIN).pdf include.tex

