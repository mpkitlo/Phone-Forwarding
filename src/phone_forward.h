/** @file
 * Interfejs klasy przechowującej przekierowania numerów telefonicznych
 *
 * @author Marcin Peczarski <marpe@mimuw.edu.pl>, Michał Kitłowski <mk438753@mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 2022
 */

#ifndef __PHONE_FORWARD_H__
#define __PHONE_FORWARD_H__

#include <stdbool.h>
#include <stddef.h>

/**
 * To jest struktura przechowująca przekierowania numerów telefonów.
 */
struct PhoneForward;
typedef struct PhoneForward PhoneForward;

/**
 * To jest struktura przechowująca ciąg numerów telefonów.
 */
struct PhoneNumbers;
typedef struct PhoneNumbers PhoneNumbers;

/** @brief kopiuje napis.
 * @param[in] num - wskaźnik na napis.
 * @return kopie danego napisu.
 */
char * str_coppy(char * num);

/** @brief porownuje napisy czy są takie same.
 * @param[in] num1 - wskaźnik na pierwszy napis.
 * @param[in] num2 - wskaźnik na drugi napis.
 * @return prawde jeśli napisy są takie same i fałsz jeśli nie są.
 */
bool strings_equal(char * num1, char * num2);

/** @brief porownuje napisy sprawdza ktory jest mniejszy leksykograficznie.
 * @param[in] num1 - wskaźnik na pierwszy napis.
 * @param[in] num2 - wskaźnik na drugi napis.
 * @return mniejszy napis leksykograficznie.
 */
char * compare_strings(char * num1, char * num2);

/** @brief zamienia znak na liczbe.
 * @param[in] digit   – liczba.
 * @return liczbe znaku.
 */
int return_idx(char digit);

/** @brief zamienia liczbe na znak tej liczby.
 * @param[in] idx   – liczba.
 * @return znak liczby.
 */
char return_char(int idx);

/** @brief Sprawdza czy znak jest obowiązującym znakiem.
 * @param[in] digit   – znak.
 * @return prawde jesli znak jest poprawny inaczej fałsz.
 */
bool is_digit(char digit);

/** @brief Liczy długość napisu.
 * zwraca długość napisu.
 * @param[in] num   – wskaźnik na napis.
 * @return liczbe reprezentująca długość naisu.
 */
size_t num_length(char *num);

/** @brief Sprawdza czy dany ciąg znaków jest obowiązującym napisem.
 * @param[in] num   – wskaźnik na napis.
 * @return prawde jesli dany ciąg znaków jest obowiązującym napisem fałsz gdy nie jest.
 */
bool check_if_num(char const *num);

/** @brief Tworzy nową liste napisów.
 * Tworzy nową liste niezawierają napisów.
 * @param[in,out] pnum -wskaźnik na strukturę przechowującą ciąg numerów telefonów.
 * @return Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *         alokować pamięci.
 */
PhoneNumbers * phnumNew(PhoneNumbers * pnum);

/** @brief Dodaje napis na tablice.
 * Dodaje nowy napis na tablice.
 * @param[in,out] pnum – wskaźnik na strukturę przechowującą listę numerów.
 * @param[in] num   – wskaźnik na napis.
 * @return Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *         alokować pamięci.
 */
PhoneNumbers * phnumAdd(PhoneNumbers *pnum ,char *num);

/** @brief Usuwa strukturę.
 * Usuwa strukturę wskazywaną przez @p pnum. Nic nie robi, jeśli wskaźnik ten ma
 * wartość NULL.
 * @param[in] pnum – wskaźnik na usuwaną strukturę.
 */
void phnumDelete(PhoneNumbers *pnum);

/** @brief Udostępnia numer.
 * Udostępnia wskaźnik na napis reprezentujący numer. Napisy są indeksowane
 * kolejno od zera.
 * @param[in] pnum – wskaźnik na strukturę przechowującą ciąg numerów telefonów;
 * @param[in] idx  – indeks numeru telefonu.
 * @return Wskaźnik na napis reprezentujący numer telefonu. Wartość NULL, jeśli
 *         wskaźnik @p pnum ma wartość NULL lub indeks ma za dużą wartość.
 */
char const * phnumGet(PhoneNumbers const *pnum, size_t idx);

/** @brief Tworzy nową strukturę.
 * Tworzy nową strukturę niezawierającą żadnych przekierowań.
 * @return Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *         alokować pamięci.
 */
PhoneForward * phfwdNew(void);

