#!/bin/sh
UTL_DIR=./utils
TEMPL_DIR=templates
PTML_DIR=html_src

$UTL_DIR/create_menu.py $TEMPL_DIR/course_struct.txt $TEMPL_DIR/navbar.txt
$UTL_DIR/create_pages.py $TEMPL_DIR/course_struct.txt $PTML_DIR
$UTL_DIR/templates/template.ptml $PTML_DIR
git add $PTML_DIR/*.ptml
make local

