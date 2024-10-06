/**
 * This file is part of the calc scripting language project,
 * under the Apache License v2.0. See LICENSE for license
 * informations.
 */

#include "calc/core/hash.h"

CALC_API CalcHashCode_t CALC_STDCALL calcGetSimpleHashCode(const byte_t *const key)
{
    CalcHashCode_t i, hash = 0;

    for (i = 0; key[i]; i++)
        hash += key[i];

    return hash;
}
