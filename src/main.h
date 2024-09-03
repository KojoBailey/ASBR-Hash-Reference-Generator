#pragma once

#define EXPORT extern "C" __declspec(dllexport)

#include <JojoAPI.h>
#define USE_BINARY_TYPES
#include <binary.hpp>

#include <bit>
#include <filesystem>
#include <format>
#include <fstream>
#include <unordered_set>

EXPORT ModMeta __stdcall GetModInfo();
EXPORT void __stdcall ModInit();

ModMeta __stdcall GetModInfo() {
    static ModMeta meta = {
        "Character ID Hash Printer", // Name
        "Character_ID_Hash_Printer", // GUID
        "1.0.0",                        // Version
        "Kojo Bailey"                   // Author
    };

    return meta;
}

#define DEBUG_BUILD

#define JFATAL(message, ...) JAPI_LogFatal(std::format(message, ##__VA_ARGS__))
#define JERROR(message, ...) JAPI_LogError(std::format(message, ##__VA_ARGS__))
#define JWARN(message, ...) JAPI_LogWarn(std::format(message, ##__VA_ARGS__))
#define JINFO(message, ...) JAPI_LogInfo(std::format(message, ##__VA_ARGS__))

#ifdef DEBUG_BUILD
    #define JDEBUG(message, ...) JAPI_LogDebug(std::format(message, ##__VA_ARGS__))
    #define JTRACE(message, ...) JAPI_LogTrace(std::format(message, ##__VA_ARGS__))
#else
    #define JDEBUG(message, ...)
    #define JTRACE(message, ...)
#endif