/*   Created:  07-23-2025
 *   Modified: 09-26-2025
 */

#ifndef PONE_YAML_TOKENIZER_HPP
#define PONE_YAML_TOKENIZER_HPP

// #include <array>
#include <fstream>
#include <memory>
#include <stack>
#include <string>
#include <vector>

#include "yaml_utils.hpp"

namespace YAML {

/*! Abstract base class for Tokens.
 */
class Token : public std::enable_shared_from_this<Token> {
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
        Indent,            /*! Represents an indent specified. */
        Key,               /*! A grouped type for keys */
        LeftBrace,         /*! The left brace character { */
        LeftBracket,       /*! The left bracket character [ */
        Newline,           /*! The newline character \n */
        None,              /*! Placeholder token type */
        NumSign,           /*! The number sign character # */
        RightBrace,        /*! The right brace character } */
        RightBracket,      /*! The right bracket character ] */
        Root,              /*! The root groupToken. */
        Scalar,            /*! An alphanumeric identifier type */
        Sequence,          /*! A grouped type for sequences */
        SeqElement,        /*! A grouped type for sequence elements */
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
    static const int ALL_TOKENS_SIZE = 28;

    /*! Default Token constructor.

        \note This constructor is deleted.
     */
    Token() = delete;

    /*! Token constructor.

        \param parent the parent Token.
     */

    Token(const std::shared_ptr<Token> &parent);

    /*! Token constructor.

        \param parent the parent Token.
        \param cls the Token class.
     */
    Token(const std::shared_ptr<Token> &parent, const Class &cls);

    /*! Token constructor.

        \param parent the parent Token.
        \param type the Token type.
     */
    Token(const std::shared_ptr<Token> &parent, const Type &type);

    /*! Token constructor.

        \param parent the parent Token.
        \param class the Token class.
        \param type the Token type.
     */
    Token(const std::shared_ptr<Token> &parent, const Class &cls,
          const Type &type);

    /*! Pure virtual token destructor */
    virtual ~Token() = 0;

    // Start of basic Token functions
    // ----------------------------------------
    /*! Pure virtual function for making a deep copy of a Token pointer.

        \param parent the parent Token.
        \return a shared_ptr of the Token copy.
     */
    virtual std::shared_ptr<Token> clone(
        std::shared_ptr<Token> parent) const = 0;

    /*! Pure virtual function for getting the class of a Token.

        \return an enum value of type Token::Class.
        \sa Token::Class
     */
    virtual Class getClass() const = 0;

    /*! Pure virtual function for getting the depth of a Token.

        \return an int value.
     */
    virtual int getDepth() const = 0;

    /*! Pure virtual function for getting the parent of a Token.

        \return a read-only reference to the parent Token pointer.
     */
    virtual const std::shared_ptr<Token> &getParent() const = 0;

    /*! Pure virtual function that gets a pointer from the current Token.

        \return a pointer to the Token.
     */
    virtual std::shared_ptr<Token> getPtr() const = 0;

    /*! Pure virtual function for getting the type of a Token.

        \return an enum value of type Token::Type.
        \sa Token::Type
     */

    virtual Type getType() const = 0;

    /*! Pure virtual function for setting the depth of a Token.
        If parent is null, set to 0, otherwise depth(parent) + 1.
     */
    virtual void setDepth() = 0;

    /*! Pure virtual function for setting the parent of a Token.

        \return parent the parent Token.
     */
    virtual void setParent(const std::shared_ptr<Token> &parent) = 0;

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
    virtual void clear();

    /*! A virtual function to copy the root vector of Tokens.
     */
    virtual std::vector<std::shared_ptr<Token>> copy() const;

    /*! A virtual function for getting a vector of a Tokens within a GroupToken.

       \return a read-only vector reference of Token pointers.
     */
    virtual const std::vector<std::shared_ptr<Token>> &getTokens() const;

    /*! A virtual function for inserting a Token to a GroupToken.

        \param token an rvalue reference to a Token pointer.
     */
    virtual void insert(std::shared_ptr<Token> token);

