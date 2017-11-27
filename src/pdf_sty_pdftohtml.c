/*
 *                                                 Copyright (C) 2017
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#include <pdf_sty_pdftohtml.h>
#include <pdf_sty_memory.h>
#include <stdio.h>
#include <string.h>

#define PDF_STY_PDFTOHTML_CMDLINE "pdftohtml -i -q %s %s"

#define PDF_STY_PDFTOHTML_SFILE_SFFX "s.html"

char *pdf_sty_pdftohtml(const char *filepath, size_t *data_size) {
    char *data = NULL, *dp, *dp_end;
    char *temp_filepath = NULL;
    char sfilepath[0xffff], cmdline[0xffff];
    FILE *fp = NULL;

    if (filepath == NULL || data_size == NULL) {
        return NULL;
    }

    *data_size = 0;

    temp_filepath = tempnam(".", NULL);
    if (temp_filepath == NULL) {
        goto pdf_sty_pdftohtml_epilogue;
    }

    sprintf(cmdline, PDF_STY_PDFTOHTML_CMDLINE, filepath, temp_filepath);
    if (system(cmdline) != 0) {
        goto pdf_sty_pdftohtml_epilogue;
    }

    sprintf(sfilepath, "%s%s", temp_filepath, PDF_STY_PDFTOHTML_SFILE_SFFX);

    if ((fp = fopen(sfilepath, "r")) == NULL) {
        goto pdf_sty_pdftohtml_epilogue;
    }

    fseek(fp, 0L, SEEK_END);
    *data_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    data = (char *) pdf_sty_newseg(*data_size + 1);
    memset(data, 0L, *data_size + 1);
    fread(data, 1, *data_size, fp);

    dp = data;
    dp_end = dp + *data_size;

    // INFO(Rafael): Some versions of pdftohtml has some case differences in HTML tags.
    while (dp != dp_end) {
        *dp = tolower(*dp);
        dp++;
    }

    fclose(fp);

pdf_sty_pdftohtml_epilogue:

    if (temp_filepath != NULL) {
#ifndef _WIN32
        sprintf(cmdline, "rm %s*.html", temp_filepath);
#else
        sprintf(cmdline, "del %s*.html", temp_filepath);
#endif
        system(cmdline);
        free(temp_filepath);
    }

    return data;
}

#undef PDF_STY_PDFTOHTML_CMDLINE

#undef PDF_STY_PDFTOHTML_SFILE_SFFX
