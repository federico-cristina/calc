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

#include "calc/base/alloc.h"
#include "calc/core/sha256.h"

CALC_API CalcSha256Context_t *CALC_STDCALL calcSha256ContextInit(CalcSha256Context_t *const ctx)
{
    assert(ctx != NULL);

    ctx->datalen = 0;
    ctx->bitlen  = 0;

    CALC_REGISTER uint32_t *const state = (uint32_t *)ctx->state;

    state[0] = 0x6A09E667;
    state[1] = 0xBB67AE85;
    state[2] = 0x3C6EF372;
    state[3] = 0xA54FF53A;
    state[4] = 0x510E527F;
    state[5] = 0x9B05688C;
    state[6] = 0x1F83D9AB;
    state[7] = 0x5BE0CD19;

    return ctx;
}

CALC_API CalcSha256Context_t *CALC_STDCALL calcCreateSha256Context(void)
{
    return calcSha256ContextInit(alloc(CalcSha256Context_t));
}

#define ROTLEFT(a,b)    (((a) << (b)) | ((a) >> (32 - (b))))
#define ROTRIGHT(a,b)   (((a) >> (b)) | ((a) << (32 - (b))))

#define CH(x,y,z)       (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z)      (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x)          (ROTRIGHT(x,  2) ^ ROTRIGHT(x, 13) ^ ROTRIGHT(x, 22))
#define EP1(x)          (ROTRIGHT(x,  6) ^ ROTRIGHT(x, 11) ^ ROTRIGHT(x, 25))
#define SIG0(x)         (ROTRIGHT(x,  7) ^ ROTRIGHT(x, 18) ^ ((x) >>  3))
#define SIG1(x)         (ROTRIGHT(x, 17) ^ ROTRIGHT(x, 19) ^ ((x) >> 10))

static void CALC_STDCALL calc_Sha256Transform(CalcSha256Context_t *const ctx)
{
    uint32_t a, b, c, d, e, f, g, h, i, j, *const k = (uint32_t *)ctx->key, t1, t2, m[64], *const state = (uint32_t *)ctx->state;
    byte_t *const data = (byte_t *)ctx->data;

    for (i = 0, j = 0; i < 16; ++i, j += 4)
        m[i] = (data[j + 0] << 24)
             | (data[j + 1] << 16)
             | (data[j + 2] <<  8)
             | (data[j + 3] <<  0);

    for (; i < 64; ++i)
        m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    f = state[5];
    g = state[6];
    h = state[7];

    for (i = 0; i < 64; ++i)
    {
        t1 = h + EP1(e) + CH(e, f, g) + k[i] + m[i];
        t2 = EP0(a) + MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;

    return;
}

CALC_API CalcSha256Context_t *CALC_STDCALL calcSha256Update(CalcSha256Context_t *const ctx, const byte_t *const data, size_t count, const CalcSha256HashKey_t key)
{
    CALC_REGISTER uint32_t i;

    for (i = 0; i < count; i++)
    {
        ctx->data[ctx->datalen] = data[i];
        ctx->datalen++;

        if (ctx->datalen == 64)
        {
            calc_Sha256Transform(ctx);

            ctx->bitlen += 512;
            ctx->datalen = 0;
        }
    }

    for (i = 0; i < CALC_SHA256_KEY_SIZE; i++)
        ctx->key[i] = key[i];

    return ctx;
}

CALC_API CalcSha256Context_t *CALC_STDCALL calcSha256Final(CalcSha256Context_t *const ctx, byte_t *const outHash)
{
    CALC_REGISTER uint32_t i = ctx->datalen, *const state = (uint32_t *)ctx->state;
    CALC_REGISTER byte_t *const data = ctx->data;

    // Pad whatever data is left in the buffer.
    if (ctx->datalen < 56)
    {
        data[i++] = 0x80;

        while (i < 56)
            data[i++] = 0x00;
    }
    else
    {
        data[i++] = 0x80;

        while (i < 64)
            data[i++] = 0x00;

        calc_Sha256Transform(ctx);
        bufset(data, 0, 56);
    }

    // Append to the padding the total message's length in bits and transform.
    ctx->bitlen += (uint64_t)ctx->datalen * 8;

    CALC_REGISTER uint64_t bitlen = ctx->bitlen;

    data[63] = (byte_t)(bitlen >>  0);
    data[62] = (byte_t)(bitlen >>  8);
    data[61] = (byte_t)(bitlen >> 16);
    data[60] = (byte_t)(bitlen >> 24);
    data[59] = (byte_t)(bitlen >> 32);
    data[58] = (byte_t)(bitlen >> 40);
    data[57] = (byte_t)(bitlen >> 48);
    data[56] = (byte_t)(bitlen >> 56);

    calc_Sha256Transform(ctx);

    // Since this implementation uses little endian byte ordering and SHA uses big endian,
    // reverse all the bytes when copying the final state to the output hash.
    for (i = 0; i < 4; ++i)
    {
        outHash[i +  0] = (state[0] >> (24 - i * 8)) & 0x000000ff;
        outHash[i +  4] = (state[1] >> (24 - i * 8)) & 0x000000ff;
        outHash[i +  8] = (state[2] >> (24 - i * 8)) & 0x000000ff;
        outHash[i + 12] = (state[3] >> (24 - i * 8)) & 0x000000ff;
        outHash[i + 16] = (state[4] >> (24 - i * 8)) & 0x000000ff;
        outHash[i + 20] = (state[5] >> (24 - i * 8)) & 0x000000ff;
        outHash[i + 24] = (state[6] >> (24 - i * 8)) & 0x000000ff;
        outHash[i + 28] = (state[7] >> (24 - i * 8)) & 0x000000ff;
    }

    return ctx;
}

CALC_API void CALC_STDCALL calcSha256Encrypt(byte_t *const outHash, const byte_t *const data, const uint32_t *const key)
{
    static const CalcSha256HashKey_t defaultKey = {
        0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
        0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
        0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
        0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
        0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
        0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
        0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
        0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
    };

    CalcSha256Context_t *ctx = stackalloc(CalcSha256Context_t);

    ctx = calcSha256ContextInit(ctx);
    ctx = calcSha256Update(ctx, data, buflen(data), !key ? defaultKey : *(CalcSha256HashKey_t *)&key);
    ctx = calcSha256Final(ctx, outHash);

    freea(ctx);

    return;
}
