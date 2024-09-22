#pragma once

/**
 * @file        utf8.h
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 *
 *              Copyright (c) 2014-2021 by Steven G. Johnson, Jiahao Chen,
 *              Tony Kelman, Jonas Fonseca, and other contributors listed
 *              in the git history.
 *
 *              This file (and its .c implementation) is partially derived
 *              from utf8proc library:
 *
 *              https://github.com/JuliaStrings/utf8proc.git
 *
 * @brief       In this header are defined macros, constants and functions
 *              to deal with Unicode characters: Unicode normalization,
 *              case-folding, and other operations for strings in the UTF-8
 *              encoding, supporting up-to-date Unicode versions.
 */

#ifndef CALC_BASE_UTF8_H_
#define CALC_BASE_UTF8_H_

#include "calc/base/bits.h"
#include "calc/base/bool.h"
#include "calc/base/error.h"

CALC_C_HEADER_BEGIN

/// @brief Option flags used by several functions in the library.
typedef enum _utf8_option
{
    /// @brief The given UTF-8 input is NULL terminated.
    UTF8_NULLTERM = (1 << 0),
    /// @brief Unicode Versioning Stability has to be respected.
    UTF8_STABLE = (1 << 1),
    /// @brief Compatibility decomposition (i.e. formatting information is lost).
    UTF8_COMPAT = (1 << 2),
    /// @brief Return a result with decomposed characters.
    UTF8_COMPOSE = (1 << 3),
    /// @brief Return a result with decomposed characters.
    UTF8_DECOMPOSE = (1 << 4),
    /// @brief Strip "default ignorable characters" such as SOFT-HYPHEN or ZERO-WIDTH-SPACE.
    UTF8_IGNORE = (1 << 5),
    /// @brief Return an error, if the input contains unassigned codepoints.
    UTF8_REJECTNA = (1 << 6),
    /// @brief Indicating that NLF-sequences (LF, CRLF, CR, NEL) are representing a
    ///        line break, and should be converted to the codepoint for line
    ///        separation (LS).
    UTF8_NLF2LS = (1 << 7),
    /// @brief Indicating that NLF-sequences are representing a paragraph break, and
    ///        should be converted to the codepoint for paragraph separation
    ///        (PS).
    UTF8_NLF2PS = (1 << 8),
    /// @brief Indicating that the meaning of NLF-sequences is unknown.
    UTF8_NLF2LF = (UTF8_NLF2LS | UTF8_NLF2PS),
    /// @brief Strips and/or convers control characters.
    ///
    /// NLF-sequences are transformed into space, except if one of the
    /// NLF2LS/PS/LF options is given. HorizontalTab (HT) and FormFeed (FF)
    /// are treated as a NLF-sequence in this case.  All other control
    /// characters are simply removed.
    ///
    UTF8_STRIPCC = (1 << 9),
    /// @brief Performs unicode case folding, to be able to do a case-insensitive
    ///        string comparison.
    UTF8_CASEFOLD = (1 << 10),
    /// @brief Inserts 0xFF bytes at the beginning of each sequence which is
    ///        representing a single grapheme cluster (see UAX#29).
    UTF8_CHARBOUND = (1 << 11),
    /// @brief Lumps certain characters together.
    ///
    /// E.g. HYPHEN U+2010 and MINUS U+2212 to ASCII "-". See lump.md for details.
    ///
    /// If NLF2LF is set, this includes a transformation of paragraph and
    /// line separators to ASCII line-feed (LF).
    ///
    UTF8_LUMP = (1 << 12),
    /// @brief Strips all character markings.
    ///
    /// This includes non-spacing, spacing and enclosing (i.e. accents).
    ///
    /// @note This option works only with UTF8_COMPOSE or
    ///       UTF8_DECOMPOSE.
    ///
    UTF8_STRIPMARK = (1 << 13),
    /// @brief Strip unassigned codepoints.
    UTF8_STRIPNA = (1 << 14),
} utf8_option_t;

/// @name Error codes
/// @{
/// Memory could not be allocated.
#define UTF8_ERROR_NOMEM -1
/// The given string is too long to be processed.
#define UTF8_ERROR_OVERFLOW -2
/// The given string is not a legal UTF-8 string.
#define UTF8_ERROR_INVALIDUTF8 -3
/// The @ref UTF8_REJECTNA flag was set and an unassigned codepoint was found.
#define UTF8_ERROR_NOTASSIGNED -4
/// Invalid options have been used.
#define UTF8_ERROR_INVALIDOPTS -5
/// @}

