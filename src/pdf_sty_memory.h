/*
 *                                                 Copyright (C) 2017
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#ifndef PDF_STY_MEMORY_H
#define PDF_STY_MEMORY_H 1

#include <stdlib.h>

void *pdf_sty_newseg(const size_t ssize);

void pdf_sty_freeseg(void *seg);

#endif
