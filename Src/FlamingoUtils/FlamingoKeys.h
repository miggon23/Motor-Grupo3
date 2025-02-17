#pragma once

#ifndef __FLAMINGO_KEYS_H__
#define __FLAMINGO_KEYS_H__

#include "FlamingoExport/FlamingoAPI.h"
#include <cstdint>

namespace Flamingo
{
    extern "C"
    {
        typedef int32_t __declspec(dllexport) FLM_Keycode;
        typedef enum __declspec(dllexport) 
        {
            FLM_UNKNOWN,
            FLM_RETURN,
            FLM_ESCAPE,
            FLM_BACKSPACE,
            FLM_TAB,
            FLM_SPACE,
            FLM_EXCLAIM,
            FLM_QUOTEDBL,
            FLM_HASH,
            FLM_PERCENT,
            FLM_DOLLAR,
            FLM_AMPERSAND,
            FLM_QUOTE,
            FLM_LEFTPAREN,
            FLM_RIGHTPAREN,
            FLM_ASTERISK,
            FLM_PLUS,
            FLM_COMMA,
            FLM_MINUS,
            FLM_PERIOD,
            FLM_SLASH,
            FLM_0,
            FLM_1,
            FLM_2,
            FLM_3,
            FLM_4,
            FLM_5,
            FLM_6,
            FLM_7,
            FLM_8,
            FLM_9,
            FLM_COLON,
            FLM_SEMICOLON,
            FLM_LESS,
            FLM_EQUALS,
            FLM_GREATER,
            FLM_QUESTION,
            FLM_AT,

            FLM_LEFTBRACKET,
            FLM_BACKSLASH,
            FLM_RIGHTBRACKET,
            FLM_CARET,
            FLM_UNDERSCORE,
            FLM_BACKQUOTE,
            FLM_a,
            FLM_b,
            FLM_c,
            FLM_d,
            FLM_e,
            FLM_f,
            FLM_g,
            FLM_h,
            FLM_i,
            FLM_j,
            FLM_k,
            FLM_l,
            FLM_m,
            FLM_n,
            FLM_o,
            FLM_p,
            FLM_q,
            FLM_r,
            FLM_s,
            FLM_t,
            FLM_u,
            FLM_v,
            FLM_w,
            FLM_x,
            FLM_y,
            FLM_z,

            FLM_CAPSLOCK,

            FLM_F1,
            FLM_F2,
            FLM_F3,
            FLM_F4,
            FLM_F5,
            FLM_F6,
            FLM_F7,
            FLM_F8,
            FLM_F9,
            FLM_F10,
            FLM_F11,
            FLM_F12,

            FLM_PRINTSCREEN,
            FLM_SCROLLLOCK,
            FLM_PAUSE,
            FLM_INSERT,
            FLM_HOME,
            FLM_PAGEUP,
            FLM_DELETE,
            FLM_END,
            FLM_PAGEDOWN,
            FLM_RIGHT,
            FLM_LEFT,
            FLM_DOWN,
            FLM_UP,

            FLM_NUMLOCKCLEAR,
            FLM_KP_DIVIDE,
            FLM_KP_MULTIPLY,
            FLM_KP_MINUS,
            FLM_KP_PLUS,
            FLM_KP_ENTER,
            FLM_KP_1,
            FLM_KP_2,
            FLM_KP_3,
            FLM_KP_4,
            FLM_KP_5,
            FLM_KP_6,
            FLM_KP_7,
            FLM_KP_8,
            FLM_KP_9,
            FLM_KP_0,
            FLM_KP_PERIOD
        } FLM_KeyCode;

        typedef enum __declspec(dllexport) MOUSEBUTTON : uint8_t
        {
            LEFT = 0,
            MIDDLE = 1,
            RIGHT = 2
        } MOUSEBUTTON;
    }
} // namespace Flamingo
#endif