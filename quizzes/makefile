QINCS = $(shell ls quiz*.txt | sed -e 's/txt/qhtm/g')
TEST = $(shell ls quiz*.txt | sed -e 's/txt/thtm/g')
QUIZZES = $(shell ls quiz*.txt)

%.qhtm: %.txt
	../utils/quiz2html.py $< \# >$@
	git add $@

%.thtm: %.txt
	../utils/quiz2test.py $< \# >$@

all: $(QINCS)

tests: $(TEST)

clean:
	touch *.txt
