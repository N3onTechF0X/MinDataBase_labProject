#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

char *get_system_username();
bool validate_key(const char *key);
bool validate_birthday(int date);
char *get_config_filename(char *exe_name);
char *generate_license_key(const char *db_name, const char *user_name);

#endif
