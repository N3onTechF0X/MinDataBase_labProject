#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/types.h>
    #include <pwd.h>
#endif
#include <stdbool.h>
#include "contact.h"

char *get_system_username() {
    static char username[MAX_STR];
    #ifdef _WIN32
        DWORD size = MAX_STR;
        GetUserNameA(username, &size);
    #else
        // TODO: Перевірити на лінуксі
        // UPD: Перевірено, лінукс +
        struct passwd *pw = getpwuid(getuid());
        strncpy(username, pw->pw_name, MAX_STR);
        username[MAX_STR - 1] = '\0';
    #endif
    return username;
}

char *generate_license_key(const char *db_name, const char *user_name) {
    static char key[MAX_STR];
    const char *salt = "kitsune";
    uint64_t checksum = 0;

    char data[MAX_STR];
    snprintf(data, sizeof(data), "%s_%s_%s", user_name, salt, db_name);

    for (size_t i = 0; i < strlen(data); i++) {
        checksum ^= (uint64_t) (unsigned char) data[i] << i % 8 * 8;
        checksum += (uint64_t) (unsigned char) data[i] * (i + 9);
    }

    snprintf(key, sizeof(key), "WTC-%08X", (unsigned int) (checksum & 0xFFFFFFFF));
    // printf("[DEBUG] gen key: %s\n", key);
    return key;
}

bool validate_key(const char *key) {
    char expected_key[MAX_STR];
    strcpy(expected_key, generate_license_key(db_filename, get_system_username()));
    // printf("[DEBUG] expected key: %s\tkey: %s\n", expected_key, key);
    return strcmp(key, expected_key) == 0;
}

bool validate_birthday(const int date) {
    const int day = date / 10000;
    const int month = date / 100 % 100;
    const int year = date % 100;
    if (day < 1 || day > 31 || month < 1 || month > 12)
        return false;
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && year % 4 == 0) days_in_month[1] = 29;  // У випадку високосного року
    return day <= days_in_month[month - 1];
}

char *get_config_filename(char *exe_name) {
    static char config_filename[MAX_STR];
    char *dot = strrchr(exe_name, '.');
    if (dot) *dot = '\0';
    snprintf(config_filename, sizeof(config_filename), "%s.cfg", exe_name);
    // printf("[DEBUG] config: %s\n", config_filename);
    return config_filename;
}
