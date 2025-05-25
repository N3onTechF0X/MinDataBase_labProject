#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "utils.h"

char db_filename[MAX_STR] = "new_base.dat";
bool license_valid = false;

void save_database(const char *filename, const Contact *head) {
    FILE *file = fopen(filename, "wb");
    if (!file) return;
    for (const Contact *p = head; p; p = p->next)
        fwrite(p, sizeof(Contact) - sizeof(Contact *), 1, file);
    fclose(file);
    // printf("[DEBUG] save db\n");
}

void load_database(const char *filename, Contact **head) {
    FILE *file = fopen(filename, "rb");
    if (!file) return;
    Contact temp;
    while (fread(&temp, sizeof(Contact) - sizeof(Contact *), 1, file)) {
        Contact *new_node = malloc(sizeof(Contact));
        *new_node = temp;
        new_node->next = *head;
        *head = new_node;
    }
    fclose(file);
    // printf("[DEBUG] load db\n");
}

void add_contact(Contact **head) {
    Contact *new_contact = malloc(sizeof(Contact));
    printf("Прізвище та ім’я: ");
    fgets(new_contact->name, MAX_STR, stdin);
    new_contact->name[strcspn(new_contact->name, "\n")] = 0;
    do {
        printf("Нова дата народження (ДДММРР): ");
        scanf("%d", &new_contact->birthday);
        getchar();
        if (!validate_birthday(new_contact->birthday))
            printf("Неправильна дата. Перевірте формат (ДДММРР)\n");
    } while (!validate_birthday(new_contact->birthday));
    printf("Номер телефону: ");
    fgets(new_contact->phone, MAX_STR, stdin);
    new_contact->phone[strcspn(new_contact->phone, "\n")] = 0;
    char tg[10];
    printf("Є Telegram (так/ні): ");
    fgets(tg, 10, stdin);
    new_contact->hasTelegram = strncmp(tg, "так", 3) == 0;
    new_contact->next = *head;
    *head = new_contact;
    // printf("[DEBUG] add contact\n");
}

void delete_contact(Contact **head) {
    char name[MAX_STR];
    printf("Введіть ім’я для видалення: ");
    fgets(name, MAX_STR, stdin);
    name[strcspn(name, "\n")] = 0;
    Contact **curr = head;
    while (*curr) {
        if (strcmp((*curr)->name, name) == 0) {
            Contact *to_delete = *curr;
            *curr = (*curr)->next;
            free(to_delete);
            printf("Контакт видалено.\n");
            // printf("[DEBUG] del contact success\n");
            return;
        }
        curr = &(*curr)->next;
    }
    printf("Контакт не знайдено.\n");
    // printf("[DEBUG] del contact failed\n");
}

void edit_contact(Contact *head) {
    char name[MAX_STR];
    printf("Введіть ім’я для редагування: ");
    fgets(name, MAX_STR, stdin);
    name[strcspn(name, "\n")] = 0;
    while (head) {
        if (strcmp(head->name, name) == 0) {
            printf("Нове ім’я: ");
            fgets(head->name, MAX_STR, stdin);
            head->name[strcspn(head->name, "\n")] = 0;
            do {
                printf("Нова дата народження (ДДММРР): ");
                scanf("%d", &head->birthday);
                getchar();
                if (!validate_birthday(head->birthday))
                    printf("Неправильна дата. Перевірте формат (ДДММРР): ");
            } while (!validate_birthday(head->birthday));
            printf("Новий номер телефону: ");
            fgets(head->phone, MAX_STR, stdin);
            head->phone[strcspn(head->phone, "\n")] = 0;
            char tg[10];
            printf("Є Telegram (так/ні): ");
            fgets(tg, 10, stdin);
            head->hasTelegram = strncmp(tg, "так", 3) == 0;
            printf("Контакт оновлено.\n");
            // printf("[DEBUG] edit contact success\n");
            return;
        }
        head = head->next;
    }
    printf("Контакт не знайдено.\n");
    // printf("[DEBUG] edit contact failed\n");
}

void view_contacts(Contact *head) {
    while (head) {
        printf("Ім’я: %s\nДень нар: %06d\nТелефон: %s\nTelegram: %s\n\n",
               head->name, head->birthday, head->phone, head->hasTelegram ? "так" : "ні");
        head = head->next;
    }
    // printf("[DEBUG] view contacts\n");
}

void export_to_csv(const char *filename, Contact *head) {
    if (!license_valid) {
        printf("Немає доступу. Невірний ліцензійний ключ.\n");
        return;
    }

    char full_filename[256];
    if (strrchr(filename, '.') == NULL)
        snprintf(full_filename, sizeof(full_filename), "%s.csv", filename);
    else
        snprintf(full_filename, sizeof(full_filename), "%s", filename);

    FILE *file = fopen(full_filename, "wb");
    if (!file) return;

    const unsigned char bom[] = {0xEF, 0xBB, 0xBF};
    fwrite(bom, sizeof(bom), 1, file);

    while (head) {
        char line[MAX_STR * 4];
        snprintf(line, sizeof(line), "%s;%06d;%s;%s\n",
                 head->name, head->birthday, head->phone, head->hasTelegram ? "так" : "ні");
        fputs(line, file);
        head = head->next;
    }
    fclose(file);
    printf("Експорт завершено.\n");
    // printf("[DEBUG] export to csv\n");
}

void filter_birthdays(Contact *head) {
    if (!license_valid) {
        printf("Немає доступу.\n");
        return;
    }
    int month;
    printf("Введіть місяць (ММ): ");
    scanf("%d", &month);
    getchar();
    while (head) {
        const int mm = head->birthday / 100 % 100;
        if (mm == month)
            printf("Ім’я: %s | Дата: %06d\n", head->name, head->birthday);
        head = head->next;
    }
    // printf("[DEBUG] view by birthday\n");
}

void filter_no_telegram(Contact *head) {
    if (!license_valid) {
        printf("Немає доступу.\n");
        return;
    }
    while (head) {
        if (!head->hasTelegram)
            printf("Ім’я: %s | Телефон: %s\n", head->name, head->phone);
        head = head->next;
    }
    // printf("[DEBUG] view by telegram\n");
}