    /*! A virtual function. Checks if a GroupToken is empty.
        \return true if empty, false otherwise.
     */
    virtual bool empty() const;

    /*! A virtual function. The size of a GroupToken.

        \return a size_t value.
     */
    virtual size_t size() const;
    // ----------------------------------------
    // End of basic GroupToken functions

   protected:
    Class m_class;
    int m_depth;  // root will always have depth = 0
    std::shared_ptr<Token> m_parent;
    Type m_type;
};

/*! Token class for single-storage Tokens

    \sa Token
 */
class SingleToken : public Token {
   public:
    /*! Default SingleToken constructor.

        \note This constructor is deleted.
        \sa Token
     */
    SingleToken() = delete;

    /*! SingleToken constructor.

        \param parent the parent Token.
        \param type the assigned type of SingleToken.
        \sa Token
     */
    SingleToken(const std::shared_ptr<Token> &parent, const Token::Type &type);

    /*! SingleToken constructor.

        \param parent the parent Token.
        \param type the assigned type of SingleToken.
        \param data a read-only string reference of the Token's data.
        \sa Token
     */
    SingleToken(const std::shared_ptr<Token> &parent, const Token::Type &type,
                const std::string &data);

    /*! SingleToken constructor.

        \param parent the parent Token.
        \param type the assigned type of SingleToken.
        \param data a string rvalue reference of the Token's data.
        \sa Token
     */
    SingleToken(const std::shared_ptr<Token> &parent, const Token::Type &type,
                std::string &&data);

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
    /*! Creates a deep copy of a SingleToken pointer.

        \param parent the parent Token.
        \returns a shared_ptr of the Token copy.
        \sa Token
     */
    std::shared_ptr<Token> clone(std::shared_ptr<Token> parent) const override;

    /*! Gets the class of a SingleToken.

        \return an enum value of type Type::Class.
        \sa Token, Token::Class
     */
    Token::Class getClass() const override;

    /*! Gets the depth of a SingleToken.

        \return an int value.
     */
    int getDepth() const override;

    /*! Gets the parent of a SingleToken.

        \return the parent of the SingleToken.
     */
    const std::shared_ptr<Token> &getParent() const override;

    /*! Gets a pointer from the current SingleToken.

        \return a pointer to the Token.
     */
    std::shared_ptr<Token> getPtr() const override;

    /*! Gets the type of a SingleToken.

        \return an enum value of type Token::Type.
        \sa Token, Token::Type
     */
    Token::Type getType() const override;

    /*! Sets the depth of a SingleToken.
        If parent is null, set to 0, otherwise depth(parent) + 1.
     */
    void setDepth() override;

    /*! Sets the parent of a SingleToken.

        \param parent the parent Token.
     */
    void setParent(const std::shared_ptr<Token> &parent) override;

    /*! Sets the type of a SingleToken.

        \param type the type assigned to the SingleToken.
        \sa Token, Token::Type
     */
    void setType(const Token::Type &type) override;

   private:
    std::string m_data;
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

        \note This constructor is deleted.
        \sa Token
     */
    GroupToken() = delete;

    /*! GroupToken constructor.

        \param parent the parent Token.
        \param type the assigned type of GroupToken.
        \sa Token
     */
    GroupToken(const std::shared_ptr<Token> &parent, const Token::Type &type);

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
    void clear() override;

    /*! Makes a copy of the root vector of Tokens

        \return a vector of Token pointers.
     */
    std::vector<std::shared_ptr<Token>> copy() const override;

    /*! Gets the vector of Tokens within a GroupToken.

        \return a read-only vector reference of Token pointers.
        \sa Token
     */

    const std::vector<std::shared_ptr<Token>> &getTokens() const override;

    // NOTE: Cannot use std::shared_ptr<Token> & due to clone()
    //       requirement of rvalue argument

    /*! Inserts a Token into a GroupToken.

        \param token a Token pointer.
        \sa Token
     */
    void insert(std::shared_ptr<Token> token) override;

