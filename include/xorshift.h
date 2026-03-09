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
#ifndef __LIBCROSSCOMMUNICATION_XORSHIFT_H__
#define __LIBCROSSCOMMUNICATION_XORSHIFT_H__
#include <cstdint>
// This file contains an xorshift32 implementation as taken off of https://en.wikipedia.org/wiki/Xorshift
// xorshift is useful for iterating through the entire 32-bit/64-bit numeric
// range without hitting duplicates. It is used in this library for generating
// unique ids in a simple way.

class Xorshift32 {
    public:
        Xorshift32(uint32_t initialState) : _state(initialState) { }
        uint32_t next() noexcept {
            auto x = _state;
            x ^= x << 13;
            x ^= x >> 17;
            x ^= x << 5;
            _state = x;
            return x;
        }
        uint32_t getCurrentState() const noexcept {
            return _state;
        }
    private:
        uint32_t _state;
};

class Xorshift64 {
    public:
        Xorshift64(uint64_t initialState) : _state(initialState) { }
        uint64_t next() noexcept {
            auto x = _state;
            x ^= x << 13;
            x ^= x >> 7;
            x ^= x << 17;
            _state = x;
            return x;
        }
        uint64_t getCurrentState() const noexcept {
            return _state;
        }
    private:
        uint64_t _state;
};



#endif // end !defined(__LIBCROSSCOMMUNICATION_XORSHIFT_H__)
