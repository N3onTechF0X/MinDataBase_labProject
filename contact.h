#ifndef CONTACT_H
#define CONTACT_H

#include <stdbool.h>

#define MAX_STR 100

typedef struct Contact {
    char name[MAX_STR];
    int birthday;
    char phone[MAX_STR];
    bool hasTelegram;
    struct Contact *next;
} Contact;

extern char db_filename[MAX_STR];
extern bool license_valid;

void add_contact(Contact **head);
void delete_contact(Contact **head);
void edit_contact(Contact *head);
void view_contacts(Contact *head);
void save_database(const char *filename, const Contact *head);
void load_database(const char *filename, Contact **head);
void export_to_csv(const char *filename, Contact *head);
void filter_birthdays(Contact *head);
void filter_no_telegram(Contact *head);

#endif
