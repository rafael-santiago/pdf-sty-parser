/*
 *                                                 Copyright (C) 2017
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#include <pdf_sty_memory.h>
#include <stdio.h>

void *pdf_sty_newseg(const size_t ssize) {
    void *data;

    if (ssize == 0) {
        return NULL;
    }

    data = malloc(ssize);

    if (data == NULL) {
        printf("pdf_sty_newseg PANIC: no memory!\n");
        exit(1);
    }

    return data;
}

void pdf_sty_freeseg(void *seg) {
    if (seg != NULL) {
        free(seg);
    }
}
