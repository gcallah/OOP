#!/bin/sh
UTL_DIR=./utils
TEMPL_DIR=templates

$UTL_DIR/create_menu.py $TEMPL_DIR/course_struct.txt $TEMPL_DIR/navbar.txt
$UTL_DIR/create_pages.py $TEMPL_DIR/course_struct.txt $UTL_DIR/templates/template.ptml
make local

