/*
 *                                                 Copyright (C) 2017
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#include "memory_tests.h"
#include <pdf_sty_memory.h>

CUTE_TEST_CASE(pdf_sty_memory_tests)
    char *data = pdf_sty_newseg(10);
    CUTE_ASSERT(data != NULL);
    pdf_sty_freeseg(data);
    // INFO(Rafael): Once enabled the memory leak check system, the pdf_sty_freeseg()
    //               correctness will be checked at the end of the tests.
CUTE_TEST_CASE_END
