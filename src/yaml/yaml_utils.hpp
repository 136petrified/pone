/*   Created:  07-21-2025
 *   Modified: 01-03-2026
 */

#pragma once

#include <string>

namespace pone::YAML {

/* Checks if a character is alphanumeric.
 *
 * @param c a character.
 * @return true if alphanumeric, false otherwise.
 */
bool isAlnum(char &c);

/* Checks if every character of a string is alphanumeric.
 *
 * @param s a string.
 * @return true if alphanumeric, false otherwise.
 */
bool isAlnum(const char *s);

/* Checks if every character of a string is alphanumeric.
 *
 * @param s a string.
 * @return true if alphanumeric, false otherwise.
 */
bool isAlnum(std::string &s);

/* Checks if a character is in the alphabet.
 *
 * @param c a character.
 * @return true if alphabetic, false otherwise.
 */
bool isAlpha(char &c);

/* Checks if a character is in the alphabet.
 *
 * @param c a character.
 * @return true if alphabetic, false otherwise.
 */
bool isAlpha(const char *s);

/* Checks if every character of a string is in the alphabet.
 *
 * @param s a string.
 * @return true if alphabetic, false otherwise.
 */
bool isAlpha(std::string &s);

/* Checks if a character is numeric.
 *
 * @param c a character.
 * @return true if numeric, false otherwise.
 */
bool isDigit(char &c);

/* Checks if every character of a string is alphanumeric.
 *
 * @param s a string.
 * @return true if numeric, false otherwise.
 */
bool isDigit(const char *s);

/* Checks if every character of a string is in the alphabet.
 *
 * @param s a string.
 * @return true if numeric, false otherwise.
 */
bool isDigit(std::string &s);

/* Check if a character is a quotation mark.
 *
 * @param c a character.
 * @return true if it is a quotation mark, false otherwise.
 */
bool isQuote(char &c);

/* Check if a character is a whitespace character.
 *
 * @param c a character.
 * @return true if it is whitespace, false otherwise.
 */
bool isSpace(char &c);

/* Checks if every character of a string is alphanumeric.
 *
 * @param s a string.
 * @return true if whitespace, false otherwise.
 */
bool isSpace(const char *s);

/* Check if every character of a string is a whitespace character.
 *
 * @param s a string.
 * @return true if it is whitespace, false otherwise.
 */
bool isSpace(std::string &s);

/* Check if a character is a punctuation character.
 *
 * @param c a character.
 * @return true if it is a punctuation mark, false otherwise.
 */
bool isSymbol(char &c);

/* Checks if every character of a string is alphanumeric.
 *
 * @param s a string.
 * @return true if it is a punctuation mark, false otherwise.
 */
bool isSymbol(const char *s);

/* Check if every character of a string is a punctuation character.
 *
 * @param s a string.
 * @return true if it is a punctuation mark, false otherwise.
 */
bool isSymbol(std::string &s);

}  // namespace pone::YAML