/// @brief Struct containing information about a codepoint.
typedef struct _utf8_property_struct
{
    /// @brief  Unicode category.
    uint16_t category;
    uint16_t combining_class;
    /// @brief Bidirectional class.
    uint16_t bidi_class;
    /// @brief  Decomposition type.
    uint16_t decomp_type;
    uint16_t decomp_seqindex;
    uint16_t casefold_seqindex;
    uint16_t uppercase_seqindex;
    uint16_t lowercase_seqindex;
    uint16_t titlecase_seqindex;
    uint16_t comb_index;
    uint32_t bidi_mirrored : 1;
    uint32_t comp_exclusion : 1;
    /// @brief Can this codepoint be ignored?
    ///
    /// Used by utf8_decompose_char() when UTF8_IGNORE is
    /// passed as an option.
    ///
    uint32_t ignorable : 1;
    uint32_t control_boundary : 1;
    /// @brief The width of the codepoint.
    uint32_t charwidth : 2;
    /// @brief East Asian width class A.
    uint32_t ambiguous_width : 1;
    uint32_t pad : 1;
    uint32_t boundclass : 6;
    uint32_t indic_conjunct_break : 2;
} utf8_property_t;

/// @brief Unicode categories.
typedef enum _utf8_category
{
    UTF8_CATEGORY_CN = 0,  /// @brief Other, not assigned
    UTF8_CATEGORY_LU = 1,  /// @brief Letter, uppercase
    UTF8_CATEGORY_LL = 2,  /// @brief Letter, lowercase
    UTF8_CATEGORY_LT = 3,  /// @brief Letter, titlecase
    UTF8_CATEGORY_LM = 4,  /// @brief Letter, modifier
    UTF8_CATEGORY_LO = 5,  /// @brief Letter, other
    UTF8_CATEGORY_MN = 6,  /// @brief Mark, nonspacing
    UTF8_CATEGORY_MC = 7,  /// @brief Mark, spacing combining
    UTF8_CATEGORY_ME = 8,  /// @brief Mark, enclosing
    UTF8_CATEGORY_ND = 9,  /// @brief Number, decimal digi
    UTF8_CATEGORY_NL = 10, /// @brief Number, letter
    UTF8_CATEGORY_NO = 11, /// @brief Number, other
    UTF8_CATEGORY_PC = 12, /// @brief Punctuation, connector
    UTF8_CATEGORY_PD = 13, /// @brief Punctuation, dash
    UTF8_CATEGORY_PS = 14, /// @brief Punctuation, open
    UTF8_CATEGORY_PE = 15, /// @brief Punctuation, close
    UTF8_CATEGORY_PI = 16, /// @brief Punctuation, initial quote
    UTF8_CATEGORY_PF = 17, /// @brief Punctuation, final quote
    UTF8_CATEGORY_PO = 18, /// @brief Punctuation, other
    UTF8_CATEGORY_SM = 19, /// @brief Symbol, math
    UTF8_CATEGORY_SC = 20, /// @brief Symbol, currency
    UTF8_CATEGORY_SK = 21, /// @brief Symbol, modifier
    UTF8_CATEGORY_SO = 22, /// @brief Symbol, other
    UTF8_CATEGORY_ZS = 23, /// @brief Separator, space
    UTF8_CATEGORY_ZL = 24, /// @brief Separator, line
    UTF8_CATEGORY_ZP = 25, /// @brief Separator, paragraph
    UTF8_CATEGORY_CC = 26, /// @brief Other, control
    UTF8_CATEGORY_CF = 27, /// @brief Other, format
    UTF8_CATEGORY_CS = 28, /// @brief Other, surrogate
    UTF8_CATEGORY_CO = 29, /// @brief Other, private use
} utf8_category_t;

