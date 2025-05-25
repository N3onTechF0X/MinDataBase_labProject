#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

/**
 * @brief Отримує ім’я поточного користувача системи.
 *
 * @return Вказівник на статичний рядок з ім’ям користувача.
 */
char *get_system_username();

/**
 * @brief Перевіряє ліцензійний ключ на коректність.
 *
 * @param key Ліцензійний ключ, що перевіряється.
 * @return true, якщо ключ дійсний, інакше false.
 */
bool validate_key(const char *key);

/**
 * @brief Перевіряє коректність дати народження у форматі ДДММРР.
 *
 * @param date Ціле число, що представляє дату у форматі ДДММРР.
 * @return true, якщо дата коректна, інакше false.
 */
bool validate_birthday(int date);

/**
 * @brief Формує назву конфігураційного файлу на основі імені виконуваного файлу.
 *
 * @param exe_name Ім’я виконуваного файлу.
 * @return Вказівник на статичний рядок з назвою конфігураційного файлу.
 */
char *get_config_filename(char *exe_name);

/**
 * @brief Генерує ліцензійний ключ на основі імені бази даних та користувача.
 *
 * @param db_name Назва бази даних.
 * @param user_name Ім’я користувача.
 * @return Вказівник на статичний рядок зі згенерованим ліцензійним ключем.
 */
char *generate_license_key(const char *db_name, const char *user_name);

#endif
