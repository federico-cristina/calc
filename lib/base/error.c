/**
 * This file is part of the calc scripting language project,
 * under the Apache License v2.0. See LICENSE for license
 * informations.
 */

#include "calc/base/error.h"

// Non-fatal errors handling

typedef struct _jmpframe
{
    jmp_buf          *jump;
    struct _jmpframe *prev;
} jmpframe_t, *jmpstack_t;

static inline jmpframe_t *CALC_STDCALL _new_jmpframe(jmp_buf *const buf, jmpframe_t *const prev)
{
    jmpframe_t *frame = (jmpframe_t *)malloc(sizeof(jmpframe_t));

    if (!frame)
        fail("error: cannot allocate jmpframe", NULL);

    frame->jump = buf;
    frame->prev = prev;

    return frame;
}

static inline jmpstack_t *CALC_STDCALL _get_jmpstack(void)
{
    static jmpstack_t stack = NULL;

    if (!stack)
        stack = (jmpstack_t)_new_jmpframe(NULL, NULL);

    return &stack;
}

void CALC_STDCALL jmptop(jmp_buf *const buf)
{
    jmpstack_t stack = *_get_jmpstack();

    if (!stack->jump)
        stack->jump = buf;
    else
        stack = _new_jmpframe(buf, (jmpframe_t *)stack);

    return;
}

void CALC_STDCALL jmppop(void)
{
    jmpstack_t stack = *_get_jmpstack();

    if (!stack->prev)
        stack->jump = NULL;
    else
        (*_get_jmpstack()) = stack->prev, free(stack);

    return;
}

CALC_NORETURN void CALC_STDCALL jump(int value)
{
    jmpstack_t stack = *_get_jmpstack();

    if (!stack->jump)
        fail("error %d: an unhandled error signal has been raised.", value);

    jmp_buf *buf = stack->jump;

    jmppop();
    longjmp(*buf, value);
}
