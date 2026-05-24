/* Created:  2026-05-23
 * Modified: 2026-05-24
 */

#pragma once

#include "toml_token.hpp"
#include <fstream>
#include <iostream>
#include <stack>

namespace pone::TOML {

/* A class to tokenize custom YAML files for this program.
 */
class Tokenizer {
    // +----------------------------------+
    // + Tokenizer data members           +
    // +----------------------------------+

    std::string m_fileName;
    std::ifstream m_ifs;

    int m_indent; // Defined by YAML config
    int m_depth;  // Current depth of tokenizer
                  // not depth of a token.

    /* A stack of GroupToken pointers. */
    std::stack<std::shared_ptr<Token>> groupStack;
    size_t m_size;

    std::string m_buf;
    char m_char;

    bool m_endOfFile;

  public:
    // +----------------------------------+
    // + Tokenizer constructors           +
    // +----------------------------------+

    /* Default Tokenizer constructor. */
    Tokenizer();

    /* Tokenizer constructor.
     *
     * @param fileName the string .YAML filename to load.
     */
    Tokenizer(const std::string &fileName);

    /* Gets a deep copy of the vector of Tokens within the Tokenizer.
     *
     * @return a vector of Token pointers.
     */

    /* Gets the size of the Tokenizer.
     *
     * @return a size_t value.
     */

    // +----------------------------------+
    // + Tokenizer functions              +
    // +----------------------------------+

    size_t size() const;

    /* Gets a read-only reference to the tree of Tokens.
     *
     * @return a pointer to the token tree.
     */
    const std::shared_ptr<Token> &getTokens() const;

    /* Initializes the Tokenizer.
       This function is the entry point of the Tokenizer.
     */

    void tokenize();

    /*! Tokenizer destructor. */
    ~Tokenizer();

    // FIXME: Enable the protected access specifier
    //        after testing! v v v

    // protected:
    /* Processes an array token.
     */
    void array();

    /* Clears the current character buffer in the tokenizer.
     */
    void clearBuf();

    /* Processes a comma token.
     */
    void comma();

    /* Processes a comment token.
     */
    void comment();

    /* Creates a shared GroupToken pointer.
     *
     * @param type the Token type to create the GroupToken with.
     * @return a shared pointer to the GroupToken.
     */
    std::shared_ptr<GroupToken> createGroupToken(const Token::Type &type) const;

    /* Creates a shared GroupToken pointer from an existing GroupToken.
     *
     * @param gtok the GroupToken object to tokenize.
     * @return a shared pointer to the GroupToken.
     */
    std::shared_ptr<GroupToken> createGroupToken(GroupToken &gtok);

    /* Creates a shared SingleToken pointer.
     *
     * @param type the Token type to create the SingleToken with.
     * @return a shared pointer to the SingleToken.
     */
    std::shared_ptr<SingleToken>
    createSingleToken(const Token::Type &type) const;

    /* Creates a shared SingleToken pointer with string data.
     *
     * @param type the Token type to create the SingleToken with.
     * @param data a string rvalue reference.
     * @return a shared pointer to the SingleToken.
     */
    std::shared_ptr<SingleToken> createSingleToken(const Token::Type &type,
                                                   std::string &&data) const;

    /* Creates a shared SingleToken pointer from an existing SingleToken.
     *
     * @param stok the SingleToken object to tokenize.
     * @return a shared pointer to the SingleToken.
     */
    std::shared_ptr<SingleToken> createSingleToken(SingleToken &stok);

    /* Processes a double quote Token.
     */
    void doubleQuote();

    /* Inserts a GroupToken to a parent GroupToken.
     *
     * @param type the Token type.
     */
    void insertGroupToken(const Token::Type &type);

    /* Inserts a GroupToken to a parent GroupToken.
     *
     * @param gtok a pointer to the GroupToken.
     */
    void insertGroupToken(const std::shared_ptr<GroupToken> &gtok);

    /* Moves and inserts a GroupToken to a parent GroupToken.
     *
     * @param gtokPtr a pointer rvalue reference to a GroupToken.
     */

    void insertSingleToken(const Token::Type &type);

    /* Creates and inserts a SingleToken to a parent GroupToken with
     * string data.
     *
     * @param type the Token type.
     * @param data a string rvalue reference.
     */
    void insertSingleToken(const Token::Type &type, std::string &&data);

    /* Inserts a SingleToken to a parent GroupToken.
     *
     * @param stok a pointer to the SingleToken.
     */
    void insertSingleToken(const std::shared_ptr<SingleToken> &stok);

    /* Processes a key token.
     */
    void key();

    /* Processes a left brace ({) token.
     */
    void leftBrace();

    /* Processes a left bracket ([) token.
     */
    void leftBracket();

    /* Processes literals.
     */
    void literal();

    /* Peeks to the next character in the ifstream.
     *
     * @return a read-only character.
     */
    const char lookahead();

    /* Processes a mapping token.
     * A mapping is defined as a key and value pair.
     */
    void mapping();

    /* Processes a newline token.
     */
    void newline();

    /* Advances the next character in the ifstream.
     *
     * @throws EndOfIstreamException if the filestream throws EOF.
     */
    void next();

    /* Processes a number sign (#) token.
     */
    void numSign();

    /* Prints out a tree of the tokenizer.
     */
    void print(std::ostream &out) const;

    /* Processes a quoted segment of tokens.
     */
    void quoted();

    /* Processes a right brace ({) token.
     */
    void rightBrace();

    /* Processes a right bracket ([) token.
     */
    void rightBracket();

    /* Processes a single quote token.
     */
    void singleQuote();

    /* Processes a table token.
     */
    void table();

    /* Processes a value token.
     */
    void value();

    /* Processes a whitespace token. */
    void whitespace();

    /* Friend function to print out the tokenizer.
     */
    friend std::ostream &operator<<(std::ostream &out,
                                    const Tokenizer &tokenizer);
};

} // namespace pone::TOML
