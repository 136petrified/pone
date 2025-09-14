/*   Created:  07-23-2025
 *   Modified: 09-14-2025
 */

#ifndef PONE_YAML_TOKENIZER_HPP
#define PONE_YAML_TOKENIZER_HPP

#include <array>
#include <fstream>
#include <memory>
#include <stack>
#include <string>
#include <vector>

#include "yaml_utils.hpp"

namespace YAML {

/*! Abstract base class for Tokens.
 */
class Token {
   public:
    /*! An enum of all types of Tokens. */
    enum class Type {
        Backslash,         /*! The backslash character \ */
        Colon,             /*! The colon character : */
        Comma,             /*! The comma character , */
        Comment,           /*! A grouped type for YAML comments */
        Dash,              /*! The dash character -*/
        DoubleQuote,       /*! The double quote character " */
        DoubleQuotedKey,   /*! A grouped type for keys within double quotes */
        DoubleQuotedValue, /*! A grouped type for values within double quotes */
        Key,               /*! A grouped type for keys */
        LeftBrace,         /*! The left brace character { */
        LeftBracket,       /*! The left bracket character [ */
        Newline,           /*! The newline character \n */
        None,              /*! Placeholder token type */
        NumSign,           /*! The number sign character # */
        RightBrace,        /*! The right brace character } */
        RightBracket,      /*! The right bracket character ]*/
        Scalar,            /*! An alphanumeric identifier type */
        SingleQuote,       /* The single quote character ' */
        SingleQuotedKey,   /* A grouped type for keys within single quotes */
        SingleQuotedValue, /* A grouped type for values within single quotes */
        Space,             /* The space character ' ' */
        Symbol,            /* A generic symbol character type */
        Tab,               /* The tab character \t */
        Value,             /* A grouped type for values */
    };

    /*! An enum of all derived Token classes */
    enum class Class {
        // This is a "type" to differentiate derived classes
        Group, /*! The GroupToken class */
        Single /*! The SingleToken class */
    };

    /*! The total size of the token types. */
    static const int ALL_TOKENS_SIZE = 24;
    const std::array<Type, ALL_TOKENS_SIZE> ALL_TOKEN_TYPES = {
        Type::Backslash,
        Type::Colon,
        Type::Comma,
        Type::Comment,
        Type::Dash,
        Type::DoubleQuote,
        Type::DoubleQuotedKey,
        Type::DoubleQuotedValue,
        Type::Key,
        Type::LeftBracket,
        Type::LeftBrace,
        Type::Newline,
        Type::None,
        Type::NumSign,
        Type::RightBrace,
        Type::RightBracket,
        Type::Scalar,
        Type::SingleQuote,
        Type::SingleQuotedKey,
        Type::SingleQuotedValue,
        Type::Space,
        Type::Symbol,
        Type::Tab,
        Type::Value};

    /*! Token constructor. */
    Token();

    /*! Pure virtual token destructor */
    virtual ~Token() = 0;

    // Start of basic Token functions
    // ----------------------------------------
    /*! Pure virtual function for making a deep copy of a Token.
        \return a unique_ptr of type Token.
     */
    virtual std::unique_ptr<Token> clone() const = 0;

    /*! Pure virtual function for getting the class of a Token.

        \return an enum value of type Token::Class.
        \sa Token::Class
     */
    virtual Class getClass() const = 0;

    /*! Pure virtual function for getting the type of a Token.

        \return an enum value of type Token::Type.
        \sa Token::Type
     */
    virtual Type getType() const = 0;

    /*! Pure virtual function for setting the type of a Token.
        \param type the type assigned to the Token.
        \sa Token::Type
     */
    virtual void setType(const Type &type) = 0;
    // ----------------------------------------
    // End of basic Token functions

    // Start of basic SingleToken functions
    // ----------------------------------------
    /*! A virtual function to the string data from a SingleToken.

        \return a read-only std::string reference of the data.
     */
    virtual const std::string &getData() const;

    /*! A virtual function to set the string data of a SingleToken.

        \param data a std::string representing SingleToken data.
     */
    virtual void setData(const std::string &data);
    // End of basic SingleToken functions

    // Start of basic GroupToken functions
    // ----------------------------------------
    /* A virtual function for erasing all of the Tokens within a GroupToken.
     */
    virtual void clearTokenGroup();

    /*! A virtual function for getting a list of a Tokens within a GroupToken.

       \return a vector of Token pointers.
     */
    virtual std::vector<std::unique_ptr<Token>> getTokenGroup() const;

    /*! A virtual function for inserting a Token to a GroupToken.
     */
    virtual void insertToTokenGroup(std::unique_ptr<Token> &&token);

    /*! A virtual function. Checks if a GroupToken is empty.
        \return true if empty, false otherwise.
     */
    virtual bool isTokenGroupEmpty() const;

    /*! A virtual function. The number of Tokens within a GroupToken.

        \return a size_t value.
     */
    virtual size_t sizeOfTokenGroup() const;
    // ----------------------------------------
    // End of basic GroupToken functions
};

/*! Token class for single-storage Tokens

    \sa Token
 */
class SingleToken : public Token {
   public:
    /*!
     */
    SingleToken();
    SingleToken(const Token::Type &type);
    SingleToken(const Token::Type &type, const std::string &data);
    SingleToken(const Token::Type &type, std::string &&data);
    SingleToken(const SingleToken &other);
    SingleToken &operator=(const SingleToken &other);
    const std::string &getData() const override;
    void setData(const std::string &data) override;
    ~SingleToken();

    // Pure virtual functions from Token
    std::unique_ptr<Token> clone() const override;
    Token::Class getClass() const override;
    Token::Type getType() const override;
    void setType(const Token::Type &type) override;

