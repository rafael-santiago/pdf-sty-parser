/*
 *                                                 Copyright (C) 2017
 *
 * This is free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#include <pdf_sty_parse_utils.h>
#include <pdf_sty_memory.h>
#include <ctype.h>
#include <string.h>

#define pdf_sty_parse_is_punctuation(b) ( (b) == ',' || (b) == '.' || (b) == ';' || (b) == '(' || (b) == ')' ||\
                                          (b) == '?' || (b) == '!' || (b) == ':' || (b) == '[' || (b) == ']' ||\
                                          (b) == '{' || (b) == '}')

char *pdf_sty_get_data_from_tag(char **buf, char *buf_end, size_t *data_size) {
    char *bp;
    char *data;

    if (buf == NULL || *buf >= buf_end) {
        return NULL;
    }

    bp = *buf;

    (*data_size) = 0;

    while (bp != buf_end && strstr(bp, "</") != bp && !pdf_sty_parse_is_punctuation(*bp)) {
        bp++;
        (*data_size) += 1;
    }

    if (pdf_sty_parse_is_punctuation(*bp)) {
        while (bp != buf_end && strstr(bp, "</") != bp) {
            bp++;
        }
    }

    if (bp == buf_end) {
        (*data_size) = 0;
        return NULL;
    }

    data = (char *) pdf_sty_newseg((*data_size) + 1);
    memset(data, 0, (*data_size) + 1);
    memcpy(data, *buf, *data_size);
    data = pdf_sty_case_folding(data, *data_size);
    (*buf) = bp;

    return data;
}

char *pdf_sty_case_folding(char *data, const size_t data_size) {
    char *dp, *dp_end;

    if (data == NULL) {
        return NULL;
    }

    dp = data;
    dp_end = dp + data_size;

    while (dp != dp_end) {
        if (isalpha(*dp)) {
            *dp = toupper(*dp);
        } else {
            switch (*dp) {
                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                case '�':
                    *dp = '�';
                    break;

                default:
                    break;

            }
        }
        dp++;
    }

    return data;
}

#undef pdf_sty_parse_is_punctuation
