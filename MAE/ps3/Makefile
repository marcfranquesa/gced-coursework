DELIVERABLE := 2a

NAME := marcfranquesamones
TITLE := $(NAME)_E$(DELIVERABLE)
TEX := pdflatex
BIB := bibtex
FILE := main

all: pdf

del: clean pdf zip
	@mkdir $(TITLE)
	@mv main.pdf $(TITLE)/$(TITLE).pdf
	@mv $(TITLE).zip $(TITLE)/
	@rm -rf ${XDG_DESKTOP_DIR}/$(TITLE)
	@mv $(TITLE) ${XDG_DESKTOP_DIR}

pdf: *.tex
	$(TEX) $(FILE)

zip:
	@zip -rj $(TITLE).zip code/*.m

clean:
	@rm -f *.aux *.fls *.fdb_latexmk *.fls *.log *.out *.toc *.bbl *.bcf *.xml *.gz *blx.bib *blg
	@rm -rf *.zip main.pdf $(TITLE) ${XDG_DESKTOP_DIR}/$(TITLE)