/// @brief Bidirectional character classes.
typedef enum _utf8_bidi_class
{
    UTF8_BIDI_CLASS_L = 1,    /// @brief Left-to-Right
    UTF8_BIDI_CLASS_LRE = 2,  /// @brief Left-to-Right Embedding
    UTF8_BIDI_CLASS_LRO = 3,  /// @brief Left-to-Right Override
    UTF8_BIDI_CLASS_R = 4,    /// @brief Right-to-Left
    UTF8_BIDI_CLASS_AL = 5,   /// @brief Right-to-Left Arabic
    UTF8_BIDI_CLASS_RLE = 6,  /// @brief Right-to-Left Embedding
    UTF8_BIDI_CLASS_RLO = 7,  /// @brief Right-to-Left Override
    UTF8_BIDI_CLASS_PDF = 8,  /// @brief Pop Directional Format
    UTF8_BIDI_CLASS_EN = 9,   /// @brief European Number
    UTF8_BIDI_CLASS_ES = 10,  /// @brief European Separator
    UTF8_BIDI_CLASS_ET = 11,  /// @brief European Number Terminator
    UTF8_BIDI_CLASS_AN = 12,  /// @brief Arabic Number
    UTF8_BIDI_CLASS_CS = 13,  /// @brief Common Number Separator
    UTF8_BIDI_CLASS_NSM = 14, /// @brief Nonspacing Mark
    UTF8_BIDI_CLASS_BN = 15,  /// @brief Boundary Neutral
    UTF8_BIDI_CLASS_B = 16,   /// @brief Paragraph Separator
    UTF8_BIDI_CLASS_S = 17,   /// @brief Segment Separator
    UTF8_BIDI_CLASS_WS = 18,  /// @brief Whitespace
    UTF8_BIDI_CLASS_ON = 19,  /// @brief Other Neutrals
    UTF8_BIDI_CLASS_LRI = 20, /// @brief Left-to-Right Isolate
    UTF8_BIDI_CLASS_RLI = 21, /// @brief Right-to-Left Isolate
    UTF8_BIDI_CLASS_FSI = 22, /// @brief First Strong Isolate
    UTF8_BIDI_CLASS_PDI = 23, /// @brief Pop Directional Isolate
} utf8_bidi_class_t;

/// @brief Decomposition type.
typedef enum _utf8_decomp_type
{
    UTF8_DECOMP_TYPE_FONT = 1,      /// @brief Font
    UTF8_DECOMP_TYPE_NOBREAK = 2,   /// @brief Nobreak
    UTF8_DECOMP_TYPE_INITIAL = 3,   /// @brief Initial
    UTF8_DECOMP_TYPE_MEDIAL = 4,    /// @brief Medial
    UTF8_DECOMP_TYPE_FINAL = 5,     /// @brief Final
    UTF8_DECOMP_TYPE_ISOLATED = 6,  /// @brief Isolated
    UTF8_DECOMP_TYPE_CIRCLE = 7,    /// @brief Circle
    UTF8_DECOMP_TYPE_SUPER = 8,     /// @brief Super
    UTF8_DECOMP_TYPE_SUB = 9,       /// @brief Sub
    UTF8_DECOMP_TYPE_VERTICAL = 10, /// @brief Vertical
    UTF8_DECOMP_TYPE_WIDE = 11,     /// @brief Wide
    UTF8_DECOMP_TYPE_NARROW = 12,   /// @brief Narrow
    UTF8_DECOMP_TYPE_SMALL = 13,    /// @brief Small
    UTF8_DECOMP_TYPE_SQUARE = 14,   /// @brief Square
    UTF8_DECOMP_TYPE_FRACTION = 15, /// @brief Fraction
    UTF8_DECOMP_TYPE_COMPAT = 16,   /// @brief Compat
} utf8_decomp_type_t;

