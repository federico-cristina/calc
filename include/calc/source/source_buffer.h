#pragma once

/**
 * @file        source_buffer.h
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 *
 * @brief       In this header are defined structures, macro and functions
 *              to create, delete and manipulate source buffers.
 */

#ifndef CALC_SOURCE_SOURCE_BUFFER_H_
#define CALC_SOURCE_SOURCE_BUFFER_H_

#include "calc/base/api.h"
#include "calc/base/bool.h"
#include "calc/base/byte.h"
#include "calc/base/file.h"
#include "calc/base/utf8.h"

CALC_C_HEADER_BEGIN

/// @brief Enumeration of supported encodings.
typedef enum _CalcSourceEncoding
{
    /// @brief ASCII encoding.
    CALC_SOURCE_ENCODING_ASCII,
    /// @brief UTF-8 encoding.
    CALC_SOURCE_ENCODING_UTF_8,
} CalcSourceEncoding_t;

/// @brief Source buffer data structure.
typedef struct _CalcSourceBuffer
{
    /// @brief A pointer to the beginning of the buffer's data.
    byte_t *data;
    /// @brief The maximum number of characters that this source buffer can
    ///        contain.
    size_t  size;
} CalcSourceBuffer_t;

/// @brief Creates a new source buffer of the same number of characters as
///        size parameter specifies and an initial content specified by the
///        content parameter.
/// @param size The maximum number of bytes that the source buffer will
///             store.
/// @param content A buffer of bytes representing the content that will be
///                copied in the buffer on its creation. It can be NULL.
/// @param count The number of bytes stored into content parameter.
/// @return A pointer to the new source buffer.
CALC_API CalcSourceBuffer_t *CALC_STDCALL calcCreateSourceBuffer(size_t size, byte_t *const content, size_t count);

/// @brief Creates a new source buffer that will contain a specified string
///        of bytes.
/// @param text The string to wrap into the buffer.
/// @return A pointer to the new source buffer.
CALC_API CalcSourceBuffer_t *CALC_STDCALL calcCreateSourceBufferFromText(const char *const text);
/// @brief Creates a new source buffers with the entire content of the file
///        specified by the path parameter.
/// @param path The path to the file to load and wrap into the buffer.
/// @return A pointer to the new source buffer.
CALC_API CalcSourceBuffer_t *CALC_STDCALL calcCreateSourceBufferFromFile(const char *const path);

/// @brief Creates a new source buffer loading the content of a file stream,
///        do not use this function to load a source buffer form stdin.
/// @param stream A source file stream.
/// @return A pointer to the new source buffer.
CALC_API CalcSourceBuffer_t *CALC_STDCALL calcCreateSourceBufferFromStream(FILE *const stream);
/// @brief Creates a new source buffer loading the next line of the stdin.
/// @return A pointer to the new source buffer.
CALC_API CalcSourceBuffer_t *CALC_STDCALL calcCreateSourceBufferFromStdin(void);

/// @brief Gets thecharacter in the position specified by position parameter.
/// @param sourceBuffer A pointer to the source buffer from which read.
/// @param encoding The encoding of the character to read.
/// @param position The position of the character to read.
/// @param outOffset A pointer to a variable in which store the character's
///                  width in bytes.
/// @return The character in the specified position.
CALC_API int32_t CALC_STDCALL calcSourceBufferGetChar(CalcSourceBuffer_t *const sourceBuffer, CalcSourceEncoding_t encoding, uint64_t position, uint32_t *const outOffset);

/// @brief Dumps the content of a source buffer on a stream. When stream parameter
///        is NULL the default choice is stderr stream.
/// @param stream The stream on which dump the content of the source buffer.
/// @return The number of written characters.
CALC_API int CALC_STDCALL calcDumpSourceBuffer(const CalcSourceBuffer_t *const sourceBuffer, FILE *const stream);

/// @brief Clears the content of the source buffer.
/// @param sourceBuffer A pointer to the source buffer to clear.
/// @return TRUE when the buffer is cleared succefully, FALSE in the other cases.
CALC_API bool_t CALC_STDCALL calcClearSourceBuffer(CalcSourceBuffer_t *const sourceBuffer);

/// @brief Deletes the specified source buffer releasing each used resource.
/// @param sourceBuffer A pointer to the source buffer to delete.
CALC_API void CALC_STDCALL calcDeleteSourceBuffer(CalcSourceBuffer_t *const sourceBuffer);

CALC_C_HEADER_END

#endif // CALC_SOURCE_SOURCE_BUFFER_H_
