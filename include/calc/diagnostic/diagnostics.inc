/**
 * @file        diagnsotics.inc
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 *
 * @brief       This file is an x-macro header file, designed to be
 *              included more than once. Its use can change depending
 *              how is defined the corresponed x-macro.
 * 
 *              To use this header is necessary to define the following
 *              macro:
 * 
 *              - calcDefineDiagnosticCode(name, displayName, level, defaultFormat)
 * 
 *                Defines a sepcific kind of diagnostics specifing its enum
 *                name, display name, error level (NOTE, WARNING, ERROR or
 *                FATAL) and the default format in printf style.
 */

#ifndef calcDefineDiagnosticCode
#   error 'calcDefineDiagnosticCode' macro must be defined here.
#endif // CHECK calcDefineDiagnosticCode

 /// @brief UnhandledError: An unhandled error has been reported.
calcDefineDiagnosticCode(CE0001, "UnhandledError", ERROR, "an unhandled error has been reported")