    /*! Checks if a GroupToken is empty.

        \return true if empty, false otherwise.
        \sa Token
     */

    bool empty() const override;

    /*! Gets the size of a GroupToken.

        \return a size_t value.
        \sa Token
     */
    size_t size() const override;

    /*! GroupToken destructor.
     */
    ~GroupToken();

    // Pure virtual functions from Token

    /*! Creates a deep copy of a GroupToken pointer.

        \param parent the parent Token.
        \return a shared_ptr to the GroupToken copy.
        \sa Token
     */
    std::shared_ptr<Token> clone(std::shared_ptr<Token> parent) const override;

    /*! Gets the class of a GroupToken.

        \return an enum value of type Token::Class.
        \sa Token::Class, Token
     */
    Token::Class getClass() const override;

    /*! Gets the depth of a GroupToken.

        \return an int value.
     */
    int getDepth() const override;

    /*! Gets the parent of a GroupToken.

        \return a read-only reference of a Token pointer.
     */
    const std::shared_ptr<Token> &getParent() const override;

    /*! Gets a pointer from the current GroupToken.

        \return a pointer to the Token.
     */
    std::shared_ptr<Token> getPtr() const override;

    /*! Gets the type of a GroupToken.

        \return an enum value of type Token::Type.
        \sa Token::Type, Token
     */
    Token::Type getType() const override;

    /*! Sets the depth of a GroupToken.
        If parent is null, set to 0, otherwise depth(parent) + 1.
     */
    void setDepth() override;

    /*! Sets the parent of a GroupToken.

        \param parent the parent token.
     */
    void setParent(const std::shared_ptr<Token> &parent) override;

    /*! Sets the type of a GroupToken.

        \param type the type assigned to a GroupToken.
        \sa Token::Type, Token
     */
    void setType(const Token::Type &type) override;

   private:
    std::vector<std::shared_ptr<Token>> m_tokens;
    size_t m_size;
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

    /*! Gets the size of the Tokenizer.

        \return a size_t value.
     */

    size_t size() const;

    const std::vector<std::shared_ptr<Token>> &getTokens() const;

    /*! Initializes the Tokenizer.
        This function is the entry point of the Tokenizer.
     */

    void tokenize();

    /*! Tokenizer destructor. */
    ~Tokenizer();

    // FIXME: Enable the protected access specifier
    //        after testing! v v v

    // protected:
    /*! Processes a backslash Token.
     */
    void backslash();

    /*! Clears the current character buffer in the Tokenizer.
     */
    void clearBuf();

    /*! Processes a colon Token.
     */
    void colon();

    /*! Processes a comma Token.
     */
    void comma();

    /*! Processes a comment Token.
     */
    void comment();

    /*! Creates a shared GroupToken pointer.

        \param type the Token type to create the GroupToken with.
        \return a shared pointer to the GroupToken.
     */
    std::shared_ptr<GroupToken> createGroupToken(const Token::Type &type) const;

    /*! Creates a shared GroupToken pointer from an existing GroupToken.

        \param gtok the GroupToken object to tokenize.
        \return a shared pointer to the GroupToken.
     */
    std::shared_ptr<GroupToken> createGroupToken(GroupToken &gtok);

    /*! Creates a shared SingleToken pointer.

        \param type the Token type to create the SingleToken with.
        \return a shared pointer to the SingleToken.
     */
    std::shared_ptr<SingleToken> createSingleToken(
        const Token::Type &type) const;

    /*! Creates a shared SingleToken pointer with string data.

       \param type the Token type to create the SingleToken with.
       \param data a string rvalue reference.
       \return a shared pointer to the SingleToken.
     */
    std::shared_ptr<SingleToken> createSingleToken(const Token::Type &type,
                                                   std::string &&data) const;

    /*! Creates a shared SingleToken pointer from an existing SingleToken.

        \param stok the SingleToken object to tokenize.
        \return a shared pointer to the SingleToken.
     */
    std::shared_ptr<SingleToken> createSingleToken(SingleToken &stok);

