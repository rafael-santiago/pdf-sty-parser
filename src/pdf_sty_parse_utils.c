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

char *pdf_sty_get_data_from_tag(char **buf, char *buf_end, size_t *data_size) {
    char *bp;
    char *data;

    if (buf == NULL || *buf >= buf_end) {
        return NULL;
    }

    bp = *buf;

    while (bp != buf_end && strstr(bp, "</") != bp) {
        bp++;
        (*data_size) += 1;
    }

    if (bp == buf_end) {
        (*data_size) = 0;
        return NULL;
    }

    data = (char *) pdf_sty_newseg((*data_size) + 1);
    memset(data, 0, (*data_size) + 1);
    memcpy(data, *buf, *data_size);
    data = pdf_sty_case_folding(data, *data_size);
    (*buf) += *data_size;

    return data;
}

char *pdf_sty_case_folding(char *data, const size_t data_size) {
    char *dp = data;
    char *dp_end = dp + data_size;

    while (dp != dp_end) {
        if (isalpha(*dp)) {
            *dp = toupper(*dp);
        } else {
            switch (*dp) {
                case 'á':
                    *dp = 'Á';
                    break;

                case 'â':
                    *dp = 'Â';
                    break;

                case 'ã':
                    *dp = 'Ã';
                    break;

                case 'à':
                    *dp = 'À';
                    break;

                case 'ä':
                    *dp = 'Ä';
                    break;

                case 'é':
                    *dp = 'É';
                    break;

                case 'ê':
                    *dp = 'Ê';
                    break;

                case 'è':
                    *dp = 'È';
                    break;

                case 'ë':
                    *dp = 'Ë';
                    break;

                case 'í':
                    *dp = 'Í';
                    break;

                case 'ï':
                    *dp = 'Ï';
                    break;

                case 'ì':
                    *dp = 'Ì';
                    break;

                case 'ó':
                    *dp = 'Ó';
                    break;

                case 'ö':
                    *dp = 'Ö';
                    break;

                case 'ò':
                    *dp = 'Ò';
                    break;

                case 'õ':
                    *dp = 'Õ';
                    break;

                case 'ú':
                    *dp = 'Ú';
                    break;

                case 'ü':
                    *dp = 'Ü';
                    break;

                case 'ù':
                    *dp = 'Ù';
                    break;

                case 'ç':
                    *dp = 'Ç';
                    break;

                default:
                    break;

            }
        }
        dp++;
    }

    return data;
}
