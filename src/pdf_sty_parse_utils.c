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
#include <stdio.h>

#define pdf_sty_parse_is_punctuation(b) ( (b) == ',' || (b) == '.' || (b) == ';' || (b) == '(' || (b) == ')' ||\
                                          (b) == '?' || (b) == '!' || (b) == ':' || (b) == '[' || (b) == ']' ||\
                                          (b) == '{' || (b) == '}')

static void pdf_sty_rm_hyphenation(char *buf, size_t *data_size);

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
        if (*bp == '&' && (strstr(bp, "&#160") == bp || strstr(bp, "&nbsp") == bp)) {
            while (bp != buf_end && *bp != ';' && *bp != '<') {
                bp++;
            }
        }
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
    pdf_sty_rm_hyphenation(data, data_size);
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
            *dp = tolower(*dp);
        } else {
            switch (tolower(*dp)) {
                case 'á':
                    *dp = 'á';
                    break;

                case 'â':
                    *dp = 'â';
                    break;

                case 'ã':
                    *dp = 'ã';
                    break;

                case 'à':
                    *dp = 'à';
                    break;

                case 'ä':
                    *dp = 'ä';
                    break;

                case 'é':
                    *dp = 'é';
                    break;

                case 'ê':
                    *dp = 'ê';
                    break;

                case 'è':
                    *dp = 'è';
                    break;

                case 'ë':
                    *dp = 'ë';
                    break;

                case 'í':
                    *dp = 'í';
                    break;

                case 'ï':
                    *dp = 'ï';
                    break;

                case 'ì':
                    *dp = 'ì';
                    break;

                case 'ó':
                    *dp = 'ó';
                    break;

                case 'ö':
                    *dp = 'ö';
                    break;

                case 'ò':
                    *dp = 'ò';
                    break;

                case 'õ':
                    *dp = 'õ';
                    break;

                case 'ú':
                    *dp = 'ú';
                    break;

                case 'ü':
                    *dp = 'ü';
                    break;

                case 'ù':
                    *dp = 'ù';
                    break;

                case 0xC7:
                    *dp = 'ç';
                    break;

                default:
                    break;

            }
        }
        dp++;
    }

    return data;
}

static void pdf_sty_rm_hyphenation(char *buf, size_t *data_size) {
    char temp_buf[0xFFFF], *bp, *bp_end;
    size_t temp_buf_size;
    char *token;
    size_t token_off;

    if (buf == NULL || data_size == NULL || *data_size == 0 || *data_size > sizeof(temp_buf)) {
        return;
    }

    if ((token = strstr(buf, "-<br>")) != NULL || strstr(buf, "-<br/>") != NULL) {
        if (token == NULL) {
            token = "-<br/>";
            token_off = 5;
        } else {
            token = "-<br>";
            token_off = 4;
        }

        memset(temp_buf, 0, sizeof(temp_buf));
        temp_buf_size = 0;
        bp = buf;
        bp_end = bp + *data_size;

        while (bp < bp_end) {
            if (strstr(bp, token) == bp) {
                bp += token_off;
            } else {
                temp_buf[temp_buf_size++] = *bp;
            }
            bp++;
        }
        *data_size = temp_buf_size;
        sprintf(buf, "%s", temp_buf);
    }
}

#undef pdf_sty_parse_is_punctuation
