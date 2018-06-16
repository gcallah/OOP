# Need to export as ENV var
export TEMPLATE_DIR = templates
export QUIZ_DIR = quizzes
PTML_DIR = html_src
UTILS_DIR = utils

INCS = $(TEMPLATE_DIR)/navbar.txt $(TEMPLATE_DIR)/head.txt

HTMLFILES = $(shell ls $(PTML_DIR)/*.ptml | sed -e 's/.ptml/.html/' | sed -e 's/html_src\///')

%.html: $(PTML_DIR)/%.ptml $(INCS)
	python3 $(UTILS_DIR)/html_checker.py $< 
	$(UTILS_DIR)/html_include.awk <$< >$@
	git add $@

website: $(INCS) $(HTMLFILES)
	-git commit -a 
	git pull origin master
	git push origin master

local: $(HTMLFILES)

clean:
	touch $(PTML_DIR)/*.ptml; make local

menu:
	$(UTILS_DIR)/create_menu.py $(TEMPLATE_DIR)/course_struct.txt $(TEMPLATE_DIR)/navbar.txt

ptml_files:
	$(UTILS_DIR)/create_pages.py $(TEMPLATE_DIR)/course_struct.txt $(UTILS_DIR)/templates/template.ptml $(PTML_DIR)

course_struct: menu html_files
	git add $(PTML_DIR)/*.ptml
	make local
