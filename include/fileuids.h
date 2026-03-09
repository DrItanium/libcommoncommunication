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
#ifndef __LIBCROSSCOMMUNICATION_FILEUIDS_H__
#define __LIBCROSSCOMMUNICATION_FILEUIDS_H__
#include <cstdint>

/**
 * @brief A useful union type that allows two different providers (i960 and
 * teensy specifically) to assist in construction of the 64-bit number
 */
union FileUID {
    uint64_t raw;
    struct {
        uint32_t i960;
        uint32_t chipset;
    };
};
static_assert(sizeof(FileUID) == sizeof(uint64_t));

/**
 * @brief The common structure shared between the i960 and teensy devices to
 * make requests to manipulate a filesystem
 */
union FilesystemOperation {
    enum class Opcode : uint16_t {
        None, // make sure that zero is not accepted as a valid operation
        // direct manipulation
        Read,
        Write,
        // position manipulation
        SetPosition_Absolute,
        SetPosition_RelativeToCurr,
        SetPosition_RelativeToEnd,
        // flags
        Valid,
        Available,
        IsOpen,
        IsDirectory,
        // individual large size parameters
        GetPosition,
        GetSize,
        // Other
        Peek,
        Open,
        Close,
        Flush,
        // extra operations, keep the commented out ones at the bottom to not
        // break compatibility
        // GetName,
        // Truncate,
        // OpenNextFile,
        // RewindDirectory,
    };
    static constexpr bool valid(Opcode code) noexcept {
        switch (code) {
            case Opcode::None:
            case Opcode::Read:
            case Opcode::Write:
            case Opcode::SetPosition_Absolute:
            case Opcode::SetPosition_RelativeToCurr:
            case Opcode::SetPosition_RelativeToEnd:
            case Opcode::Valid:
            case Opcode::Available:
            case Opcode::IsOpen:
            case Opcode::IsDirectory:
            case Opcode::GetPosition:
            case Opcode::GetSize:
            case Opcode::Peek:
            case Opcode::Open:
            case Opcode::Close:
            case Opcode::Flush:
                return true;
            default:
                return false;
        }
    }
    using Cell = uint64_t;
    using UID = FileUID;
    using Pointer = uint32_t;
    Cell storage[8]; // reserve 64-bytes for this
    struct {
        union {
            Cell raw;
            struct {
                Opcode opcode;
                uint16_t errorCode;
                Cell rest : 32;
            };
        } control;
        UID target; // always allocated and is the first 64-bit Cell in the return values
        // add two extra 64-bit cells for extra return data
        Cell returnComponents[2];
        // upper 32-bytes used for arguments
        union {
            Cell words[4]; // we can never exceed this
            struct {
                Pointer bufferAddress;
                uint32_t size;
            } onRead, onWrite;
            struct {
                uint64_t position;
            } onSeekOperation;
            struct {
                Pointer path;
                uint32_t flags;
                /// @brief i960 organization id used to salt the file system handle to make it somewhat harder to access files that don't belong to you!
                uint32_t org;
            } onOpen;
        } args;
        static_assert(sizeof(args) == 32);
    };
    constexpr Pointer getOpen_Path() const noexcept {
        return args.onOpen.path;
    }
    constexpr uint32_t getOpen_Flags() const noexcept {
        return args.onOpen.flags;
    }
    constexpr uint32_t getOpen_i960Orgid() const noexcept {
        return args.onOpen.org;
    }
    Opcode getOpcode() const noexcept { return control.opcode; }
    uint16_t getErrorCode() const noexcept {
        return control.errorCode;
    }
    void setErrorCode(uint16_t code) noexcept {
        control.errorCode = code;
    }
    template<typename T>
    void setErrorCode(T code) noexcept {
        setErrorCode(static_cast<uint16_t>(code));
    }
    [[nodiscard]] constexpr uint64_t getUid() const noexcept {
        return target.raw;
    }
    constexpr uint64_t getPosition() const noexcept {
        return args.onSeekOperation.position;
    }
};
static_assert(sizeof(FilesystemOperation) == 64);

/**
 * @brief Error codes that the file tracker uses
 */
enum class FileRequestErrorCodes : uint16_t {
    None = 0,
    Unknown = 0x0100, // first unknown code
    CouldNotFindASpotForFileGivenI960UniqueId,
    CouldNotOpenFile,
    InvalidOperation,
    UnimplementedOperation,
    CouldNotCloseFile,
    NotAnOpenFile,
    InvalidBufferAddress,
    RequestedLengthTooLong,
};

/**
 * @brief Error codes that are generated by the raw filesystem interface thing that the i960 uses to talk to the teensy.
 */
enum class FilesystemInterfaceErrorCodes : uint32_t {
    Ok = 0,
    NotEnabled,
    UnimplementedOperation,
    UnalignedAddressProvided,
    IllegalAddressProvided,
    ErrorHappenedDuringProcessing,
};


#endif // end !defined(__LIBCROSSCOMMUNICATION_FILEUIDS_H__)
