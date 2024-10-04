#include "calc/base/alloc.h"

#include "calc/core/hash.h"

CALC_API CalcHashCode_t CALC_STDCALL calcGetSimpleHashCode(const byte_t *const key)
{
    CalcHashCode_t i, hash = 0;

    for (i = 0; key[i]; i++)
        hash += key[i];

    return hash;
}

// Base64 Conversion Functions

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

CALC_API size_t CALC_STDCALL calcBase64Encode(const byte_t *const key, byte_t *const out, size_t count, bool_t newlineFlag)
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
            out[idx2] = charset[key[idx] >> 2];
            out[idx2 + 1] = charset[((key[idx] & 0x03) << 4) | (key[idx + 1] >> 4)];
            out[idx2 + 2] = charset[((key[idx + 1] & 0x0f) << 2) | (key[idx + 2] >> 6)];
            out[idx2 + 3] = charset[key[idx + 2] & 0x3F];

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
            out[idx2] = charset[key[idx] >> 2];
            out[idx2 + 1] = charset[(key[idx] & 0x03) << 4];
            out[idx2 + 2] = '=';
            out[idx2 + 3] = '=';

            idx2 += 4;
        }
        else if (left_over == 2)
        {
            out[idx2] = charset[key[idx] >> 2];
            out[idx2 + 1] = charset[((key[idx] & 0x03) << 4) | (key[idx + 1] >> 4)];
            out[idx2 + 2] = charset[(key[idx + 1] & 0x0F) << 2];
            out[idx2 + 3] = '=';

            idx2 += 4;
        }
    }

    return idx2;
}

CALC_API size_t CALC_STDCALL calcBase64Decode(const byte_t *const b64, byte_t *const out, size_t count)
{
    byte_t ch;
    size_t idx, idx2, blks, blk_ceiling, left_over;

    if (b64[count - 1] == '=')
        count--;
    if (b64[count - 1] == '=')
        count--;

    blks = count / 4;
    left_over = count % 4;

    if (out == NULL)
    {
        if (count >= 77 && b64[NEWLINE_INVL] == '\n')   // Verify that newlines where used.
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
            if (b64[idx2] == '\n')
                idx2++;

            out[idx] = (calc_revchar(b64[idx2]) << 2) | ((calc_revchar(b64[idx2 + 1]) & 0x30) >> 4);
            out[idx + 1] = (calc_revchar(b64[idx2 + 1]) << 4) | (calc_revchar(b64[idx2 + 2]) >> 2);
            out[idx + 2] = (calc_revchar(b64[idx2 + 2]) << 6) | calc_revchar(b64[idx2 + 3]);
        }

        if (left_over == 2)
        {
            out[idx] = (calc_revchar(b64[idx2]) << 2) | ((calc_revchar(b64[idx2 + 1]) & 0x30) >> 4);

            idx++;
        }
        else if (left_over == 3)
        {
            out[idx] = (calc_revchar(b64[idx2]) << 2) | ((calc_revchar(b64[idx2 + 1]) & 0x30) >> 4);
            out[idx + 1] = (calc_revchar(b64[idx2 + 1]) << 4) | (calc_revchar(b64[idx2 + 2]) >> 2);

            idx += 2;
        }
    }

    return idx;
}

CALC_API CalcHashCode_t CALC_STDCALL calcGetBase64HashCode(const byte_t *const key)
{
    size_t i, count, length;
    byte_t *outBuffer;
    CalcHashCode_t hashCode = 0;

    length = buflen(key);
    count = calcBase64Encode(key, NULL, length, FALSE);
    outBuffer = stackdim(byte_t, count);

    calcBase64Encode(key, outBuffer, length, FALSE);

    for (i = 0; i < count; i++)
        hashCode += outBuffer[i];

    freea(outBuffer);

    return hashCode;
}

#undef NEWLINE_INVL

// SHA-256 Hashing Function

CALC_API CalcSha256Context_t *CALC_STDCALL calcSha256ContextInit(CalcSha256Context_t *const ctx)
{
    assert(ctx != NULL);

    ctx->datalen = 0;
    ctx->bitlen = 0;
    ctx->state[0] = 0x6A09E667;
    ctx->state[1] = 0xBB67AE85;
    ctx->state[2] = 0x3C6EF372;
    ctx->state[3] = 0xA54FF53A;
    ctx->state[4] = 0x510E527F;
    ctx->state[5] = 0x9B05688C;
    ctx->state[6] = 0x1F83D9AB;
    ctx->state[7] = 0x5BE0CD19;

    return ctx;
}

