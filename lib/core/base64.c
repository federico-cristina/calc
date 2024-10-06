/**
 * This file is part of the calc scripting language project,
 * under the Apache License v2.0. See LICENSE for license
 * informations.
 * 
 * This fileis partially derived from files in the following
 * repository:
 *
 * https://github.com/B-Con/crypto-algorithms.git
 */

#include "calc/core/base64.h"

#define NEWLINE_INVL 76

static byte_t CALC_STDCALL calc_revchar(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        ch -= 'A';
    else if (ch >= 'a' && ch <= 'z')
        ch = ch - 'a' + 26;
    else if (ch >= '0' && ch <= '9')
        ch = ch - '0' + 52;
    else if (ch == '+')
        ch = 62;
    else if (ch == '/')
        ch = 63;

    return (byte_t)ch;
}

CALC_API size_t CALC_STDCALL calcBase64Encode(const byte_t *const in, byte_t *const out, size_t count, bool_t newlineFlag)
{
    // Note: To change the charset to a URL encoding, replace the '+' and '/' with '*' and '-'
    static const byte_t charset[] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
    };

    size_t idx, idx2, blks, blk_ceiling, left_over, newline_count = 0;

    blks = (count / 3);
    left_over = count % 3;

    if (out == NULL)
    {
        idx2 = blks * 4;

        if (left_over)
            idx2 += 4;

        if (newlineFlag)
            idx2 += count / 57;   // (NEWLINE_INVL / 4) * 3 = 57. One newline per 57 input bytes.
    }
    else
    {
        // Since 3 input bytes = 4 output bytes, determine out how many even sets of
        // 3 bytes the input has.
        blk_ceiling = blks * 3;

        for (idx = 0, idx2 = 0; idx < blk_ceiling; idx += 3, idx2 += 4)
        {
            out[idx2] = charset[in[idx] >> 2];
            out[idx2 + 1] = charset[((in[idx] & 0x03) << 4) | (in[idx + 1] >> 4)];
            out[idx2 + 2] = charset[((in[idx + 1] & 0x0f) << 2) | (in[idx + 2] >> 6)];
            out[idx2 + 3] = charset[in[idx + 2] & 0x3F];

            // The offical standard requires a newline every 76 characters.
            // (Eg, first newline is character 77 of the output.)
            if (((idx2 - newline_count + 4) % NEWLINE_INVL == 0) && newlineFlag)
            {
                out[idx2 + 4] = '\n';

                idx2++;
                newline_count++;
            }
        }

        if (left_over == 1)
        {
            out[idx2] = charset[in[idx] >> 2];
            out[idx2 + 1] = charset[(in[idx] & 0x03) << 4];
            out[idx2 + 2] = '=';
            out[idx2 + 3] = '=';

            idx2 += 4;
        }
        else if (left_over == 2)
        {
            out[idx2] = charset[in[idx] >> 2];
            out[idx2 + 1] = charset[((in[idx] & 0x03) << 4) | (in[idx + 1] >> 4)];
            out[idx2 + 2] = charset[(in[idx + 1] & 0x0F) << 2];
            out[idx2 + 3] = '=';

            idx2 += 4;
        }
    }

    return idx2;
}

CALC_API size_t CALC_STDCALL calcBase64Decode(const byte_t *const in, byte_t *const out, size_t count)
{
    byte_t ch;
    size_t idx, idx2, blks, blk_ceiling, left_over;

    if (in[count - 1] == '=')
        count--;
    if (in[count - 1] == '=')
        count--;

    blks = count / 4;
    left_over = count % 4;

    if (out == NULL)
    {
        if (count >= 77 && in[NEWLINE_INVL] == '\n')   // Verify that newlines where used.
            count -= count / (NEWLINE_INVL + 1);

        blks = count / 4;
        left_over = count % 4;

        idx = blks * 3;

        if (left_over == 2)
            idx++;
        else if (left_over == 3)
            idx += 2;
    }
    else
    {
        blk_ceiling = blks * 4;

        for (idx = 0, idx2 = 0; idx2 < blk_ceiling; idx += 3, idx2 += 4)
        {
            if (in[idx2] == '\n')
                idx2++;

            out[idx] = (calc_revchar(in[idx2]) << 2) | ((calc_revchar(in[idx2 + 1]) & 0x30) >> 4);
            out[idx + 1] = (calc_revchar(in[idx2 + 1]) << 4) | (calc_revchar(in[idx2 + 2]) >> 2);
            out[idx + 2] = (calc_revchar(in[idx2 + 2]) << 6) | calc_revchar(in[idx2 + 3]);
        }

        if (left_over == 2)
        {
            out[idx] = (calc_revchar(in[idx2]) << 2) | ((calc_revchar(in[idx2 + 1]) & 0x30) >> 4);

            idx++;
        }
        else if (left_over == 3)
        {
            out[idx] = (calc_revchar(in[idx2]) << 2) | ((calc_revchar(in[idx2 + 1]) & 0x30) >> 4);
            out[idx + 1] = (calc_revchar(in[idx2 + 1]) << 4) | (calc_revchar(in[idx2 + 2]) >> 2);

            idx += 2;
        }
    }

    return idx;
}