/// @brief Boundclass property. (TR29)
typedef enum _utf8_boundclass
{
    UTF8_BOUNDCLASS_START = 0,               /// @brief Start
    UTF8_BOUNDCLASS_OTHER = 1,               /// @brief Other
    UTF8_BOUNDCLASS_CR = 2,                  /// @brief Cr
    UTF8_BOUNDCLASS_LF = 3,                  /// @brief Lf
    UTF8_BOUNDCLASS_CONTROL = 4,             /// @brief Control
    UTF8_BOUNDCLASS_EXTEND = 5,              /// @brief Extend
    UTF8_BOUNDCLASS_L = 6,                   /// @brief L
    UTF8_BOUNDCLASS_V = 7,                   /// @brief V
    UTF8_BOUNDCLASS_T = 8,                   /// @brief T
    UTF8_BOUNDCLASS_LV = 9,                  /// @brief Lv
    UTF8_BOUNDCLASS_LVT = 10,                /// @brief Lvt
    UTF8_BOUNDCLASS_REGIONAL_INDICATOR = 11, /// @brief Regional indicator
    UTF8_BOUNDCLASS_SPACINGMARK = 12,        /// @brief Spacingmark
    UTF8_BOUNDCLASS_PREPEND = 13,            /// @brief Prepend
    UTF8_BOUNDCLASS_ZWJ = 14,                /// @brief Zero Width Joiner

    /* the following are no longer used in Unicode 11, but we keep
     the constants here for backward compatibility */
    UTF8_BOUNDCLASS_E_BASE             = 15, /**< Emoji Base */
    UTF8_BOUNDCLASS_E_MODIFIER         = 16, /**< Emoji Modifier */
    UTF8_BOUNDCLASS_GLUE_AFTER_ZWJ     = 17, /**< Glue_After_ZWJ */
    UTF8_BOUNDCLASS_E_BASE_GAZ         = 18, /**< E_BASE + GLUE_AFTER_ZJW */

    /* the Extended_Pictographic property is used in the Unicode 11
     grapheme-boundary rules, so we store it in the boundclass field */
    UTF8_BOUNDCLASS_EXTENDED_PICTOGRAPHIC = 19,
    UTF8_BOUNDCLASS_E_ZWG = 20, /* UTF8_BOUNDCLASS_EXTENDED_PICTOGRAPHIC + ZWJ */
} utf8_boundclass_t;

/// @brief Indic_Conjunct_Break property. (TR44)
typedef enum _utf8_indic_conjunct_break
{
    UTF8_INDIC_CONJUNCT_BREAK_NONE = 0,
    UTF8_INDIC_CONJUNCT_BREAK_LINKER = 1,
    UTF8_INDIC_CONJUNCT_BREAK_CONSONANT = 2,
    UTF8_INDIC_CONJUNCT_BREAK_EXTEND = 3,
} utf8_indic_conjunct_break_t;

/// @brief Function pointer type passed to utf8_map_custom() and
///        utf8_decompose_custom(), which is used to specify a user-defined
///        mapping of codepoints to be applied in conjunction with other mappings.
typedef int32_t (*utf8_custom_func_t)(int32_t codepoint, void *data);

/// @brief Array containing the byte lengths of a UTF-8 encoded codepoint based
///        on the first byte.
CALC_EXTERN const int8_t utf8_utf8class[256];

/// @brief Returns the utf8proc API version as a string MAJOR.MINOR.PATCH
///        (http://semver.org format), possibly with a "-dev" suffix for
///        development versions.
CALC_EXTERN const char *utf8_version(void);

/// @brief Returns the utf8proc supported Unicode version as a string MAJOR.MINOR.PATCH.
CALC_EXTERN const char *utf8_unicode_version(void);

/// @brief Returns an informative error string for the given utf8proc error code
///        (e.g. the error codes returned by utf8_map()).
CALC_EXTERN const char *utf8_errmsg(ssize_t errcode);

/// @brief Reads a single codepoint from the UTF-8 sequence being pointed to by `str`.
///        The maximum number of bytes read is `strlen`, unless `strlen` is
///        negative (in which case up to 4 bytes are read).
///
///        If a valid codepoint could be read, it is stored in the variable
///        pointed to by `codepoint_ref`, otherwise that variable will be set to -1.
///        In case of success, the number of bytes read is returned; otherwise, a
///        negative error code is returned.
///
CALC_EXTERN ssize_t utf8_iterate(const uint8_t *str, ssize_t strlen, int32_t *codepoint_ref);

/// @brief Check if a codepoint is valid (regardless of whether it has been
///        assigned a value by the current Unicode standard).
/// @return 1 if the given `codepoint` is valid and otherwise return 0.
CALC_EXTERN bool_t utf8_codepoint_valid(int32_t codepoint);

/// @brief Encodes the codepoint as an UTF-8 string in the byte array pointed
///        to by `dst`. This array must be at least 4 bytes long.
///
///        In case of success the number of bytes written is returned, and
///        otherwise 0 is returned.
///
///        This function does not check whether `codepoint` is valid Unicode.
///
CALC_EXTERN ssize_t utf8_encode_char(int32_t codepoint, uint8_t *dst);

