#pragma once

/**
 * @file        emitter.h
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 *
 * @brief       In this header are defined functions to emit to a stream
 *              diagnostics.
 */

#ifndef CALC_DIAGNOSTIC_EMITTER_H_
#define CALC_DIAGNOSTIC_EMITTER_H_

#include "calc/base/file.h"

#include "calc/diagnostic/diagnostics.h"

CALC_C_HEADER_BEGIN

/// @brief Function type for diagnostics emitter function.
typedef int (*CalcDiagnosticEmitterFunc_t)(CalcDiagnostic_t *const, FILE *const, bool_t);

/// @brief Emits on the selected stream a textual representation
///        of the specified location.
/// @param location A pointer to the structure containing
///                 location infos.
/// @param stream The stream on which write the text.
/// @param useColors Specifies to use or not colored output messages.
/// @return The number of characters written.
CALC_API int CALC_STDCALL calcEmitDiagnosticLocation(CalcDiagnosticLocation_t *const diagnosticLocation, FILE *const stream, bool_t useColors);
/// @brief Emits on the selected stream a textual representation
///        of the specified location with the reference to the
///        line form which is originated the diagnostic.
/// @param hint Diangostic hint to display with diagnostic trace.
/// @param location A pointer to the structure containing
///                 location infos.
/// @param stream The stream on which write the text.
/// @param useColors Specifies to use or not colored output messages.
/// @return The number of characters written.
CALC_API int CALC_STDCALL calcEmitDiagnosticTrace(char *const hint, CalcDiagnosticLocation_t *const diagnosticLocation, FILE *const stream, bool_t useColors);

/// @brief Emits on the selected stream a textual representation
///        of the specified diagnostics. This function handles
///        each NULL possibility.
/// @param diagnostic A pointer tot he structure containing the
///                   diagnostic infos.
/// @param stream The stream on which write the text.
/// @param useColors Specifies to use or not colored output messages.
/// @return The number of characters written.
CALC_API int CALC_STDCALL calcEmitDiagnostic(CalcDiagnostic_t *const diagnostic, FILE *const stream, bool_t useColors);

// Diagnostics Emitter

/// @brief Enumerates possible states (SUCCESS or FAILURE) of the
///        result of an operation.
typedef enum _CalcResult
{
    /// @brief Success status.
    CALC_SUCCESS = TRUE,
    /// @brief Failure status.
    CALC_FAILURE = FALSE,
} CalcResult_t;

/// @brief Enumerates each possible diagnsotic emitter status.
typedef enum _CalcDiagnosticEmitterStatus
{
    /// @brief When status is success there are no reported
    ///        errors (maybe notes and warnings).
    CALC_DIAGNOSTIC_EMITTER_STATUS_SUCCESS = 0,
    /// @brief When status is failure there is at least one
    ///        reported error, but not fatals.
    CALC_DIAGNOSTIC_EMITTER_STATUS_FAILURE = 1,
    /// @brief Status is set to aborted only when is reported
    ///        a fatal error. As the name say, when is set this
    ///        status the execution is killed.
    CALC_DIAGNOSTIC_EMITTER_STATUS_ABORTED = 3,
} CalcDiagnosticEmitterStatus_t;

/// @brief Diagnostic emitter data structure. This structure
///        manages each error, warning and note, how they're
///        displayed and where, and also the execution status
///        of the process.
typedef struct _CalcDiagnosticEmitter
{
    /// @brief The stream on which will be emitted messages.
    FILE                         *stream;
    /// @brief Emitter function. Defines how are emitted messages
    ///        on the stream.
    CalcDiagnosticEmitterFunc_t   emitter;
    /// @brief A pointer to the top diagnostic. Diagnostics are
    ///        listed and emitted chronologically, this is the
    ///        first that will be displayed and disposed.
    CalcDiagnostic_t             *top;
    /// @brief The current status of the emitter.
    CalcDiagnosticEmitterStatus_t status;
    /// @brief The number of warnings.
    uint16_t                      warningCount;
    /// @brief The number of errors (with fatals and errnos).
    uint16_t                      errorCount;
    /// @brief Specifies to use or not colored output messages.
    bool_t                        useColors;
} CalcDiagnosticEmitter_t;

