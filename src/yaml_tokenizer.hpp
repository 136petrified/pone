/*   Created:  07-23-2025
 *   Modified: 09-16-2025
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
        List,              /*! A grouped type for list containers */
        ListElement,       /*! A grouped type for list elements */
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
        \return a unique_ptr of the Token copy.
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

        \return a read-only string reference of the data.
     */
    virtual const std::string &getData() const;

    /*! A virtual function to set the string data of a SingleToken.

        \param data a string representing SingleToken data.
     */
    virtual void setData(const std::string &data);
    // End of basic SingleToken functions

    // Start of basic GroupToken functions
    // ----------------------------------------
    /* A virtual function for erasing all of the Tokens within a GroupToken.
     */
    virtual void clearTokenGroup();

    /*! A virtual function for getting a vector of a Tokens within a GroupToken.

       \return a vector of Token pointers.
     */
    virtual std::vector<std::unique_ptr<Token>> getTokenGroup() const;

    /*! A virtual function for inserting a Token to a GroupToken.

        \param token an rvalue reference to a Token pointer.
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
    /*! Default SingleToken constructor.

        \sa Token
     */
    SingleToken();

    /*! SingleToken constructor.

        \param type the assigned type of SingleToken.
        \sa Token
     */
    SingleToken(const Token::Type &type);

    /*! SingleToken constructor.

        \param type the assigned type of SingleToken.
        \param data a read-only string reference of the Token's data.
        \sa Token
     */
    SingleToken(const Token::Type &type, const std::string &data);

    /*! SingleToken constructor.

        \param type the assigned type of SingleToken.
        \param data a string rvalue reference of the Token's data.
        \sa Token
     */
    SingleToken(const Token::Type &type, std::string &&data);

    /*! SingleToken copy constructor.

        \param other the SingleToken to copy from.
        \sa Token
     */
    SingleToken(const SingleToken &other);

    /*! SingleToken copy assignment.

        \param other the SingleToken to copy from.
        \sa Token
     */
    SingleToken &operator=(const SingleToken &other);

    /*! Gets string data from a SingleToken.

        \return a read-only string reference SingleToken data.
        \sa Token
     */
    const std::string &getData() const override;

    /*! Sets string data for a SingleToken.

        \param data a string representing SingleToken data.
        \sa Token
     */
    void setData(const std::string &data) override;

    /*! SingleToken destructor.
     */
    ~SingleToken();

    // Pure virtual functions from Token
    // ----------------------------------------
    /*! Creates a deep copy of a SingleToken.

        \returns a unique_ptr of the Token copy.
        \sa Token
     */
    std::unique_ptr<Token> clone() const override;

    /*! Gets the class of a SingleToken.

        \return an enum value of type Type::Class.
        \sa Token, Token::Class
     */
    Token::Class getClass() const override;

    /*! Gets the type of a SingleToken.

        \return an enum value of type Token::Type.
        \sa Token, Token::Type
     */
    Token::Type getType() const override;

    /*! Sets the type of a SingleToken.

        \param type the type assigned to the SingleToken.
        \sa Token, Token::Type
     */
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

/*! Token class for Tokens that contain nested Tokens.

    \sa Token
 */
class GroupToken : public Token {
    // NOTE: This allows for a Token to be made up of Tokens
   public:
    /*! Default GroupToken constructor.

        \sa Token
     */
    GroupToken();

    /*! GroupToken constructor.

        \param type the assigned type of GroupToken.
        \sa Token
     */
    GroupToken(const Token::Type &type);

    /*! GroupToken copy constructor.

        \param other the GroupToken to copy from.
        \sa Token
     */
    GroupToken(const GroupToken &other);

    /*! GroupToken move constructor.

        \param other an rvalue reference to the GroupToken to move from.
        \sa Token
     */
    GroupToken(GroupToken &&other) noexcept;

    /*! GroupToken copy assignment.

        \param other the GroupToken to copy from.
        \sa Token
     */
    GroupToken &operator=(const GroupToken &other);

    /*! GroupToken move assignment.

        \param other an rvalue reference to the GroupToken to move from.
        \sa Token
     */
    GroupToken &operator=(GroupToken &&other) noexcept;

    /*! Clears all the elements from a GroupToken.

        \sa Token
     */
    void clearTokenGroup() override;

    /*! Gets the vector of Tokens within a GroupToken.

        \return a vector of Token pointers.
        \sa Token
     */

    std::vector<std::unique_ptr<Token>> getTokenGroup() const override;

    /*! Inserts a Token into a GroupToken.

        \param token an rvalue reference to a Token pointer.
        \sa Token
     */
    void insertToTokenGroup(std::unique_ptr<Token> &&token) override;

    /*! Checks if a GroupToken is empty.

        \return true if empty, false otherwise.
        \sa Token
     */

    bool isTokenGroupEmpty() const override;

    /*! Gets the size of a GroupToken.

        \return a size_t value.
        \sa Token
     */
    size_t sizeOfTokenGroup() const override;

    /*! GroupToken destructor.
     */
    ~GroupToken();

    // Pure virtual functions from Token

    /*! Creates a deep copy of a GroupToken.

        \return a unique_ptr to the GroupToken copy.
        \sa Token
     */
    std::unique_ptr<Token> clone() const override;