/// @brief Look up the properties for a given codepoint.
///
/// @param codepoint The Unicode codepoint.
///
/// @returns A pointer to a (constant) struct containing information about
///          the codepoint.
///
/// If the codepoint is unassigned or invalid, a pointer to a special struct is
/// returned in which `category` is 0 (UTF8_CATEGORY_CN).
///
CALC_EXTERN const utf8_property_t *utf8_get_property(int32_t codepoint);

/// @brief Decompose a codepoint into an array of codepoints.
///
/// @param codepoint the codepoint.
/// @param dst the destination buffer.
/// @param bufsize the size of the destination buffer.
/// @param options one or more of the following flags:
/// - UTF8_REJECTNA  - return an error `codepoint` is unassigned
/// - UTF8_IGNORE    - strip "default ignorable" codepoints
/// - UTF8_CASEFOLD  - apply Unicode casefolding
/// - UTF8_COMPAT    - replace certain codepoints with their
///                        compatibility decomposition
/// - UTF8_CHARBOUND - insert 0xFF bytes before each grapheme cluster
/// - UTF8_LUMP      - lump certain different codepoints together
/// - UTF8_STRIPMARK - remove all character marks
/// - UTF8_STRIPNA   - remove unassigned codepoints
/// @param last_boundclass Pointer to an integer variable containing
/// the previous codepoint's (boundclass + indic_conjunct_break << 1) if the UTF8_CHARBOUND
/// option is used.  If the string is being processed in order, this can be initialized to 0 for
/// the beginning of the string, and is thereafter updated automatically.  Otherwise, this parameter is ignored.
///
/// @return In case of success, the number of codepoints written is returned; in case
///         of an error, a negative error code is returned (utf8_errmsg()).
///
/// If the number of written codepoints would be bigger than `bufsize`, the
/// required buffer size is returned, while the buffer will be overwritten with
/// undefined data.
///
CALC_EXTERN ssize_t utf8_decompose_char(
    int32_t codepoint, int32_t *dst, ssize_t bufsize,
    utf8_option_t options, int *last_boundclass);

/// @brief The same as utf8_decompose_char(), but acts on a whole UTF-8
///        string and orders the decomposed sequences correctly.
///
/// If the UTF8_NULLTERM flag in `options` is set, processing
/// will be stopped, when a NULL byte is encountered, otherwise `strlen`
/// bytes are processed.  The result (in the form of 32-bit unicode
/// codepoints) is written into the buffer being pointed to by
/// `buffer` (which must contain at least `bufsize` entries).  In case of
/// success, the number of codepoints written is returned; in case of an
/// error, a negative error code is returned (utf8_errmsg()).
/// See utf8_decompose_custom() to supply additional transformations.
///
/// If the number of written codepoints would be bigger than `bufsize`, the
/// required buffer size is returned, while the buffer will be overwritten with
/// undefined data.
///
CALC_EXTERN ssize_t utf8_decompose(
    const uint8_t *str, ssize_t strlen,
    int32_t *buffer, ssize_t bufsize, utf8_option_t options);

/// @brief The same as utf8_decompose(), but also takes a `custom_func` mapping function
///        that is called on each codepoint in `str` before any other transformations
///        (along with a `custom_data` pointer that is passed through to `custom_func`).
///        The `custom_func` argument is ignored if it is `NULL`.  See also utf8_map_custom().
CALC_EXTERN ssize_t utf8_decompose_custom(
    const uint8_t *str, ssize_t strlen,
    int32_t *buffer, ssize_t bufsize, utf8_option_t options,
    utf8_custom_func_t custom_func, void *custom_data);

/// @brief Normalizes the sequence of `length` codepoints pointed to by `buffer`
///        in-place (i.e., the result is also stored in `buffer`).
///
/// @param buffer the (native-endian UTF-32) unicode codepoints to re-encode.
/// @param length the length (in codepoints) of the buffer.
/// @param options a bitwise or (`|`) of one or more of the following flags:
/// - UTF8_NLF2LS  - convert LF, CRLF, CR and NEL into LS
/// - UTF8_NLF2PS  - convert LF, CRLF, CR and NEL into PS
/// - UTF8_NLF2LF  - convert LF, CRLF, CR and NEL into LF
/// - UTF8_STRIPCC - strip or convert all non-affected control characters
/// - UTF8_COMPOSE - try to combine decomposed codepoints into composite
///                      codepoints
/// - UTF8_STABLE  - prohibit combining characters that would violate
///                      the unicode versioning stability
///
/// @return In case of success, the length (in codepoints) of the normalized UTF-32 string is
///         returned; otherwise, a negative error code is returned (utf8_errmsg()).
///
/// @warning The entries of the array pointed to by `str` have to be in the
///          range `0x0000` to `0x10FFFF`. Otherwise, the program might crash!
///
CALC_EXTERN ssize_t utf8_normalize_utf32(int32_t *buffer, ssize_t length, utf8_option_t options);