   private:
    Token::Class m_class;
    std::string m_data;
    Token::Type m_type;
};

/*  func(Token &) means that you
 *  should pass the reference before making it read access
 *  only
 */

class GroupToken : public Token {
    // NOTE: This allows for a Token to be made up of Tokens
   public:
    GroupToken();
    GroupToken(const Token::Type &type);
    GroupToken(const GroupToken &other);
    GroupToken(GroupToken &&other);
    GroupToken &operator=(const GroupToken &other);
    GroupToken &operator=(GroupToken &&other);
    void clearTokenGroup() override;
    std::vector<std::unique_ptr<Token>> getTokenGroup() const override;
    void insertToTokenGroup(std::unique_ptr<Token> &&token) override;
    bool isTokenGroupEmpty() const override;
    size_t sizeOfTokenGroup() const override;
    ~GroupToken();

    // Pure virtual functions from Token
    std::unique_ptr<Token> clone() const override;
    Token::Class getClass() const override;
    Token::Type getType() const override;
    void setType(const Token::Type &type) override;

   private:
    Token::Class m_class;
    std::vector<std::unique_ptr<Token>> m_tokenGroup;
    size_t m_tokenGroupSize;
    Token::Type m_type;
};

class Tokenizer {
   public:
    Tokenizer();
    Tokenizer(const std::string &file_name);
    std::vector<std::unique_ptr<Token>> getTokens() const;
    void tokenize();
    ~Tokenizer();

   protected:
    void backslash();
    void backslash(GroupToken &toGtok);
    void clearBuf();
    void colon();
    void colon(GroupToken &toGtok);
    void comma();
    void comma(GroupToken &toGtok);
    void comment();
    void comment(GroupToken &toGtok);
    std::unique_ptr<GroupToken> createGroupToken(
        const Token::Type &tokenType) const;
    std::unique_ptr<GroupToken> createGroupToken(GroupToken &gtok);
    std::unique_ptr<SingleToken> createSingleToken(
        const Token::Type &tokenType) const;
    std::unique_ptr<SingleToken> createSingleToken(const Token::Type &tokenType,
                                                   std::string &&data) const;
    std::unique_ptr<SingleToken> createSingleToken(SingleToken &stok);
    void dash();
    void dash(GroupToken &toGtok);
    void doubleQuote();
    void doubleQuote(GroupToken &toGtok);
    void doubleQuotedKey(GroupToken &toGtok);
    void doubleQuotedValue(GroupToken &toGtok);
    void insertGroupTokenToGroupToken(GroupToken &toGtok,
                                      const Token::Type &tokenType);
    void insertGroupTokenToGroupToken(
        GroupToken &to_gtok, const std::unique_ptr<GroupToken> &gtokPtr);
    void insertGroupTokenToGroupToken(GroupToken &toGtok,
                                      std::unique_ptr<GroupToken> &&gtokPtr);
    void insertGroupTokenToTokens(const Token::Type &tokenType);
    void insertGroupTokenToTokens(const std::unique_ptr<GroupToken> &gtokPtr);
    void insertGroupTokenToTokens(std::unique_ptr<GroupToken> &&gtokPtr);
    void insertSingleTokenToGroupToken(GroupToken &toGtok,
                                       const Token::Type &tokenType);
    void insertSingleTokenToGroupToken(GroupToken &toGtok,
                                       const Token::Type &tokenType,
                                       std::string &&data);
    void insertSingleTokenToGroupToken(
        GroupToken &toGtok, const std::unique_ptr<SingleToken> &stokPtr);
    void insertSingleTokenToGroupToken(GroupToken &toGtok,
                                       std::unique_ptr<SingleToken> &&stokPtr);
    void insertSingleTokenToTokens(const Token::Type &tokenType);
    void insertSingleTokenToTokens(const Token::Type &tokenType,
                                   std::string &&data);
    void insertSingleTokenToTokens(const std::unique_ptr<SingleToken> &stokPtr);
    void insertSingleTokenToTokens(std::unique_ptr<SingleToken> &&stokPtr);
    void key();
    void key(GroupToken &toGtok);
    void leftBrace();
    void leftBrace(GroupToken &toGtok);
    void leftBracket();
    void leftBracket(GroupToken &toGtok);
    const char lookahead();
    void mapping();  // TODO: Group mapping
    void newline();
    void newline(GroupToken &toGtok);
    void next();
    void numSign();
    void numSign(GroupToken &toGtok);
    void otherSymbols();
    void otherSymbols(GroupToken &toGtok);
    void rightBrace();
    void rightBrace(GroupToken &toGtok);
    void rightBracket();
    void rightBracket(GroupToken &toGtok);
    void scalar();
    void scalar(GroupToken &toGtok);
    void singleQuote();
    void singleQuote(GroupToken &toGtok);
    void singleQuotedKey();
    void singleQuotedKey(GroupToken &toGtok);
    void singleQuotedValue();
    void singleQuotedValue(GroupToken &toGtok);
    void space();
    void space(GroupToken &toGtok);
    // This is a symbol "multiplexer"
    void sym();
    void sym(GroupToken &toGtok);
    void tab();
    void tab(GroupToken &toGtok);
    void value();
    void value(GroupToken &toGtok);
    // This is a whitespace "multiplexer"
    void whitespace();
    void whitespace(GroupToken &toGtok);

   private:
    std::string m_fileName;
    std::ifstream m_ifs;

    std::vector<std::unique_ptr<Token>> m_tokens;
    size_t m_tokensSize;

    std::string m_buf;
    char m_char;

    std::stack<GroupToken> groupTokenStack;
    bool m_endOfFile;
};
}  // namespace YAML

#endif  // PONE_YAML_TOKENIZER_HPP
