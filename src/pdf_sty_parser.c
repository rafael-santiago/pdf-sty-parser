/*
 *                                                 Copyright (C) 2017
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#include <pdf_sty_parser.h>
#include <pdf_sty_pdftohtml.h>
#include <pdf_sty_parse_utils.h>
#include <pdf_sty_memory.h>
#include <pdf_sty_ctx.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static int has_relevant_tag_open(char **buf, char *buf_end);

static int get_pages_total(char *buf, char *buf_end);

static int get_page_number(char *buf, char *buf_end, const int curr_page);

static char *g_relevant_tags[] = {
    "<b>", "<B>", "<i>", "<I>"
};

static size_t g_relevant_tags_nr = sizeof(g_relevant_tags) / sizeof(g_relevant_tags[0]);

#define PDF_STY_PARSER_PAGE_NUMBERING_TAG "<a name="

#define PDF_STY_PARSER_PAGE_NUMBERING_TAG_SIZE 8

pdf_sty_word_ctx *pdf_sty_parse_pdf(const char *filepath) {
    char *buf = NULL, *bp, *bp_end;
    size_t buf_size;
    struct pages_ctx {
        pdf_sty_word_ctx *words, *words_tail;
    };
    struct pages_ctx *pages = NULL;
    pdf_sty_word_ctx *words;
    int has_error = 0;
    char *data = NULL;
    size_t data_size;
    int curr_page, pages_nr = 0, pn;

    buf = pdf_sty_pdftohtml(filepath, &buf_size);

    if (buf == NULL) {
        return NULL;
    }

    bp = buf;
    bp_end = bp + buf_size;

    pages_nr = get_pages_total(bp, bp_end);

    bp = strstr(bp, "<a name=1></a>");

    if (pages_nr == 0 || bp == NULL) {
        pdf_sty_freeseg(buf);
        return NULL;
    }

    // INFO(Rafael): Reducing the search space for each page.

    pages = (struct pages_ctx *) pdf_sty_newseg(sizeof(struct pages_ctx) * pages_nr);

    for (curr_page = 0; curr_page < pages_nr; curr_page++) {
        pages[curr_page].words = NULL;
        pages[curr_page].words_tail = NULL;
    }

    curr_page = 1;

    while (bp != bp_end) {

        if (has_relevant_tag_open(&bp, bp_end)) {
            data = pdf_sty_get_data_from_tag(&bp, bp_end, &data_size);
            if (data != NULL) {
                pages[curr_page - 1].words = add_word_to_pdf_sty_word(pages[curr_page - 1].words,
                                                                      data, data_size, curr_page,
                                                                      &pages[curr_page - 1].words_tail);
                pdf_sty_freeseg(data);
            }
        }

        bp++;
        curr_page = get_page_number(bp, bp_end, curr_page);
    }

    // INFO(Rafael): Merging all document pages.
    words = NULL;

    pn = 0;
    while (pages[pn].words == NULL && pn < pages_nr) {
        pn++;
    }

    if (pn == pages_nr) {
        goto pdf_sty_parse_pdf_epilogue;
    }


    words = pages[pn].words;

    for (curr_page = pn + 1; curr_page < pages_nr; curr_page++) {
        if (pages[curr_page].words != NULL) {
            pages[pn].words_tail->next = pages[curr_page].words;
            pn = curr_page;
        }
    }

pdf_sty_parse_pdf_epilogue:

    pdf_sty_freeseg(pages);
    pdf_sty_freeseg(buf);

    return words;
}

static int has_relevant_tag_open(char **buf, char *buf_end) {
    size_t t;

    if (buf == NULL || *buf >= buf_end) {
        return 0;
    }

    for (t = 0; t < g_relevant_tags_nr; t++) {
        if (strstr(*buf, g_relevant_tags[t]) == (*buf)) {
            while (*buf != buf_end && **buf != '>') {
                (*buf)++;
            }

            if (*buf != buf_end) {
                (*buf) += 1;
            }

            return 1;
        }
    }

    return 0;
}

static int get_page_number(char *buf, char *buf_end, const int curr_page) {
    char *bp, temp[200];
    size_t t;

    if (buf == NULL || buf == buf_end) {
        return curr_page;
    }

    if (strstr(buf, PDF_STY_PARSER_PAGE_NUMBERING_TAG) != buf) {
        return curr_page;
    }

    bp = buf + PDF_STY_PARSER_PAGE_NUMBERING_TAG_SIZE;

    if (!isdigit(*bp)) {
        return curr_page;
    }

    memset(temp, 0, sizeof(temp));
    t = 0;

    while (isdigit(*bp) && t < sizeof(temp)) {
        temp[t++] = *bp;
        bp++;
    }

    return atoi(temp);
}

static int get_pages_total(char *buf, char *buf_end) {
    char *bp;
    int pages_total = 0;

    if (buf == NULL || buf == buf_end) {
        return 0;
    }

    bp = buf_end - 1;

    while (pages_total == 0 && bp != buf) {
        pages_total = get_page_number(bp, buf_end, pages_total);
        bp--;
    }

    return pages_total;
}

#undef PDF_STY_PARSER_PAGE_NUMBERING_TAG

#undef PDF_STY_PARSER_PAGE_NUMBERING_TAG_SIZE