/// @brief Reencodes the sequence of `length` codepoints pointed to by `buffer`
///        UTF-8 data in-place (i.e., the result is also stored in `buffer`).
///        Can optionally normalize the UTF-32 sequence prior to UTF-8 conversion.
///
/// @param buffer the (native-endian UTF-32) unicode codepoints to re-encode.
/// @param length the length (in codepoints) of the buffer.
/// @param options a bitwise or (`|`) of one or more of the following flags:
/// - UTF8_NLF2LS  - convert LF, CRLF, CR and NEL into LS
/// - UTF8_NLF2PS  - convert LF, CRLF, CR and NEL into PS
/// - UTF8_NLF2LF  - convert LF, CRLF, CR and NEL into LF
/// - UTF8_STRIPCC - strip or convert all non-affected control characters
/// - UTF8_COMPOSE - try to combine decomposed codepoints into composite
///                      codepoints
/// - UTF8_STABLE  - prohibit combining characters that would violate
///                      the unicode versioning stability
/// - UTF8_CHARBOUND - insert 0xFF bytes before each grapheme cluster
///
/// @return In case of success, the length (in bytes) of the resulting nul-terminated
///         UTF-8 string is returned; otherwise, a negative error code is returned
///         (utf8_errmsg()).
///
/// @warning The amount of free space pointed to by `buffer` must
///          exceed the amount of the input data by one byte, and the
///          entries of the array pointed to by `str` have to be in the
///          range `0x0000` to `0x10FFFF`. Otherwise, the program might crash!
///
CALC_EXTERN ssize_t utf8_reencode(int32_t *buffer, ssize_t length, utf8_option_t options);

/// @brief Given a pair of consecutive codepoints, return whether a grapheme break is
///        permitted between them (as defined by the extended grapheme clusters in UAX#29).
///
/// @param codepoint1 The first codepoint.
/// @param codepoint2 The second codepoint, occurring consecutively after `codepoint1`.
/// @param state Beginning with Version 29 (Unicode 9.0.0), this algorithm requires
///              state to break graphemes. This state can be passed in as a pointer
///              in the `state` argument and should initially be set to 0. If the
///              state is not passed in (i.e. a null pointer is passed), UAX#29 rules
///              GB10/12/13 which require this state will not be applied, essentially
///              matching the rules in Unicode 8.0.0.
///
/// @warning If the state parameter is used, `utf8_grapheme_break_stateful` must
///          be called IN ORDER on ALL potential breaks in a string.  However, it
///          is safe to reset the state to zero after a grapheme break.
///
CALC_EXTERN bool_t utf8_grapheme_break_stateful(
    int32_t codepoint1, int32_t codepoint2, int32_t *state);

/// @brief Same as utf8_grapheme_break_stateful(), except without support for the
///        Unicode 9 additions to the algorithm. Supported for legacy reasons.
CALC_EXTERN bool_t utf8_grapheme_break(
    int32_t codepoint1, int32_t codepoint2);

/// @brief Given a codepoint `c`, return the codepoint of the corresponding
///        lower-case character, if any; otherwise (if there is no lower-case
///        variant, or if `c` is not a valid codepoint) return `c`.
CALC_EXTERN int32_t utf8_tolower(int32_t c);

/// @brief Given a codepoint `c`, return the codepoint of the corresponding
///        upper-case character, if any; otherwise (if there is no upper-case
///        variant, or if `c` is not a valid codepoint) return `c`.
CALC_EXTERN int32_t utf8_toupper(int32_t c);

/// @brief Given a codepoint `c`, return the codepoint of the corresponding
///        title-case character, if any; otherwise (if there is no title-case
///        variant, or if `c` is not a valid codepoint) return `c`.
CALC_EXTERN int32_t utf8_totitle(int32_t c);

