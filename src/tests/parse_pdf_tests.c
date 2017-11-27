/*
 *                                                 Copyright (C) 2017
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#include "parse_pdf_tests.h"
#include <pdf_sty_parser.h>
#include <pdf_sty_ctx.h>
#include <string.h>

CUTE_TEST_CASE(pdf_sty_parse_pdf_tests)
    pdf_sty_word_ctx *words = NULL, *wp;

    CUTE_ASSERT(pdf_sty_parse_pdf(NULL) == NULL);

    words = pdf_sty_parse_pdf("test_data/blah.pdf");
    CUTE_ASSERT(words != NULL);

    wp = words;

    CUTE_ASSERT(wp->page == 1);
    CUTE_ASSERT(strcmp(wp->data, "FOOBAR") == 0);
    CUTE_ASSERT(wp->freq == 2);

    wp = wp->next;

    CUTE_ASSERT(wp->page == 2);
    CUTE_ASSERT(strcmp(wp->data, "FOOBAR") == 0);
    CUTE_ASSERT(wp->freq == 1);

    wp = wp->next;

    CUTE_ASSERT(wp->page == 3);
    CUTE_ASSERT(strcmp(wp->data, "WORKS") == 0);
    CUTE_ASSERT(wp->freq == 1);

    wp = wp->next;

    CUTE_ASSERT(wp == NULL);

    del_pdf_sty_word(words);
CUTE_TEST_CASE_END
