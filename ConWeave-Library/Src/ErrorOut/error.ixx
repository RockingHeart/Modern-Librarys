module;
#include <windows.h>

export module sys.error;

import utility;
import dast.string;

import <stdio.h>;
import <print>;
import <type_traits>;

export namespace sys {
    template <rest::character CharType>
    unsigned long detailed_error(unsigned long error) noexcept;
}

template <rest::character CharType = char>
unsigned long sys::detailed_error(unsigned long error) noexcept {
    CharType* message = nullptr;

    if constexpr (std::is_same_v<CharType, char>) {
        FormatMessageA (
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr, error,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<char*>(&message),
            0, nullptr
        );
        if (message) {
            fprintf(stderr, "\033[31mError: %s\033[0m\n", message);
            LocalFree(message);
        }
    }
    else {
        FormatMessageW (
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr, error,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<wchar_t*>(&message),
            0, nullptr
        );
        if (message) {
            fwprintf(stderr, L"\033[31mError: %s\033[0m\n", message);
            LocalFree(message);
        }
    }

    return error;
}