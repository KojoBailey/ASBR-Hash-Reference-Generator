#include "main.h"

std::ofstream output_file;
std::unordered_set<std::string> hash_log;

typedef u32(__fastcall* NUCC_Hash_t)(const char*);
NUCC_Hash_t NUCC_Hash_original;

u32 __fastcall NUCC_Hash(const char* c_str) {
    std::string str{c_str};
    u32 hash = std::byteswap(NUCC_Hash_original(c_str));
    if (str.length() == 6 && str.at(0) >= '0' && str.at(0) <= '8') {
        if (!hash_log.contains(str)) {
            hash_log.insert(str);
            output_file.open("char_id_hashes.bin", std::ios::binary | std::ios::app);
            output_file.write((const char*)&hash, 4);
            output_file << str;
            output_file.close();
        }
    }
    return NUCC_Hash_original(c_str);
}

Hook NUCC_Hash_hook = {
    (void*)0x6C92A0, // Address of the function we want to hook
    (void*)NUCC_Hash, // Address of our hook function
    (void**)&NUCC_Hash_original, // Address of the variable that will store the original function address
    "NUCC_Hash" // Name of the function we want to hook
};

// This function is called when the mod is loaded.
void __stdcall ModInit() {
    if (!JAPI_HookASBRFunction(&NUCC_Hash_hook))
        JERROR("Failed to hook function `{}`.", NUCC_Hash_hook.name);

    output_file.open("char_id_hashes.bin");
    output_file.close();

    JINFO("Loaded!");
}