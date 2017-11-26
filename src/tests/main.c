/*
 *                                                 Copyright (C) 2017
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#include <cutest.h>
#include "memory_tests.h"
#include "ctx_tests.h"
#include "parse_utils_tests.h"

CUTE_TEST_CASE(lib_pdf_sty_parser_test_monkey)
    CUTE_RUN_TEST(pdf_sty_memory_tests);
    CUTE_RUN_TEST(add_word_to_pdf_sty_word_tests);
    CUTE_RUN_TEST(pdf_sty_case_folding_tests);
    CUTE_RUN_TEST(pdf_sty_get_data_from_tag_tests);
CUTE_TEST_CASE_END

CUTE_MAIN(lib_pdf_sty_parser_test_monkey);
