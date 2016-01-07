MAIN=main

pdf: include.tex
	latexmk -pdf $(MAIN)

include.tex: layout.md
	cut -f1 -d. layout.md | sed 's/^/\\input\{/' | sed 's/$$/\}/' > include.tex

clean:
	rm -vf *.bbl *.blg *.aux *.fls *.fdb_latexmk *.log *.out *.toc $(MAIN).pdf include.tex

