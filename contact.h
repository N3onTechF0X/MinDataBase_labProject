#ifndef CONTACT_H
#define CONTACT_H

#include <stdbool.h>

#define MAX_STR 100

/**
 * @brief Структура, що представляє контакт.
 */
typedef struct Contact {
    char name[MAX_STR];       ///< Ім’я та прізвище контакту.
    int birthday;             ///< Дата народження у форматі ДДММРР.
    char phone[MAX_STR];      ///< Номер телефону.
    bool hasTelegram;         ///< Наявність Telegram.
    struct Contact *next;     ///< Вказівник на наступний контакт у списку.
} Contact;

/// Глобальна змінна — ім’я файлу бази даних.
extern char db_filename[MAX_STR];

/// Глобальна змінна — стан ліцензії (валідна або ні).
extern bool license_valid;

/**
 * @brief Додає новий контакт до списку.
 *
 * @param head Вказівник на вказівник голови списку контактів.
 */
void add_contact(Contact **head);

/**
 * @brief Видаляє контакт за іменем.
 *
 * @param head Вказівник на вказівник голови списку контактів.
 */
void delete_contact(Contact **head);

/**
 * @brief Редагує існуючий контакт за іменем.
 *
 * @param head Вказівник на голову списку контактів.
 */
void edit_contact(Contact *head);

/**
 * @brief Виводить усі контакти на екран.
 *
 * @param head Вказівник на голову списку контактів.
 */
void view_contacts(Contact *head);

/**
 * @brief Зберігає всі контакти до бінарного файлу бази даних.
 *
 * @param filename Ім’я файлу для збереження.
 * @param head Вказівник на голову списку контактів.
 */
void save_database(const char *filename, const Contact *head);

/**
 * @brief Завантажує контакти з бінарного файлу бази даних.
 *
 * @param filename Ім’я файлу бази даних.
 * @param head Вказівник на вказівник голови списку контактів.
 */
void load_database(const char *filename, Contact **head);

/**
 * @brief Експортує список контактів у CSV-файл (доступно лише з валідною ліцензією).
 *
 * @param filename Базова назва файлу (розширення .csv додається автоматично, якщо відсутнє).
 * @param head Вказівник на голову списку контактів.
 */
void export_to_csv(const char *filename, Contact *head);

/**
 * @brief Фільтрує та виводить контакти за місяцем народження (доступно лише з валідною ліцензією).
 *
 * @param head Вказівник на голову списку контактів.
 */
void filter_birthdays(Contact *head);

/**
 * @brief Виводить контакти, які не мають Telegram (доступно лише з валідною ліцензією).
 *
 * @param head Вказівник на голову списку контактів.
 */
void filter_no_telegram(Contact *head);

#endif
