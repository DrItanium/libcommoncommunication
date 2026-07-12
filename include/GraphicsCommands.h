// libcrosscommunication
// Copyright (c) 2026, Joshua Scoggins
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR 
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifndef __LIBCROSSCOMMUNICATION_GRAPHICS_COMMANDS_H__
#define __LIBCROSSCOMMUNICATION_GRAPHICS_COMMANDS_H__
#include <cstdint>
/**
 * @brief Take the first two characters in an ascii string and convert it into a 16-bit value.
 * @return the encoded 16-bit value
 * @param code The string to generate the encoded value from
 */
constexpr uint16_t asciiEncodeTwo(const char code[2]) noexcept {
    return static_cast<uint16_t>(code[0]) | (static_cast<uint16_t>(code[1]) << 8);
}

enum class GraphicsOpcode : uint16_t {
    Invalid = 0x0000,
    DrawCircle = asciiEncodeTwo("DC"),
    FillCircle = asciiEncodeTwo("FC"),
    DrawTriangle = asciiEncodeTwo("DT"),
    FillTriangle = asciiEncodeTwo("FT"),
    DrawEllipse = asciiEncodeTwo("DE"),
    FillEllipse = asciiEncodeTwo("FE"),
    DrawPixel = asciiEncodeTwo("DP"),
    DrawRectangle = asciiEncodeTwo("DR"),
    FillRectangle = asciiEncodeTwo("FR"),
    DrawRoundedRectangle = asciiEncodeTwo("DU"),
    FillRoundedRectangle = asciiEncodeTwo("FU"),
    DrawRotatedRectangle = asciiEncodeTwo("DO"),
    FillRotatedRectangle = asciiEncodeTwo("FO"),
    ScreenFill = asciiEncodeTwo("SF"),
    SetTextSize = asciiEncodeTwo("TS"),
    DrawCharacter = asciiEncodeTwo("DH"),
    DrawSquare = asciiEncodeTwo("DS"),
    FillSquare = asciiEncodeTwo("FS"),
    DrawLine = asciiEncodeTwo("DL"),
    DrawFastVerticalLine = asciiEncode("VL"),
    DrawFastHorizontalLine = asciiEncode("HL"),

};

#endif // end !defined(__LIBCROSSCOMMUNICATION_GRAPHICS_COMMANDS_H__)
