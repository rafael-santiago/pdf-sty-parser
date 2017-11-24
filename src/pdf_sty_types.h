/*
 *                                                 Copyright (C) 2017
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#ifndef PDF_STY_TYPES_H
#define PDF_STY_TYPES_H 1

#include <stdlib.h>

typedef struct pdf_sty_word {
    char *data;
    size_t data_size;
    int page;
    int freq;
    struct pdf_sty_word *next;
}pdf_sty_word_ctx;

#endif