/** @brief Dodaje przekierowanie.
 * Dodaje przekierowanie wszystkich numerów mających prefiks @p num1, na numery,
 * w których ten prefiks zamieniono odpowiednio na prefiks @p num2. Każdy numer
 * jest swoim własnym prefiksem. Jeśli wcześniej zostało dodane przekierowanie
 * z takim samym parametrem @p num1, to jest ono zastępowane.
 * Relacja przekierowania numerów nie jest przechodnia.
 * @param[in,out] pf – wskaźnik na strukturę przechowującą przekierowania
 *                     numerów;
 * @param[in] num1   – wskaźnik na napis reprezentujący prefiks numerów
 *                     przekierowywanych;
 * @param[in] num2   – wskaźnik na napis reprezentujący prefiks numerów,
 *                     na które jest wykonywane przekierowanie.
 * @return Wartość @p true, jeśli przekierowanie zostało dodane.
 *         Wartość @p false, jeśli wystąpił błąd, np. podany napis nie
 *         reprezentuje numeru, oba podane numery są identyczne lub nie udało
 *         się alokować pamięci.
 */
bool phfwdAdd(PhoneForward *pf, char const *num1, char const *num2);

/** @brief Usuwa strukturę.
 * Usuwa strukturę wskazywaną przez @p pf. Nic nie robi, jeśli wskaźnik ten ma
 * wartość NULL.
 * @param[in] pf – wskaźnik na usuwaną strukturę.
 */
void phfwdDelete(PhoneForward *pf);

/** @brief Usuwa przekierowania.
 * Usuwa wszystkie przekierowania, w których parametr @p num jest prefiksem
 * parametru @p num1 użytego przy dodawaniu. Jeśli nie ma takich przekierowań
 * lub napis nie reprezentuje numeru, nic nie robi.
 * @param[in,out] pf – wskaźnik na strukturę przechowującą przekierowania
 *                     numerów;
 * @param[in] num    – wskaźnik na napis reprezentujący prefiks numerów.
 */
void phfwdRemove(PhoneForward *pf, char const *num);

/** @brief Wyznacza przekierowanie numeru.
 * Wyznacza przekierowanie podanego numeru. Szuka najdłuższego pasującego
 * prefiksu. Wynikiem jest ciąg zawierający co najwyżej jeden numer. Jeśli dany
 * numer nie został przekierowany, to wynikiem jest ciąg zawierający ten numer.
 * Jeśli podany napis nie reprezentuje numeru, wynikiem jest pusty ciąg.
 * Alokuje strukturę @p PhoneNumbers, która musi być zwolniona za pomocą
 * funkcji @ref phnumDelete.
 * @param[in] pf  – wskaźnik na strukturę przechowującą przekierowania numerów;
 * @param[in] num – wskaźnik na napis reprezentujący numer.
 * @return Wskaźnik na strukturę przechowującą ciąg numerów lub NULL, gdy nie
 *         udało się alokować pamięci.
 */
PhoneNumbers * phfwdGet(PhoneForward const *pf, char const *num);

/** @brief Funkcja pomocnicza do phfwdReverse.
 * Przechodzi po drzewie i zwraca odwrotne przekierowania
 * @param[in] pf  – wskaźnik na strukturę przechowującą przekierowania numerów;
 * @param[in] result – wskaźnik na liste przekierowań.
 * @param[in] path_number – wskaźnik na napis reprezentujący numer generowany podczas schodzenia po drzewie.
 * @param[in] num – wskaźnik na napis reprezentujący numer.
 */
void pom_phfwdReverse(PhoneForward const *pf, PhoneNumbers *result, char const * path_number, char const *num);

/** @brief Wyznacza przekierowania na dany numer.
 * Wyznacza następujący ciąg numerów: jeśli istnieje numer @p x, taki że wynik
 * wywołania @p phfwdGet z numerem @p x zawiera numer @p num, to numer @p x
 * należy do wyniku wywołania @ref phfwdReverse z numerem @p num. Dodatkowo ciąg
 * wynikowy zawsze zawiera też numer @p num. Wynikowe numery są posortowane
 * leksykograficznie i nie mogą się powtarzać. Jeśli podany napis nie
 * reprezentuje numeru, wynikiem jest pusty ciąg. Alokuje strukturę
 * @p PhoneNumbers, która musi być zwolniona za pomocą funkcji @ref phnumDelete.
 * @param[in] pf  – wskaźnik na strukturę przechowującą przekierowania numerów;
 * @param[in] num – wskaźnik na napis reprezentujący numer.
 * @return Wskaźnik na strukturę przechowującą ciąg numerów lub NULL, gdy nie
 *         udało się alokować pamięci.
 */
PhoneNumbers * phfwdReverse(PhoneForward const *pf, char const *num);

/** @brief Wyznacza przekierowania na dany numer.
 * funkcja odwrotna do phfwdGet, wyznacza wszystkie numery które przekierowują na
 * ten numer w kolejnosci leksykograficznej.
 * @p PhoneNumbers, która musi być zwolniona za pomocą funkcji @ref phnumDelete.
 * @param[in] pf  – wskaźnik na strukturę przechowującą przekierowania numerów;
 * @param[in] num – wskaźnik na napis reprezentujący numer.
 * @return Wskaźnik na strukturę przechowującą ciąg numerów lub NULL, gdy nie
 *         udało się alokować pamięci.
 */
PhoneNumbers * phfwdGetReverse(PhoneForward const *pf, char const *num);

#endif /* __PHONE_FORWARD_H__ */