    /*! Processes a dash Token.
     */
    void dash();

    /*! Processes a double quote Token.
     */
    void doubleQuote();
    /*! Processes a double-quoted value Token.
        A double-quoted value is a value enclosed in quotes.
     */
    void doubleQuotedValue();

    /*! Processes an indent Token.
        This is a group Token.
     */
    void indent();

    /*! Inserts a GroupToken to a parent GroupToken.

        \param type the Token type.
     */
    void insertGroupToken(const Token::Type &type);

    /*! Inserts a GroupToken to a parent GroupToken.

        \param gtokPtr a pointer to the GroupToken.
     */
    void insertGroupToken(const std::shared_ptr<GroupToken> &gtokPtr);

    /*! Moves and inserts a GroupToken to a parent GroupToken.

        \param gtokPtr a pointer rvalue reference to a GroupToken.
     */

    void insertSingleToken(const Token::Type &type);

    /*! Creates and inserts a SingleToken to a parent GroupToken with
       string data.

        \param type the Token type.
        \param data a string rvalue reference.
     */
    void insertSingleToken(const Token::Type &type, std::string &&data);

    /*! Inserts a SingleToken to a parent GroupToken.

        \param stokPtr a pointer to the SingleToken.
     */
    void insertSingleToken(const std::shared_ptr<SingleToken> &stokPtr);

    /*! Processes a key Token.
     */
    void key();

    /*! Processes a left brace Token.
     */
    void leftBrace();

    /*! Processes a left bracket Token.
     */
    void leftBracket();

    /*! Peeks to the next character in the ifstream.

        \return a read-only character.
     */
    const char lookahead();

    /*! Processes a mapping Token.
        A mapping is defined as a key and value pair.
     */
    void mapping();  // TODO: Group mapping

    /*! Processes a newline Token.
     */
    void newline();

    /*! Advances the next character in the ifstream.

        \throws EndOfIstreamException if the filestream throws EOF.
     */
    void next();

    /*! Processes a number symbol (#) Token.
     */
    void numSign();

    /*! Processes a symbol Token.
     */
    void otherSymbols();

    /*! Processes a mapping where the key or value is within quotes.
        A mapping is defined as a key and value pair.
     */
    void quotedMapping();

    /*! Processes a right brace Token.
     */
    void rightBrace();

    /*! Processes a right bracket Token.
     */
    void rightBracket();

    /*! Processes a scalar token.
        A scalar is defined as an alphanumeric identifier.
     */
    void scalar();

    /*! Processes a sequence Token.
     */
    void sequence();

    /*! Processes a sequence element Token.
     */
    void seqElement();

    /*! Processes a single quote Token.
     */
    void singleQuote();

    /*! Processes a single-quoted key Token.
        A single-quoted key is a key enclosed in single quotes.
     */
    void singleQuotedKey();

    /*! Processes a single-quoted value Token.
        A single-quoted value is a value enclosed in single quotes.
     */
    void singleQuotedValue();

    /*! Processes a space Token.
     */
    void space();

    // This is a symbol "multiplexer"

    /*! Pipelines a symbol to its respective tokenizing function.
     */
    void sym();

    /*! Processes a tab Token.
     */
    void tab();

    /*! Processes a value Token.
     */
    void value();

    // This is a whitespace "multiplexer"

    /*! Pipelines a whitespace character to a tokenizing function.
     */
    void whitespace();

   private:
    std::string m_fileName;
    std::ifstream m_ifs;

    int m_indent;  // Defined by YAML config
    int m_depth;   // Current depth of tokenizer
                   // not depth of a token.

    /*! A stack of GroupToken pointers. */
    std::stack<std::shared_ptr<Token>> groupStack;
    size_t m_size;

    std::string m_buf;
    char m_char;

    bool m_endOfFile;
};
}  // namespace YAML

#endif  // PONE_YAML_TOKENIZER_HPP
