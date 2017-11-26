/*
 *                                                 Copyright (C) 2017
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#include "parse_utils_tests.h"
#include <pdf_sty_parse_utils.h>
#include <pdf_sty_memory.h>
#include <stdlib.h>
#include <string.h>

CUTE_TEST_CASE(pdf_sty_case_folding_tests)
    struct case_folding_tests {
        char *original;
        char *expected;
    };

    struct case_folding_tests test_vector[] = {
        { "foo", "FOO" },
        { "fOobaR", "FOOBAR" },
        { "após", "APÓS" },
        { "pêssego", "PÊSSEGO" }
    };

    size_t test_vector_nr = sizeof(test_vector) / sizeof(test_vector[0]), t;
    char *test_data = NULL, *h;
    size_t test_data_size;

    for (t = 0; t < test_vector_nr; t++) {
        test_data_size = strlen(test_vector[t].original);
        test_data = (char *) pdf_sty_newseg(test_data_size + 1);
        h = test_data;
        memset(test_data, 0, test_data_size + 1);
        memcpy(test_data, test_vector[t].original, test_data_size);
        test_data = pdf_sty_case_folding(test_data, test_data_size);
        CUTE_ASSERT(test_data == h);
        CUTE_ASSERT(strcmp(test_data, test_vector[t].expected) == 0);
        pdf_sty_freeseg(test_data);
    }
CUTE_TEST_CASE_END

CUTE_TEST_CASE(pdf_sty_get_data_from_tag_tests)
    struct get_data_from_tag_tests {
        char *test_buffer;
        char *expected_data;
        size_t expected_size;
    };

    struct get_data_from_tag_tests test_vector[] = {
        { "Bold</b>", "BOLD", 4 },
        { "iTaLiC</i>", "ITALIC", 6 },
        { "WowCreative</i>", "WOWCREATIVE", 11 }
    };

    size_t test_vector_nr = sizeof(test_vector) / sizeof(test_vector[0]), t;
    char *data;
    size_t data_size;

    for (t = 0; t < test_vector_nr; t++) {
        data = pdf_sty_get_data_from_tag(&test_vector[t].test_buffer,
                                         test_vector[t].test_buffer + strlen(test_vector[t].test_buffer),
                                         &data_size);

        CUTE_ASSERT(strstr(test_vector[t].test_buffer, "</") == test_vector[t].test_buffer);

        CUTE_ASSERT(data != NULL);
        CUTE_ASSERT(data_size ==  test_vector[t].expected_size);
        CUTE_ASSERT(memcmp(data, test_vector[t].expected_data, data_size) == 0);

        pdf_sty_freeseg(data);
    }
CUTE_TEST_CASE_END