/// @brief Given a codepoint `c`, return `1` if the codepoint corresponds to a lower-case character
///        and `0` otherwise.
CALC_EXTERN int utf8_islower(int32_t c);

/// @brief Given a codepoint `c`, return `1` if the codepoint corresponds to an upper-case character
///        and `0` otherwise.
CALC_EXTERN int utf8_isupper(int32_t c);

/// @brief Given a codepoint, return a character width analogous to `wcwidth(codepoint)`,
///        except that a width of 0 is returned for non-printable codepoints
///        instead of -1 as in `wcwidth`.
///
/// @note If you want to check for particular types of non-printable characters,
///       (analogous to `isprint` or `iscntrl`), use utf8_category().
///
CALC_EXTERN int utf8_charwidth(int32_t codepoint);

/// @brief Given a codepoint, return whether it has East Asian width class A (Ambiguous)
///
/// Codepoints with this property are considered to have charwidth 1 (if they are printable)
/// but some East Asian fonts render them as double width.
///
CALC_EXTERN bool_t utf8_charwidth_ambiguous(int32_t codepoint);

/// @brief Return the Unicode category for the codepoint (one of the
///        utf8_category_t constants.)
CALC_EXTERN utf8_category_t utf8_category(int32_t codepoint);

/// @brief Return the two-letter (nul-terminated) Unicode category string for
///        the codepoint (e.g. `"Lu"` or `"Co"`).
CALC_EXTERN const char *utf8_category_string(int32_t codepoint);

/// @brief Maps the given UTF-8 string pointed to by `str` to a new UTF-8
///        string, allocated dynamically by `malloc` and returned via `dstptr`.
///
///        If the UTF8_NULLTERM flag in the `options` field is set,
///        the length is determined by a NULL terminator, otherwise the
///        parameter `strlen` is evaluated to determine the string length, but
///        in any case the result will be NULL terminated (though it might
///        contain NULL characters with the string if `str` contained NULL
///        characters). Other flags in the `options` field are passed to the
///        functions defined above, and regarded as described.  See also
///        utf8_map_custom() to supply a custom codepoint transformation.
///
///        In case of success the length of the new string is returned,
///        otherwise a negative error code is returned.
///
/// @note The memory of the new UTF-8 string will have been allocated
///       with `malloc`, and should therefore be deallocated with `free`.
///
CALC_EXTERN ssize_t utf8_map(
    const uint8_t *str, ssize_t strlen, uint8_t **dstptr, utf8_option_t options);

/// @brief Like utf8_map(), but also takes a `custom_func` mapping function
///        that is called on each codepoint in `str` before any other transformations
///        (along with a `custom_data` pointer that is passed through to `custom_func`).
///        The `custom_func` argument is ignored if it is `NULL`.
CALC_EXTERN ssize_t utf8_map_custom(
    const uint8_t *str, ssize_t strlen, uint8_t **dstptr, utf8_option_t options,
    utf8_custom_func_t custom_func, void *custom_data);

/// @name Unicode normalization
///
/// Returns a pointer to newly allocated memory of a NFD, NFC, NFKD, NFKC or
/// NFKC_Casefold normalized version of the null-terminated string `str`.  These
/// are shortcuts to calling utf8_map() with UTF8_NULLTERM
/// combined with UTF8_STABLE and flags indicating the normalization.
///
/// @{
/// @brief NFD normalization (UTF8_DECOMPOSE).
CALC_EXTERN uint8_t *utf8_NFD(const uint8_t *str);
/// @brief NFC normalization (UTF8_COMPOSE).
CALC_EXTERN uint8_t *utf8_NFC(const uint8_t *str);
/// @brief NFKD normalization (UTF8_DECOMPOSE and UTF8_COMPAT).
CALC_EXTERN uint8_t *utf8_NFKD(const uint8_t *str);
/// @brief NFKC normalization (UTF8_COMPOSE and UTF8_COMPAT).
CALC_EXTERN uint8_t *utf8_NFKC(const uint8_t *str);
/// @brief NFKC_Casefold normalization (UTF8_COMPOSE and UTF8_COMPAT
///        and UTF8_CASEFOLD and UTF8_IGNORE).
CALC_EXTERN uint8_t *utf8_NFKC_Casefold(const uint8_t *str);
/// @}

CALC_C_HEADER_END

#endif // CALC_BASE_UTF8_H_
