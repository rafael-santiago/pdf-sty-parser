/*
 *                                                 Copyright (C) 2017
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#ifndef PDF_STY_PARSE_UTILS_H
#define PDF_STY_PARSE_UTILS_H 1

#include <stdlib.h>

char *pdf_sty_case_folding(char *data, const size_t data_size);

char *pdf_sty_get_data_from_tag(char **buf, char *buf_end, size_t *data_size);

#endif
