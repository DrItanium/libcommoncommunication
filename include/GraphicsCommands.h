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
#define X(action, str) action = asciiEncodeTwo( str ) ,
#include "GraphicsOpcodes.def"
#undef X
};

constexpr bool valid(GraphicsOpcode opcode) noexcept {
    switch (opcode) {
#define X(action, str) case GraphicsOpcode :: action : return true;
#include "GraphicsOpcodes.def"
#undef X

        default:
            return false;
    }
}

struct GraphicsOperation final {
    GraphicsOperation(GraphicsOpcode opcode, uint16_t a0 = 0, uint16_t a1 = 0, uint16_t a2 = 0, uint16_t a3 = 0, uint16_t a4 = 0, uint16_t a5 = 0, uint16_t a6 = 0) : op(opcode), args{a0, a1, a2, a3, a4, a5, a6 } { }
    GraphicsOpcode op;
    uint16_t args[7];
};
static_assert(sizeof(GraphicsOperation) == 16, "Graphics Operations are not possible on this target!");

#endif // end !defined(__LIBCROSSCOMMUNICATION_GRAPHICS_COMMANDS_H__)