/// @brief Creates a new diagnostic emitter specifing the stream
///        and the emitter fuction. By default (so when is NULL)
///        the emitter function is the above declared calcEmitDiagnostic.
/// @param errorStream The stream on which emit the diagnostics.
/// @param emitterFunction The emitter function that manages how
///                        are emitted diagnostics on the stream.
/// @return A pointer to the new allocated diagnostic emitter.
CALC_API CalcDiagnosticEmitter_t *CALC_STDCALL calcCreateDiagnosticEmitter(FILE *const errorStream, CalcDiagnosticEmitterFunc_t emitterFunction);
/// @brief Creates a diagnostic emitter with the standard error stream
///        and the default emitter function: calcEmitDiagnostic.
CALC_API CalcDiagnosticEmitter_t *CALC_STDCALL calcGetDefaultDiagnosticEmitter(void);

/// @brief Pushes a diagnostic in the specified emitter.
/// @param emitter The emitter on which push the diagnostic.
/// @param diagnostic The diagnostic to push.
CALC_API CalcResult_t CALC_STDCALL calcDiagnosticEmitterPush(CalcDiagnosticEmitter_t *const emitter, CalcDiagnostic_t *const diagnostic);
/// @brief Emits and disposes the top diagnostic.
/// @param emitter The emitter form which emit.
/// @return The number of written characters.
CALC_API int CALC_STDCALL calcDiagnosticEmitterEmit(CalcDiagnosticEmitter_t *const emitter);
/// @brief Emits and disposes each diagnostic pushed in the emitter.
/// @param emitter The emitter form which emit.
/// @return The number of written characters.
CALC_API int CALC_STDCALL calcDiagnosticEmitterEmitAll(CalcDiagnosticEmitter_t *const emitter);

/// @brief Reports an error to a diagnostic emitter.
/// @param emitter The emitter form which emit.
/// @param level Diagnostic level to choose what do after displayed
///              the message.
/// @param code Diagnostic code to display with diagnostic message.
/// @param location Location from which the problem has been originated.
/// @param message Diangostic message to display with diagnostic code.
/// @param cleanupMessage Specifies that on deletion of the diagnostic
///                       the message must be deleted too.
/// @param hint Diangostic hint to display with diagnostic trace.
/// @param cleanupMessage Specifies that on deletion of the diagnostic
///                       the hint must be deleted too.
CALC_API_INLINE CalcResult_t calcDiagnosticEmitterReport(CalcDiagnosticEmitter_t *const emitter, CalcDiagnosticLevel_t level, CalcDiagnosticCode_t code, CalcDiagnosticLocation_t *const location, char *const message, bool_t cleanupMessage, char *const hint, bool_t cleanupHint)
{
    return calcDiagnosticEmitterPush(emitter, calcCreateDiagnostic(level, code, location, message, cleanupMessage, hint, cleanupHint));
}

/// @brief Emits and disposes each diagnostic pushed in the emitter,
///        prints the count of notes, warnings and errors and deletes
///        the emitter with all its content.
/// @param emitter The emitter on which operate.
/// @return The number of written characters.
CALC_API int CALC_STDCALL calcDiagnosticEmitterEpilogue(CalcDiagnosticEmitter_t *const emitter);

/// @brief Clears each diagnostic pushed in the emitter.
/// @param emitter The emitter to clear.
/// @return The function is succeful when is deleted at least one
///         item.
CALC_API CalcResult_t CALC_STDCALL calcDiagnosticEmitterClear(CalcDiagnosticEmitter_t *const emitter);
/// @brief Closes the stream of an emitter.
/// @param emitter The emitter to close.
/// @return The function is succeful whem the stream is closed
///         correctly.
CALC_API CalcResult_t CALC_STDCALL calcDiagnosticEmitterClose(CalcDiagnosticEmitter_t *const emitter);

/// @brief Deletes a diagnostic emitter clearing and closing
///        it.
/// @param emitter The emitter to delete.
CALC_API void CALC_STDCALL calcDeleteDiagnosticEmitter(CalcDiagnosticEmitter_t *const emitter);

CALC_C_HEADER_END

#endif // CALC_DIAGNOSTIC_EMITTER_H_
