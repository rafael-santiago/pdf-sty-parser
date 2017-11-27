/*
 *                                                 Copyright (C) 2017
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#include "pdftohtml_tests.h"
#include <pdf_sty_pdftohtml.h>
#include <pdf_sty_memory.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

CUTE_TEST_CASE(pdf_sty_pdftohtml_tests)
    char *data;
    size_t data_size;
    DIR *dir;
    size_t html_files_nr;
    struct dirent *dir_entry;

    CUTE_ASSERT(pdf_sty_pdftohtml(NULL, NULL) == NULL);
    CUTE_ASSERT(pdf_sty_pdftohtml(NULL, &data_size) == NULL);
    CUTE_ASSERT(pdf_sty_pdftohtml("test_data/blah.pdf", NULL) == NULL);

    data = pdf_sty_pdftohtml("test_data/blah.pdf", &data_size);

    CUTE_ASSERT(data != NULL);
    CUTE_ASSERT(data_size > 0);

    // INFO(Rafael): Now checking if the directory was really cleaned up.

    dir = opendir(".");
    CUTE_ASSERT(dir != NULL);

    html_files_nr = 0;
    while ((dir_entry = readdir(dir)) != 0) {
        if (strstr(dir_entry->d_name, ".html") != NULL) {
            html_files_nr++;
        }
    }

    CUTE_ASSERT(html_files_nr == 0);

    closedir(dir);
    pdf_sty_freeseg(data);
CUTE_TEST_CASE_END