CALC_API CalcSha256Context_t *CALC_STDCALL calcCreateSha256Context(void)
{
    return calcSha256ContextInit(alloc(CalcSha256Context_t));
}

#define ROTLEFT(a,b)    (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b)   (((a) >> (b)) | ((a) << (32-(b))))

#define CH(x,y,z)       (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z)      (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x)          (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x)          (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x)         (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x)         (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

static void CALC_STDCALL calc_Sha256Transform(CalcSha256Context_t *const ctx)
{
    static const uint32_t k[64] = {
        0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
        0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
        0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
        0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
        0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
        0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
        0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
        0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
    };

    uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, m[64] = { 0 };
    byte_t *data = ctx->data;

    for (i = 0, j = 0; i < 16; ++i, j += 4)
        m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);

    for (; i < 64; ++i)
        m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

    a = ctx->state[0];
    b = ctx->state[1];
    c = ctx->state[2];
    d = ctx->state[3];
    e = ctx->state[4];
    f = ctx->state[5];
    g = ctx->state[6];
    h = ctx->state[7];

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

    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
    ctx->state[5] += f;
    ctx->state[6] += g;
    ctx->state[7] += h;

    return;
}

#undef ROTLEFT
#undef ROTRIGHT

#undef CH
#undef MAJ
#undef EP0
#undef EP1
#undef SIG0
#undef SIG1

CALC_API CalcSha256Context_t *CALC_STDCALL calcSha256Update(CalcSha256Context_t *const ctx, const byte_t *const data, size_t count)
{
    uint32_t i;

    for (i = 0; i < count; ++i)
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

    return ctx;
}

CALC_API CalcSha256Context_t *CALC_STDCALL calcSha256Final(CalcSha256Context_t *const ctx, byte_t *const outHash)
{
    uint32_t i;
    byte_t *data;

    i = ctx->datalen;
    data = ctx->data;

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

    data[63] = (byte_t)ctx->bitlen;
    data[62] = (byte_t)(ctx->bitlen >> 8);
    data[61] = (byte_t)(ctx->bitlen >> 16);
    data[60] = (byte_t)(ctx->bitlen >> 24);
    data[59] = (byte_t)(ctx->bitlen >> 32);
    data[58] = (byte_t)(ctx->bitlen >> 40);
    data[57] = (byte_t)(ctx->bitlen >> 48);
    data[56] = (byte_t)(ctx->bitlen >> 56);

    calc_Sha256Transform(ctx);

    // Since this implementation uses little endian byte ordering and SHA uses big endian,
    // reverse all the bytes when copying the final state to the output hash.
    for (i = 0; i < 4; ++i)
    {
        outHash[i] = (ctx->state[0] >> (24 - i * 8)) & 0x000000ff;
        outHash[i + 4] = (ctx->state[1] >> (24 - i * 8)) & 0x000000ff;
        outHash[i + 8] = (ctx->state[2] >> (24 - i * 8)) & 0x000000ff;
        outHash[i + 12] = (ctx->state[3] >> (24 - i * 8)) & 0x000000ff;
        outHash[i + 16] = (ctx->state[4] >> (24 - i * 8)) & 0x000000ff;
        outHash[i + 20] = (ctx->state[5] >> (24 - i * 8)) & 0x000000ff;
        outHash[i + 24] = (ctx->state[6] >> (24 - i * 8)) & 0x000000ff;
        outHash[i + 28] = (ctx->state[7] >> (24 - i * 8)) & 0x000000ff;
    }

    return ctx;
}

CALC_API CalcHashCode_t CALC_STDCALL calcGetSha256HashCode(const byte_t *const key)
{
    CalcHashCode_t hashCode = 0;
    CalcSha256HashBlock_t block = stackdim(byte_t, CALC_SHA256_BLOCK_SIZE);
    CalcSha256Context_t *ctx = stackalloc(CalcSha256Context_t);

    ctx = calcSha256ContextInit(ctx);
    ctx = calcSha256Update(ctx, key, buflen(key));
    ctx = calcSha256Final(ctx, block);

    int i;

    for (i = 0; i < CALC_SHA256_BLOCK_SIZE; i++)
        hashCode += block[i];

    freea(block);
    freea(ctx);

    return hashCode;
}
