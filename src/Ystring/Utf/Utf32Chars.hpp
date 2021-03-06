//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-09-17.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#define UTF32_NULL                                U"\u0000"
#define UTF32_START_OF_HEADING                    U"\u0001"
#define UTF32_START_OF_TEXT                       U"\u0002"
#define UTF32_END_OF_TEXT                         U"\u0003"
#define UTF32_END_OF_TRANSMISSION                 U"\u0004"
#define UTF32_ENQUIRY                             U"\u0005"
#define UTF32_ACKNOWLEDGE                         U"\u0006"
#define UTF32_BELL                                U"\u0007"
#define UTF32_BACKSPACE                           U"\u0008"
#define UTF32_CHARACTER_TABULATION                U"\u0009"
#define UTF32_LINE_FEED                           U"\u000A"
#define UTF32_LINE_TABULATION                     U"\u000B"
#define UTF32_FORM_FEED                           U"\u000C"
#define UTF32_CARRIAGE_RETURN                     U"\u000D"
#define UTF32_SHIFT_OUT                           U"\u000E"
#define UTF32_SHIFT_IN                            U"\u000F"
#define UTF32_DATA_LINK_ESCAPE                    U"\u0010"
#define UTF32_DEVICE_CONTROL_ONE                  U"\u0011"
#define UTF32_DEVICE_CONTROL_TWO                  U"\u0012"
#define UTF32_DEVICE_CONTROL_THREE                U"\u0013"
#define UTF32_DEVICE_CONTROL_FOUR                 U"\u0014"
#define UTF32_NEGATIVE_ACKNOWLEDGE                U"\u0015"
#define UTF32_SYNCHRONOUS_IDLE                    U"\u0016"
#define UTF32_END_OF_TRANSMISSION_BLOCK           U"\u0017"
#define UTF32_CANCEL                              U"\u0018"
#define UTF32_END_OF_MEDIUM                       U"\u0019"
#define UTF32_SUBSTITUTE                          U"\u001A"
#define UTF32_ESCAPE                              U"\u001B"
#define UTF32_INFORMATION_SEPARATOR_FOUR          U"\u001C"
#define UTF32_INFORMATION_SEPARATOR_THREE         U"\u001D"
#define UTF32_INFORMATION_SEPARATOR_TWO           U"\u001E"
#define UTF32_INFORMATION_SEPARATOR_ONE           U"\u001F"
#define UTF32_DELETE                              U"\u007F"
#define UTF32_BREAK_PERMITTED_HERE                U"\u0082"
#define UTF32_NO_BREAK_HERE                       U"\u0083"
#define UTF32_NEXT_LINE                           U"\u0085"
#define UTF32_START_OF_SELECTED_AREA              U"\u0086"
#define UTF32_END_OF_SELECTED_AREA                U"\u0087"
#define UTF32_CHARACTER_TABULATION_SET            U"\u0088"
#define UTF32_CHARACTER_TABULATION_WITH_JUSTIFICATION U"\u0089"
#define UTF32_LINE_TABULATION_SET                 U"\u008A"
#define UTF32_PARTIAL_LINE_FORWARD                U"\u008B"
#define UTF32_PARTIAL_LINE_BACKWARD               U"\u008C"
#define UTF32_REVERSE_LINE_FEED                   U"\u008D"
#define UTF32_SINGLE_SHIFT_TWO                    U"\u008E"
#define UTF32_SINGLE_SHIFT_THREE                  U"\u008F"
#define UTF32_DEVICE_CONTROL_STRING               U"\u0090"
#define UTF32_PRIVATE_USE_ONE                     U"\u0091"
#define UTF32_PRIVATE_USE_TWO                     U"\u0092"
#define UTF32_SET_TRANSMIT_STATE                  U"\u0093"
#define UTF32_CANCEL_CHARACTER                    U"\u0094"
#define UTF32_MESSAGE_WAITING                     U"\u0095"
#define UTF32_START_OF_GUARDED_AREA               U"\u0096"
#define UTF32_END_OF_GUARDED_AREA                 U"\u0097"
#define UTF32_START_OF_STRING                     U"\u0098"
#define UTF32_SINGLE_CHARACTER_INTRODUCER         U"\u009A"
#define UTF32_CONTROL_SEQUENCE_INTRODUCER         U"\u009B"
#define UTF32_STRING_TERMINATOR                   U"\u009C"
#define UTF32_OPERATING_SYSTEM_COMMAND            U"\u009D"
#define UTF32_PRIVACY_MESSAGE                     U"\u009E"
#define UTF32_APPLICATION_PROGRAM_COMMAND         U"\u009F"
#define UTF32_NO_BREAK_SPACE                      U"\u00A0"
#define UTF32_INVERTED_EXCLAMATION_MARK           U"\u00A1"
#define UTF32_CENT_SIGN                           U"\u00A2"
#define UTF32_POUND_SIGN                          U"\u00A3"
#define UTF32_CURRENCY_SIGN                       U"\u00A4"
#define UTF32_YEN_SIGN                            U"\u00A5"
#define UTF32_BROKEN_BAR                          U"\u00A6"
#define UTF32_SECTION_SIGN                        U"\u00A7"
#define UTF32_DIAERESIS                           U"\u00A8"
#define UTF32_COPYRIGHT_SIGN                      U"\u00A9"
#define UTF32_FEMININE_ORDINAL_INDICATOR          U"\u00AA"
#define UTF32_LEFT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK U"\u00AB"
#define UTF32_NOT_SIGN                            U"\u00AC"
#define UTF32_SOFT_HYPHEN                         U"\u00AD"
#define UTF32_REGISTERED_SIGN                     U"\u00AE"
#define UTF32_MACRON                              U"\u00AF"
#define UTF32_DEGREE_SIGN                         U"\u00B0"
#define UTF32_PLUS_MINUS_SIGN                     U"\u00B1"
#define UTF32_SUPERSCRIPT_TWO                     U"\u00B2"
#define UTF32_SUPERSCRIPT_THREE                   U"\u00B3"
#define UTF32_ACUTE_ACCENT                        U"\u00B4"
#define UTF32_MICRO_SIGN                          U"\u00B5"
#define UTF32_PILCROW_SIGN                        U"\u00B6"
#define UTF32_MIDDLE_DOT                          U"\u00B7"
#define UTF32_CEDILLA                             U"\u00B8"
#define UTF32_SUPERSCRIPT_ONE                     U"\u00B9"
#define UTF32_MASCULINE_ORDINAL_INDICATOR         U"\u00BA"
#define UTF32_RIGHT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK U"\u00BB"
#define UTF32_VULGAR_FRACTION_ONE_QUARTER         U"\u00BC"
#define UTF32_VULGAR_FRACTION_ONE_HALF            U"\u00BD"
#define UTF32_VULGAR_FRACTION_THREE_QUARTERS      U"\u00BE"
#define UTF32_INVERTED_QUESTION_MARK              U"\u00BF"
#define UTF32_LATIN_CAPITAL_A_WITH_GRAVE          U"\u00C0"
#define UTF32_LATIN_CAPITAL_A_WITH_ACUTE          U"\u00C1"
#define UTF32_LATIN_CAPITAL_A_WITH_CIRCUMFLEX     U"\u00C2"
#define UTF32_LATIN_CAPITAL_A_WITH_TILDE          U"\u00C3"
#define UTF32_LATIN_CAPITAL_A_WITH_DIAERESIS      U"\u00C4"
#define UTF32_LATIN_CAPITAL_A_WITH_RING_ABOVE     U"\u00C5"
#define UTF32_LATIN_CAPITAL_AE                    U"\u00C6"
#define UTF32_LATIN_CAPITAL_C_WITH_CEDILLA        U"\u00C7"
#define UTF32_LATIN_CAPITAL_E_WITH_GRAVE          U"\u00C8"
#define UTF32_LATIN_CAPITAL_E_WITH_ACUTE          U"\u00C9"
#define UTF32_LATIN_CAPITAL_E_WITH_CIRCUMFLEX     U"\u00CA"
#define UTF32_LATIN_CAPITAL_E_WITH_DIAERESIS      U"\u00CB"
#define UTF32_LATIN_CAPITAL_I_WITH_GRAVE          U"\u00CC"
#define UTF32_LATIN_CAPITAL_I_WITH_ACUTE          U"\u00CD"
#define UTF32_LATIN_CAPITAL_I_WITH_CIRCUMFLEX     U"\u00CE"
#define UTF32_LATIN_CAPITAL_I_WITH_DIAERESIS      U"\u00CF"
#define UTF32_LATIN_CAPITAL_ETH                   U"\u00D0"
#define UTF32_LATIN_CAPITAL_N_WITH_TILDE          U"\u00D1"
#define UTF32_LATIN_CAPITAL_O_WITH_GRAVE          U"\u00D2"
#define UTF32_LATIN_CAPITAL_O_WITH_ACUTE          U"\u00D3"
#define UTF32_LATIN_CAPITAL_O_WITH_CIRCUMFLEX     U"\u00D4"
#define UTF32_LATIN_CAPITAL_O_WITH_TILDE          U"\u00D5"
#define UTF32_LATIN_CAPITAL_O_WITH_DIAERESIS      U"\u00D6"
#define UTF32_MULTIPLICATION_SIGN                 U"\u00D7"
#define UTF32_LATIN_CAPITAL_O_WITH_STROKE         U"\u00D8"
#define UTF32_LATIN_CAPITAL_U_WITH_GRAVE          U"\u00D9"
#define UTF32_LATIN_CAPITAL_U_WITH_ACUTE          U"\u00DA"
#define UTF32_LATIN_CAPITAL_U_WITH_CIRCUMFLEX     U"\u00DB"
#define UTF32_LATIN_CAPITAL_U_WITH_DIAERESIS      U"\u00DC"
#define UTF32_LATIN_CAPITAL_Y_WITH_ACUTE          U"\u00DD"
#define UTF32_LATIN_CAPITAL_THORN                 U"\u00DE"
#define UTF32_LATIN_SMALL_SHARP_S                 U"\u00DF"
#define UTF32_LATIN_SMALL_A_WITH_GRAVE            U"\u00E0"
#define UTF32_LATIN_SMALL_A_WITH_ACUTE            U"\u00E1"
#define UTF32_LATIN_SMALL_A_WITH_CIRCUMFLEX       U"\u00E2"
#define UTF32_LATIN_SMALL_A_WITH_TILDE            U"\u00E3"
#define UTF32_LATIN_SMALL_A_WITH_DIAERESIS        U"\u00E4"
#define UTF32_LATIN_SMALL_A_WITH_RING_ABOVE       U"\u00E5"
#define UTF32_LATIN_SMALL_AE                      U"\u00E6"
#define UTF32_LATIN_SMALL_C_WITH_CEDILLA          U"\u00E7"
#define UTF32_LATIN_SMALL_E_WITH_GRAVE            U"\u00E8"
#define UTF32_LATIN_SMALL_E_WITH_ACUTE            U"\u00E9"
#define UTF32_LATIN_SMALL_E_WITH_CIRCUMFLEX       U"\u00EA"
#define UTF32_LATIN_SMALL_E_WITH_DIAERESIS        U"\u00EB"
#define UTF32_LATIN_SMALL_I_WITH_GRAVE            U"\u00EC"
#define UTF32_LATIN_SMALL_I_WITH_ACUTE            U"\u00ED"
#define UTF32_LATIN_SMALL_I_WITH_CIRCUMFLEX       U"\u00EE"
#define UTF32_LATIN_SMALL_I_WITH_DIAERESIS        U"\u00EF"
#define UTF32_LATIN_SMALL_ETH                     U"\u00F0"
#define UTF32_LATIN_SMALL_N_WITH_TILDE            U"\u00F1"
#define UTF32_LATIN_SMALL_O_WITH_GRAVE            U"\u00F2"
#define UTF32_LATIN_SMALL_O_WITH_ACUTE            U"\u00F3"
#define UTF32_LATIN_SMALL_O_WITH_CIRCUMFLEX       U"\u00F4"
#define UTF32_LATIN_SMALL_O_WITH_TILDE            U"\u00F5"
#define UTF32_LATIN_SMALL_O_WITH_DIAERESIS        U"\u00F6"
#define UTF32_DIVISION_SIGN                       U"\u00F7"
#define UTF32_LATIN_SMALL_O_WITH_STROKE           U"\u00F8"
#define UTF32_LATIN_SMALL_U_WITH_GRAVE            U"\u00F9"
#define UTF32_LATIN_SMALL_U_WITH_ACUTE            U"\u00FA"
#define UTF32_LATIN_SMALL_U_WITH_CIRCUMFLEX       U"\u00FB"
#define UTF32_LATIN_SMALL_U_WITH_DIAERESIS        U"\u00FC"
#define UTF32_LATIN_SMALL_Y_WITH_ACUTE            U"\u00FD"
#define UTF32_LATIN_SMALL_THORN                   U"\u00FE"
#define UTF32_LATIN_SMALL_Y_WITH_DIAERESIS        U"\u00FF"
#define UTF32_COMBINING_GRAVE_ACCENT              U"\u0300"
#define UTF32_COMBINING_ACUTE_ACCENT              U"\u0301"
#define UTF32_COMBINING_CIRCUMFLEX_ACCENT         U"\u0302"
#define UTF32_COMBINING_TILDE                     U"\u0303"
#define UTF32_COMBINING_MACRON                    U"\u0304"
#define UTF32_COMBINING_OVERLINE                  U"\u0305"
#define UTF32_COMBINING_BREVE                     U"\u0306"
#define UTF32_COMBINING_DOT_ABOVE                 U"\u0307"
#define UTF32_COMBINING_DIAERESIS                 U"\u0308"
#define UTF32_COMBINING_HOOK_ABOVE                U"\u0309"
#define UTF32_COMBINING_RING_ABOVE                U"\u030A"
#define UTF32_COMBINING_DOUBLE_ACUTE_ACCENT       U"\u030B"
#define UTF32_COMBINING_CARON                     U"\u030C"
#define UTF32_COMBINING_VERTICAL_LINE_ABOVE       U"\u030D"
#define UTF32_COMBINING_DOUBLE_VERTICAL_LINE_ABOVE U"\u030E"
#define UTF32_COMBINING_DOUBLE_GRAVE_ACCENT       U"\u030F"
#define UTF32_COMBINING_CANDRABINDU               U"\u0310"
#define UTF32_COMBINING_INVERTED_BREVE            U"\u0311"
#define UTF32_COMBINING_TURNED_COMMA_ABOVE        U"\u0312"
#define UTF32_COMBINING_COMMA_ABOVE               U"\u0313"
#define UTF32_COMBINING_REVERSED_COMMA_ABOVE      U"\u0314"
#define UTF32_COMBINING_COMMA_ABOVE_RIGHT         U"\u0315"
#define UTF32_COMBINING_GRAVE_ACCENT_BELOW        U"\u0316"
#define UTF32_COMBINING_ACUTE_ACCENT_BELOW        U"\u0317"
#define UTF32_COMBINING_LEFT_TACK_BELOW           U"\u0318"
#define UTF32_COMBINING_RIGHT_TACK_BELOW          U"\u0319"
#define UTF32_COMBINING_LEFT_ANGLE_ABOVE          U"\u031A"
#define UTF32_COMBINING_HORN                      U"\u031B"
#define UTF32_COMBINING_LEFT_HALF_RING_BELOW      U"\u031C"
#define UTF32_COMBINING_UP_TACK_BELOW             U"\u031D"
#define UTF32_COMBINING_DOWN_TACK_BELOW           U"\u031E"
#define UTF32_COMBINING_PLUS_SIGN_BELOW           U"\u031F"
#define UTF32_COMBINING_MINUS_SIGN_BELOW          U"\u0320"
#define UTF32_COMBINING_PALATALIZED_HOOK_BELOW    U"\u0321"
#define UTF32_COMBINING_RETROFLEX_HOOK_BELOW      U"\u0322"
#define UTF32_COMBINING_DOT_BELOW                 U"\u0323"
#define UTF32_COMBINING_DIAERESIS_BELOW           U"\u0324"
#define UTF32_COMBINING_RING_BELOW                U"\u0325"
#define UTF32_COMBINING_COMMA_BELOW               U"\u0326"
#define UTF32_COMBINING_CEDILLA                   U"\u0327"
#define UTF32_COMBINING_OGONEK                    U"\u0328"
#define UTF32_COMBINING_VERTICAL_LINE_BELOW       U"\u0329"
#define UTF32_COMBINING_BRIDGE_BELOW              U"\u032A"
#define UTF32_COMBINING_INVERTED_DOUBLE_ARCH_BELOW U"\u032B"
#define UTF32_COMBINING_CARON_BELOW               U"\u032C"
#define UTF32_COMBINING_CIRCUMFLEX_ACCENT_BELOW   U"\u032D"
#define UTF32_COMBINING_BREVE_BELOW               U"\u032E"
#define UTF32_COMBINING_INVERTED_BREVE_BELOW      U"\u032F"
#define UTF32_COMBINING_TILDE_BELOW               U"\u0330"
#define UTF32_COMBINING_MACRON_BELOW              U"\u0331"
#define UTF32_COMBINING_LOW_LINE                  U"\u0332"
#define UTF32_COMBINING_DOUBLE_LOW_LINE           U"\u0333"
#define UTF32_COMBINING_TILDE_OVERLAY             U"\u0334"
#define UTF32_COMBINING_SHORT_STROKE_OVERLAY      U"\u0335"
#define UTF32_COMBINING_LONG_STROKE_OVERLAY       U"\u0336"
#define UTF32_COMBINING_SHORT_SOLIDUS_OVERLAY     U"\u0337"
#define UTF32_COMBINING_LONG_SOLIDUS_OVERLAY      U"\u0338"
#define UTF32_COMBINING_RIGHT_HALF_RING_BELOW     U"\u0339"
#define UTF32_COMBINING_INVERTED_BRIDGE_BELOW     U"\u033A"
#define UTF32_COMBINING_SQUARE_BELOW              U"\u033B"
#define UTF32_COMBINING_SEAGULL_BELOW             U"\u033C"
#define UTF32_COMBINING_X_ABOVE                   U"\u033D"
#define UTF32_COMBINING_VERTICAL_TILDE            U"\u033E"
#define UTF32_COMBINING_DOUBLE_OVERLINE           U"\u033F"
#define UTF32_COMBINING_GRAVE_TONE_MARK           U"\u0340"
#define UTF32_COMBINING_ACUTE_TONE_MARK           U"\u0341"
#define UTF32_COMBINING_GREEK_PERISPOMENI         U"\u0342"
#define UTF32_COMBINING_GREEK_KORONIS             U"\u0343"
#define UTF32_COMBINING_GREEK_DIALYTIKA_TONOS     U"\u0344"
#define UTF32_COMBINING_GREEK_YPOGEGRAMMENI       U"\u0345"
#define UTF32_COMBINING_BRIDGE_ABOVE              U"\u0346"
#define UTF32_COMBINING_EQUALS_SIGN_BELOW         U"\u0347"
#define UTF32_COMBINING_DOUBLE_VERTICAL_LINE_BELOW U"\u0348"
#define UTF32_COMBINING_LEFT_ANGLE_BELOW          U"\u0349"
#define UTF32_COMBINING_NOT_TILDE_ABOVE           U"\u034A"
#define UTF32_COMBINING_HOMOTHETIC_ABOVE          U"\u034B"
#define UTF32_COMBINING_ALMOST_EQUAL_TO_ABOVE     U"\u034C"
#define UTF32_COMBINING_LEFT_RIGHT_ARROW_BELOW    U"\u034D"
#define UTF32_COMBINING_UPWARDS_ARROW_BELOW       U"\u034E"
#define UTF32_COMBINING_GRAPHEME_JOINER           U"\u034F"
#define UTF32_COMBINING_RIGHT_ARROWHEAD_ABOVE     U"\u0350"
#define UTF32_COMBINING_LEFT_HALF_RING_ABOVE      U"\u0351"
#define UTF32_COMBINING_FERMATA                   U"\u0352"
#define UTF32_COMBINING_X_BELOW                   U"\u0353"
#define UTF32_COMBINING_LEFT_ARROWHEAD_BELOW      U"\u0354"
#define UTF32_COMBINING_RIGHT_ARROWHEAD_BELOW     U"\u0355"
#define UTF32_COMBINING_RIGHT_ARROWHEAD_AND_UP_ARROWHEAD_BELOW U"\u0356"
#define UTF32_COMBINING_RIGHT_HALF_RING_ABOVE     U"\u0357"
#define UTF32_COMBINING_DOT_ABOVE_RIGHT           U"\u0358"
#define UTF32_COMBINING_ASTERISK_BELOW            U"\u0359"
#define UTF32_COMBINING_DOUBLE_RING_BELOW         U"\u035A"
#define UTF32_COMBINING_ZIGZAG_ABOVE              U"\u035B"
#define UTF32_COMBINING_DOUBLE_BREVE_BELOW        U"\u035C"
#define UTF32_COMBINING_DOUBLE_BREVE              U"\u035D"
#define UTF32_COMBINING_DOUBLE_MACRON             U"\u035E"
#define UTF32_COMBINING_DOUBLE_MACRON_BELOW       U"\u035F"
#define UTF32_COMBINING_DOUBLE_TILDE              U"\u0360"
#define UTF32_COMBINING_DOUBLE_INVERTED_BREVE     U"\u0361"
#define UTF32_COMBINING_DOUBLE_RIGHTWARDS_ARROW_BELOW U"\u0362"
#define UTF32_COMBINING_LATIN_SMALL_A             U"\u0363"
#define UTF32_COMBINING_LATIN_SMALL_E             U"\u0364"
#define UTF32_COMBINING_LATIN_SMALL_I             U"\u0365"
#define UTF32_COMBINING_LATIN_SMALL_O             U"\u0366"
#define UTF32_COMBINING_LATIN_SMALL_U             U"\u0367"
#define UTF32_COMBINING_LATIN_SMALL_C             U"\u0368"
#define UTF32_COMBINING_LATIN_SMALL_D             U"\u0369"
#define UTF32_COMBINING_LATIN_SMALL_H             U"\u036A"
#define UTF32_COMBINING_LATIN_SMALL_M             U"\u036B"
#define UTF32_COMBINING_LATIN_SMALL_R             U"\u036C"
#define UTF32_COMBINING_LATIN_SMALL_T             U"\u036D"
#define UTF32_COMBINING_LATIN_SMALL_V             U"\u036E"
#define UTF32_COMBINING_LATIN_SMALL_X             U"\u036F"
#define UTF32_GREEK_CAPITAL_ALPHA                 U"\u0391"
#define UTF32_GREEK_CAPITAL_BETA                  U"\u0392"
#define UTF32_GREEK_CAPITAL_GAMMA                 U"\u0393"
#define UTF32_GREEK_CAPITAL_DELTA                 U"\u0394"
#define UTF32_GREEK_CAPITAL_EPSILON               U"\u0395"
#define UTF32_GREEK_CAPITAL_ZETA                  U"\u0396"
#define UTF32_GREEK_CAPITAL_ETA                   U"\u0397"
#define UTF32_GREEK_CAPITAL_THETA                 U"\u0398"
#define UTF32_GREEK_CAPITAL_IOTA                  U"\u0399"
#define UTF32_GREEK_CAPITAL_KAPPA                 U"\u039A"
#define UTF32_GREEK_CAPITAL_LAMDA                 U"\u039B"
#define UTF32_GREEK_CAPITAL_MU                    U"\u039C"
#define UTF32_GREEK_CAPITAL_NU                    U"\u039D"
#define UTF32_GREEK_CAPITAL_XI                    U"\u039E"
#define UTF32_GREEK_CAPITAL_OMICRON               U"\u039F"
#define UTF32_GREEK_CAPITAL_PI                    U"\u03A0"
#define UTF32_GREEK_CAPITAL_RHO                   U"\u03A1"
#define UTF32_GREEK_CAPITAL_SIGMA                 U"\u03A3"
#define UTF32_GREEK_CAPITAL_TAU                   U"\u03A4"
#define UTF32_GREEK_CAPITAL_UPSILON               U"\u03A5"
#define UTF32_GREEK_CAPITAL_PHI                   U"\u03A6"
#define UTF32_GREEK_CAPITAL_CHI                   U"\u03A7"
#define UTF32_GREEK_CAPITAL_PSI                   U"\u03A8"
#define UTF32_GREEK_CAPITAL_OMEGA                 U"\u03A9"
#define UTF32_GREEK_SMALL_ALPHA                   U"\u03B1"
#define UTF32_GREEK_SMALL_BETA                    U"\u03B2"
#define UTF32_GREEK_SMALL_GAMMA                   U"\u03B3"
#define UTF32_GREEK_SMALL_DELTA                   U"\u03B4"
#define UTF32_GREEK_SMALL_EPSILON                 U"\u03B5"
#define UTF32_GREEK_SMALL_ZETA                    U"\u03B6"
#define UTF32_GREEK_SMALL_ETA                     U"\u03B7"
#define UTF32_GREEK_SMALL_THETA                   U"\u03B8"
#define UTF32_GREEK_SMALL_IOTA                    U"\u03B9"
#define UTF32_GREEK_SMALL_KAPPA                   U"\u03BA"
#define UTF32_GREEK_SMALL_LAMDA                   U"\u03BB"
#define UTF32_GREEK_SMALL_MU                      U"\u03BC"
#define UTF32_GREEK_SMALL_NU                      U"\u03BD"
#define UTF32_GREEK_SMALL_XI                      U"\u03BE"
#define UTF32_GREEK_SMALL_OMICRON                 U"\u03BF"
#define UTF32_GREEK_SMALL_PI                      U"\u03C0"
#define UTF32_GREEK_SMALL_RHO                     U"\u03C1"
#define UTF32_GREEK_SMALL_FINAL_SIGMA             U"\u03C2"
#define UTF32_GREEK_SMALL_SIGMA                   U"\u03C3"
#define UTF32_GREEK_SMALL_TAU                     U"\u03C4"
#define UTF32_GREEK_SMALL_UPSILON                 U"\u03C5"
#define UTF32_GREEK_SMALL_PHI                     U"\u03C6"
#define UTF32_GREEK_SMALL_CHI                     U"\u03C7"
#define UTF32_GREEK_SMALL_PSI                     U"\u03C8"
#define UTF32_GREEK_SMALL_OMEGA                   U"\u03C9"
#define UTF32_OGHAM_SPACE_MARK                    U"\u1680"
#define UTF32_MONGOLIAN_VOWEL_SEPARATOR           U"\u180E"
#define UTF32_EN_QUAD                             U"\u2000"
#define UTF32_EM_QUAD                             U"\u2001"
#define UTF32_EN_SPACE                            U"\u2002"
#define UTF32_EM_SPACE                            U"\u2003"
#define UTF32_THREE_PER_EM_SPACE                  U"\u2004"
#define UTF32_FOUR_PER_EM_SPACE                   U"\u2005"
#define UTF32_SIX_PER_EM_SPACE                    U"\u2006"
#define UTF32_FIGURE_SPACE                        U"\u2007"
#define UTF32_PUNCTUATION_SPACE                   U"\u2008"
#define UTF32_THIN_SPACE                          U"\u2009"
#define UTF32_HAIR_SPACE                          U"\u200A"
#define UTF32_ZERO_WIDTH_SPACE                    U"\u200B"
#define UTF32_ZERO_WIDTH_NON_JOINER               U"\u200C"
#define UTF32_ZERO_WIDTH_JOINER                   U"\u200D"
#define UTF32_LINE_SEPARATOR                      U"\u2028"
#define UTF32_PARAGRAPH_SEPARATOR                 U"\u2029"
#define UTF32_NARROW_NO_BREAK_SPACE               U"\u202F"
#define UTF32_MEDIUM_MATHEMATICAL_SPACE           U"\u205F"
#define UTF32_WORD_JOINER                         U"\u2060"
#define UTF32_IDEOGRAPHIC_SPACE                   U"\u3000"
#define UTF32_ZERO_WIDTH_NO_BREAK_SPACE           U"\uFEFF"
