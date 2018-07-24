# Need to export as ENV var
export TEMPLATE_DIR = templates
export QUIZ_DIR = quizzes
PTML_DIR = html_src
UTILS_DIR = utils

INCS = $(TEMPLATE_DIR)/navbar.txt $(TEMPLATE_DIR)/head.txt

HTMLFILES = $(shell ls $(PTML_DIR)/*.ptml | sed -e 's/.ptml/.html/' | sed -e 's/html_src\///')

%.html: $(PTML_DIR)/%.ptml $(INCS)
	python3 $(UTILS_DIR)/html_checker.py $< 
	python3 $(UTILS_DIR)/url_checker.py $< https://gcallah.github.io/OOP/
	$(UTILS_DIR)/html_include.awk <$< >$@
	git add $@

website: $(INCS) $(HTMLFILES)
	-git commit -a 
	git pull origin master
	git push origin master

local: $(HTMLFILES)

clean:
	touch $(PTML_DIR)/*.ptml; make local

quizzes:
	cd $(QUIZ_DIR); make all; cd -

# handcraft which files you want in the test:
test:
	cd $(QUIZ_DIR); make tests; cd -
	cat $(QUIZ_DIR)/quiz2.thtm $(QUIZ_DIR)/quiz3.thtm $(QUIZ_DIR)/quiz4.thtm $(QUIZ_DIR)/quiz5.thtm $(QUIZ_DIR)/quiz6.thtm $(QUIZ_DIR)/quiz7.thtm $(QUIZ_DIR)/quiz8.thtm > $(QUIZ_DIR)/vivek_akshay.html

menu:
	$(UTILS_DIR)/create_menu.py $(TEMPLATE_DIR)/course_struct.txt $(TEMPLATE_DIR)/navbar.txt

ptml_files:
	$(UTILS_DIR)/create_pages.py $(TEMPLATE_DIR)/course_struct.txt $(UTILS_DIR)/templates/template.ptml $(PTML_DIR)

course_struct: menu html_files
	git add $(PTML_DIR)/*.ptml
	make local
