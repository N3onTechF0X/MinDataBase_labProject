/**
 * @file main.c
 * @author N3onTechF0X
 * @date 2025-05-22
 * @brief Мінімалістична база данних контактів у бінарному файлі.
 * @license CCO 1.0 Universal
 */
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "contact.h"
#include "config.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Contact *head = NULL;
    const char *config_filename = get_config_filename(argv[0]);

    read_config(config_filename);
    load_database(db_filename, &head);

    int choice;
    do {
        printf("1. Переглянути контакти\n");
        printf("2. Додати контакт\n");
        printf("3. Редагувати контакт\n");
        printf("4. Видалити контакт\n");
        printf("5. Експорт у CSV\n");
        printf("6. Фільтр за днями народження\n");
        printf("7. Фільтр без Telegram\n");
        printf("0. Вийти\n");
        printf("Ваш вибір: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: view_contacts(head);
                break;
            case 2: add_contact(&head);
                break;
            case 3: edit_contact(head);
                break;
            case 4: delete_contact(&head);
                break;
            case 5: {
                char name[MAX_STR];
                printf("Ім'я файлу: ");
                fgets(name, MAX_STR, stdin);
                name[strcspn(name, "\n")] = 0;
                export_to_csv(name, head);
                break;
            }
            case 6: filter_birthdays(head);
                break;
            case 7: filter_no_telegram(head);
                break;
        }

        save_database(db_filename, head);
    } while (choice != 0);

    while (head) {
        Contact *tmp = head;
        head = head->next;
        free(tmp);
    }

    return 0;
}
