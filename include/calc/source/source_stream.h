#pragma once

/**
 * @file        source_stream.h
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 *
 * @brief       In this header are defined structures and functions to
 *              create, delete and manipulate source streams.
 */

#ifndef CALC_SOURCE_SOURCE_STREAM_H_
#define CALC_SOURCE_SOURCE_STREAM_H_

#include "calc/source/source_buffer.h"
#include "calc/source/source_location.h"

CALC_C_HEADER_BEGIN

/// @brief Source stream data structure.
typedef struct _CalcSourceStream
{
    /// @brief The textual path to the source buffer, or simply the name
    ///        of the source stream.
    char                *path;
    /// @brief A pointer to an open file stream to use to refill the source
    ///        buffer when the cursor reaches the end.
    FILE                *stream;
    /// @brief When it's set to TRUE the source file is treated as an
    ///        interactive stream and is red line by line.
    bool_t               isStdin;
    /// @brief When it's set to TRUE means that the source stream uses as
    ///        source a NUL-terminated string of characters.
    bool_t               isText;
    /// @brief When it's set to TRUE means that the source file is alredy
    ///        open.
    bool_t               isOpen;
    /// @brief When it's set to TRUE the path string is released on stream
    ///        deletion.
    bool_t               cleanup;
    /// @brief A pointer to the source buffer data structure that stores
    ///        the content of the stream.
    CalcSourceBuffer_t  *buffer;
    /// @brief The location in the source file stream.
    CalcSourceLocation_t streamLocation;
    /// @brief The current lexeme beginning location.
    CalcSourceLocation_t beginLocation;
    /// @brief The current lexeme ending location.
    CalcSourceLocation_t forwardLocation;
} CalcSourceStream_t;

/// @brief Creates a new source stream using as a source to fill the buffer
///        a NUL-terminated string of characters.
/// @param text The string of characters o wrap into the new source stream.
/// @return A pointer to the new source stream.
CALC_API CalcSourceStream_t *CALC_STDCALL calcCreateSourceStreamFromText(const char *const text);
/// @brief Creates a new source stream filling the buffer only once loading
///        the full content of the specified file.
/// @param path The path to the file to load.
/// @return A pointer to the new source stream.
CALC_API CalcSourceStream_t *CALC_STDCALL calcCreateSourceStreamFromFile(const char *const path, bool_t cleanupPath);

/// @brief Creates a new source stream filling the source buffer only once
///        loading the full content of specified stream.
/// @param stream The file stream to load.
/// @return A pointer to the new source stream.
CALC_API CalcSourceStream_t *CALC_STDCALL calcCreateSourceStreamFromStream(FILE *const stream);

/// @brief Opens a new source stream from a file specified by tha path
///        parameter.
/// @param path The path to the file to open.
/// @return A pointer to the new source stream.
CALC_API CalcSourceStream_t *CALC_STDCALL calcOpenSourceStream(const char *const path, bool_t cleanupPath);
/// @brief Opens the source stream that uses stdin as source file. This
///        function is a special case of the calcOpenSourceStream function.
/// @return A pointer to the new source stream.
CALC_API CalcSourceStream_t *CALC_STDCALL calcOpenStandardSourceStream(void);

/// @brief Closes an open source stream.
/// @param sourceStream A pointer to the source stream to close.
/// @return TRUE when the stream is closed succefully, FALSE in the other cases.
CALC_API bool_t CALC_STDCALL calcCloseSourceStream(CalcSourceStream_t *const sourceStream);
/// @brief Clear the content of the source buffer of the specified source stream-
/// @param sourceStream A pointer to the source stream to clear.
/// @return TRUE when the stream is cleared succefully, FALSE in the other cases.
CALC_API bool_t CALC_STDCALL calcClearSourceStream(CalcSourceStream_t *const sourceStream);

/// @brief Deletes a source stream, closing the file stream, clearing the source
///        buffer and releasing the resources associated to it.
/// @param sourceStream A pointer to the source stream to delete.
CALC_API void CALC_STDCALL calcDeleteSourceStream(CalcSourceStream_t *const sourceStream);

CALC_C_HEADER_END

#endif // CALC_SOURCE_SOURCE_STREAM_H_
