/*
 *                                                 Copyright (C) 2017
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#include <pdf_sty_ctx.h>
#include <pdf_sty_memory.h>
#include <string.h>

#define new_pdf_sty_word_ctx(w) {\
    (w) = pdf_sty_newseg(sizeof(pdf_sty_word_ctx));\
    (w)->data = NULL;\
    (w)->data_size = 0;\
    (w)->freq = 0;\
    (w)->next = NULL;\
}

static pdf_sty_word_ctx *get_pdf_sty_word_tail(pdf_sty_word_ctx *words);

static pdf_sty_word_ctx *get_pdf_sty_word_data(const char *data, pdf_sty_word_ctx *words);

pdf_sty_word_ctx *add_word_to_pdf_sty_word(pdf_sty_word_ctx *words,
                                           const char *data,
                                           const size_t data_size,
                                           const int page, pdf_sty_word_ctx **tail) {

    pdf_sty_word_ctx *h = words, *p = NULL;

    if (data == NULL || data_size == 0) {
        return words;
    }

    if (words == NULL) {
        new_pdf_sty_word_ctx(p);
        h = p;
    } else if ((p = get_pdf_sty_word_data(data, words)) == NULL) {
        if (tail != NULL) {
            p = (*tail);
        }

        if (p == NULL) {
            p = get_pdf_sty_word_tail(words);
        }

        new_pdf_sty_word_ctx(p->next);

        p = p->next;
    }

    if (p->data == NULL) {
        p->data = pdf_sty_newseg(data_size + 1);
        memset(p->data, 0, data_size + 1);
        memcpy(p->data, data, data_size);
        p->data_size = data_size;
        p->page = page;
    }

    p->freq++;

    if (tail != NULL) {
        (*tail) = p;
    }

    return h;
}

void del_pdf_sty_word(pdf_sty_word_ctx *words) {
    pdf_sty_word_ctx *p, *t;
    for (p = t = words; t; p = t) {
        t = p->next;
        if (p->data != NULL) {
            pdf_sty_freeseg(p->data);
        }
        pdf_sty_freeseg(p);
    }
}

static pdf_sty_word_ctx *get_pdf_sty_word_tail(pdf_sty_word_ctx *words) {
    pdf_sty_word_ctx *p;

    if (words == NULL) {
        return NULL;
    }

    for (p = words; p->next != NULL; p = p->next)
        ;

    return p;
}

static pdf_sty_word_ctx *get_pdf_sty_word_data(const char *data, pdf_sty_word_ctx *words) {
    pdf_sty_word_ctx *w;

    if (data == NULL) {
        return NULL;
    }

    for (w = words; w != NULL; w = w->next) {
        if (strcmp(w->data, data) == 0) {
            return w;
        }
    }

    return NULL;
}

#undef new_pdf_sty_word_ctx
