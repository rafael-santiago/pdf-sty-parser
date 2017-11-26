/*
 *                                                 Copyright (C) 2017
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#include "ctx_tests.h"
#include <pdf_sty_ctx.h>
#include <string.h>

CUTE_TEST_CASE(add_word_to_pdf_sty_word_tests)
    pdf_sty_word_ctx *words = NULL, *words_tail = NULL, *head = NULL;

    words = add_word_to_pdf_sty_word(words, "foo", 3, 1, &words_tail);
    CUTE_ASSERT(words != NULL);
    head = words;
    CUTE_ASSERT(words_tail != NULL && words_tail->next == NULL);
    words = add_word_to_pdf_sty_word(words, "foo", 3, 1, &words_tail);
    CUTE_ASSERT(words == head);
    CUTE_ASSERT(words_tail != NULL && words_tail->next == NULL);
    words = add_word_to_pdf_sty_word(words, "foo", 3, 1, &words_tail);
    CUTE_ASSERT(words == head);
    CUTE_ASSERT(words_tail != NULL && words_tail->next == NULL);
    words = add_word_to_pdf_sty_word(words, "foo", 3, 1, &words_tail);
    CUTE_ASSERT(words == head);
    CUTE_ASSERT(words_tail != NULL && words_tail->next == NULL);

    CUTE_ASSERT(words->data != NULL);
    CUTE_ASSERT(strcmp(words->data, "foo") == 0);
    CUTE_ASSERT(words->data_size == 3);
    CUTE_ASSERT(words->page == 1);
    CUTE_ASSERT(words->freq == 4);
    CUTE_ASSERT(words->next == NULL);

    words = add_word_to_pdf_sty_word(words, "barbaz", 6, 3, &words_tail);
    CUTE_ASSERT(words == head);
    CUTE_ASSERT(words_tail != NULL && words_tail->next == NULL);

    CUTE_ASSERT(words->next != NULL);
    CUTE_ASSERT(words->next->data != NULL);
    CUTE_ASSERT(strcmp(words->next->data, "barbaz") == 0);
    CUTE_ASSERT(words->next->data_size == 6);
    CUTE_ASSERT(words->next->page == 3);
    CUTE_ASSERT(words->next->freq == 1);
    CUTE_ASSERT(words->next->next == NULL);

    del_pdf_sty_word(words); // INFO(Rafael): The leak check system will detect and complain
                             //               if this context were not correctly freed.
CUTE_TEST_CASE_END
