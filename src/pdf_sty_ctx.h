/*
 *                                                 Copyright (C) 2017
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#ifndef PDF_STY_CTX_H
#define PDF_STY_CTX_H 1

#include <pdf_sty_types.h>

pdf_sty_word_ctx *add_word_to_pdf_sty_word(pdf_sty_word_ctx *words,
                                           const char *data,
                                           const size_t data_size,
                                           const int page, pdf_sty_word_ctx **tail);

void del_pdf_sty_word(pdf_sty_word_ctx *words);

#endif