    /*! Gets the class of a GroupToken.

        \return an enum value of type Token::Class.
        \sa Token::Class, Token
     */
    Token::Class getClass() const override;

    /*! Gets the type of a GroupToken.

        \return an enum value of type Token::Type.
        \sa Token::Type, Token
     */
    Token::Type getType() const override;

    /*! Sets the type of a GroupToken.

        \param type the type assigned to a GroupToken.
        \sa Token::Type, Token
     */
    void setType(const Token::Type &type) override;

   private:
    Token::Class m_class;
    std::vector<std::unique_ptr<Token>> m_tokenGroup;
    size_t m_tokenGroupSize;
    Token::Type m_type;
};

/*! A class to tokenize custom YAML files for this program.
 */
class Tokenizer {
   public:
    /*! Default Tokenizer constructor. */
    Tokenizer();

    /*! Tokenizer constructor.

        \param file_name the string .YAML filename to load.
     */
    Tokenizer(const std::string &file_name);

    /*! Gets a deep copy of the vector of Tokens within the Tokenizer.

        \return a vector of Token pointers.
     */
    std::vector<std::unique_ptr<Token>> getTokens() const;

    /*! Initializes the Tokenizer.
        This function is the starting point of the Tokenizer.
     */
    void tokenize();

    /*! Tokenizer destructor. */
    ~Tokenizer();

   protected:
    /*! Processes a backslash Token.
     */
    void backslash();

    /*! Processes a nested backslash Token.

        \param toGtok a reference to the current parent GroupToken.
     */
    void backslash(GroupToken &toGtok);

    /*! Clears the current character buffer in the Tokenizer.
     */
    void clearBuf();

    /*! Processes a colon Token.
     */
    void colon();

    /*! Processes a nested colon Token.

        \param toGtok a reference to the current parent GroupToken.
     */
    void colon(GroupToken &toGtok);

    /*! Processes a comma Token.
     */
    void comma();

    /*! Processes a nested comma Token.

        \param toGtok a reference to the current parent GroupToken.
     */
    void comma(GroupToken &toGtok);

    /*! Processes a comment Token.
     */
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

    /*! Processes a dash Token.
     */
    void dash();
    void dash(GroupToken &toGtok);

    /*! Processes a doubleQuote Token.
     */
    void doubleQuote();
    void doubleQuote(GroupToken &toGtok);

    /*! Processes a double-quoted key Token.
        A double-quoted key is a key enclosed in quotes.
     */
    void doubleQuotedKey();
    void doubleQuotedKey(GroupToken &toGtok);

    /*! Processes a double-quoted value Token.
        A double-quoted value is a value enclosed in quotes.
     */
    void doubleQuotedValue();
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

    /*! Processes a key Token.
     */
    void key();
    void key(GroupToken &toGtok);

    /*! Processes a left brace Token.
     */
    void leftBrace();
    void leftBrace(GroupToken &toGtok);

    /*! Processes a left bracket Token.
     */
    void leftBracket();
    void leftBracket(GroupToken &toGtok);

    /*! Processes a list Token.
     */
    void list();
    void list(GroupToken &toGtok);

    /*! Processes a list element Token.
     */
    void listElement();
    void listElement(GroupToken &toGtok);
    const char lookahead();

    /*! Processes a mapping Token.
        A mapping is defined as a key and value pair.
     */
    void mapping();  // TODO: Group mapping
    void mapping(GroupToken &toGtok);

    /*! Processes a newline Token.
     */
    void newline();
    void newline(GroupToken &toGtok);
    void next();

    /*! Processes a number symbol (#) Token.
     */
    void numSign();
    void numSign(GroupToken &toGtok);

    /*! Processes a symbol.
     */
    void otherSymbols();
    void otherSymbols(GroupToken &toGtok);

    /*! Processes a mapping where the key or value is within quotes.
        A mapping is defined as a key and value pair.
     */
    void quotedMapping();
    void quotedMapping(GroupToken &toGtok);

    /*! Processes a right brace Token.
     */
    void rightBrace();
    void rightBrace(GroupToken &toGtok);

    /*! Processes a right bracket Token.
     */
    void rightBracket();
    void rightBracket(GroupToken &toGtok);

    /*! Processes a scalar token.
        A scalar is defined as an alphanumeric identifier.
     */
    void scalar();
    void scalar(GroupToken &toGtok);

    /*! Processes a single quote Token.
     */
    void singleQuote();
    void singleQuote(GroupToken &toGtok);

    /*! Processes a single-quoted key Token.
        A single-quoted key is a key enclosed in single quotes.
     */
    void singleQuotedKey();
    void singleQuotedKey(GroupToken &toGtok);

    /*! Processes a single-quoted value Token.
        A single-quoted value is a value enclosed in single quotes.
     */
    void singleQuotedValue();
    void singleQuotedValue(GroupToken &toGtok);

    /*! Processes a space Token.
     */
    void space();
    void space(GroupToken &toGtok);
    // This is a symbol "multiplexer"
    void sym();
    void sym(GroupToken &toGtok);

    /*! Processes a tab Token.
     */
    void tab();
    void tab(GroupToken &toGtok);

    /*! Processes a value Token.
     */
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
