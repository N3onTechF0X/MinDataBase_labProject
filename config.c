#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "utils.h"

void read_config(const char *config_filename) {
    FILE *file = fopen(config_filename, "r");
    if (!file) {
        printf("Create config and db\n");
        file = fopen(config_filename, "w");
        char *key = generate_license_key("new_base.dat", get_system_username());
        // printf("[DEBUG] gen config, new key: %s\n", key);
        fprintf(file, "; auto-generated\n; Database file\nDB = new_base.dat\n; License key\nKEY = %s\n", key);
        fclose(file);
        FILE *db = fopen("new_base.dat", "wb");
        fclose(db);
        license_valid = true;
        return;
    }

    char line[MAX_STR];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == ';') continue;
        if (strncmp(line, "DB =", 4) == 0)
            sscanf(line + 5, "%s", db_filename);
        else if (strncmp(line, "KEY =", 5) == 0) {
            char key[MAX_STR];
            sscanf(line + 6, "%s", key);
            license_valid = strcmp(key, generate_license_key(db_filename, get_system_username())) == 0;
        }
    }
    fclose(file);

    FILE *db = fopen(db_filename, "rb");
    if (!db) {
        printf("Create db %s\n", db_filename);
        db = fopen(db_filename, "wb");
        fclose(db);
    } else
        fclose(db);
}
