/*   Created:  07-23-2025
 *   Modified: 10-08-2025
 */

#ifndef PONE_YAML_TOKENIZER_HPP
#define PONE_YAML_TOKENIZER_HPP

#include <fstream>
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "yaml_utils.hpp"

namespace YAML {

/*! Abstract base class for Tokens.
 */
class Token : public std::enable_shared_from_this<Token> {
   public:
    /*! An enum of all types of Tokens. */
    enum class Type {
        Backslash,    /*! The backslash character \ */
        Colon,        /*! The colon character : */
        Comma,        /*! The comma character , */
        Comment,      /*! A grouped type for YAML comments */
        Dash,         /*! The dash character -*/
        DoubleQuote,  /*! The double quote character " */
        Indent,       /*! Represents an indent specified. */
        Key,          /*! A grouped type for keys */
        LeftBrace,    /*! The left brace character { */
        LeftBracket,  /*! The left bracket character [ */
        Newline,      /*! The newline character \n */
        None,         /*! Placeholder token type */
        NumSign,      /*! The number sign character # */
        Quoted,       /*! A group type for quoted keys and values */
        RightBrace,   /*! The right brace character } */
        RightBracket, /*! The right bracket character ] */
        Root,         /*! The root groupToken. */
        Scalar,       /*! An alphanumeric identifier type */
        Sequence,     /*! A grouped type for sequences */
        SeqElement,   /*! A grouped type for sequence elements */
        SingleQuote,  /* The single quote character ' */
        Space,        /* The space character ' ' */
        Symbol,       /* A generic symbol character type */
        Tab,          /* The tab character \t */
        Value,        /* A grouped type for values */
    };

    /*! An enum of all derived Token classes */
    enum class Class {
        // This is a "type" to differentiate derived classes
        Group, /*! The GroupToken class */
        Single /*! The SingleToken class */
    };

    /*! The total size of the token types. */
    static const int ALL_TOKENS_SIZE = 24;

    /*! Map of Types to its string name. */
    std::unordered_map<Type, std::string> tokenNameMap = {
        {Type::Backslash, "Backslash"},
        {Type::Colon, "Colon"},
        {Type::Comma, "Comma"},
        {Type::Comment, "Comment"},
        {Type::Dash, "Dash"},
        {Type::DoubleQuote, "DoubleQuote"},
        {Type::Indent, "Indent"},
        {Type::Key, "Key"},
        {Type::LeftBrace, "LeftBrace"},
        {Type::LeftBracket, "LeftBracket"},
        {Type::Newline, "Newline"},
        {Type::None, "None"},
        {Type::NumSign, "NumSign"},
        {Type::Quoted, "Quoted"},
        {Type::RightBrace, "RightBrace"},
        {Type::RightBracket, "RightBracket"},
        {Type::Root, "Root"},
        {Type::Scalar, "Scalar"},
        {Type::Sequence, "Sequence"},
        {Type::SeqElement, "SequenceElement"},
        {Type::SingleQuote, "SingleQuote"},
        {Type::Symbol, "Symbol"},
        {Type::Tab, "Tab"},
        {Type::Value, "Value"}};

    /*! Default Token constructor.

        \note This constructor is deleted.
     */
    Token() = delete;

    /*! Token constructor.

        \param parent the parent Token.
        \param name the string name.
     */

    Token(const std::shared_ptr<Token> &parent, const std::string &name);

    /*! Token constructor.

        \param parent the parent Token.
        \param name the string name.
        \param cls the Token class.
     */
    Token(const std::shared_ptr<Token> &parent, const std::string &name,
          const Class &cls);

    /*! Token constructor.

        \param parent the parent Token.
        \param name the string name.
        \param type the Token type.
     */
    Token(const std::shared_ptr<Token> &parent, const std::string &name,
          const Type &type);

    /*! Token constructor.

        \param parent the parent Token.
        \param name the string name.
        \param class the Token class.
        \param type the Token type.
     */
    Token(const std::shared_ptr<Token> &parent, const std::string &name,
          const Class &cls, const Type &type);

    /*! Gets the class of a Token.

        \return an enum value of type Token::Class.
        \sa Token::Class
     */
    Class getClass() const;

    /*! Gets the depth of a Token.

         \return an int value.
      */
    int getDepth() const;

    /*! Gets the name of a Token.

        \return a read-only reference to the Token name.
     */
    const std::string &getName() const;

    /*! Gets the parent of a Token.

        \return a read-only reference to the parent Token pointer.
     */
    const std::shared_ptr<Token> &getParent() const;

    /*! Gets the type of a Token.

        \return an enum value of type Token::Type.
        \sa Token::Type
     */
    Type getType() const;

    /*! Prints out a Token entry.
        Helper function. Do not call directly.

        \param out the output stream.
        \param indent the indent for the next child Token.
        \param prefix the branch symbol before an entry.
     */
    void printEntry(std::ostream &out, std::vector<std::string> &indent,
                    const std::string &prefix) const;

    /*! Sets the depth of a Token.
        If parent is null, set to 0, otherwise depth(parent) + 1.
     */
    void setDepth();

    /*! Sets the name of a Token.

        \return the string name.
     */
    std::string setName() const;

    /*! Sets the type of a Token.
        \param type the type assigned to the Token.
        \sa Token::Type
     */
    void setType(const Type &type);

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

    /*! Pure virtual function for getting a pointer from the current Token.

        \return a pointer to the Token.
        \throws FailedAllocException
     */
    virtual std::shared_ptr<Token> getPtr() const = 0;

    /*! Pure virtual function for printing out every Token.

        \param out the output stream.
        \param indent the indent for the next child Token.
        \param prefix the branch symbol before a entry.
     */
    virtual void print(std::ostream &out, std::vector<std::string> &indent,
                       const std::string &prefix) const = 0;

    /*! Pure virtual function for setting the parent of a Token.

        \return parent the parent Token.
     */
    virtual void setParent(const std::shared_ptr<Token> &parent) = 0;
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

    // TODO: Check if this is viable
    // virtual void detach();

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

    /*! A virtual function. Releases a GroupToken's Tokens into the parent.
     */
    virtual void release();

    /*! A virtual function. The size of a GroupToken.

        \return a size_t value.
     */
    virtual size_t size() const;
    // ----------------------------------------
    // End of basic GroupToken functions

   protected:
    Class m_class;
    int m_depth = 0;  // root will always have depth = 0
    std::string m_name;
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

    /*! Gets a pointer from the current SingleToken.

        \return a pointer to the Token.
        \throws FailedAllocException
     */
    std::shared_ptr<Token> getPtr() const override;

    /*! Prints out every SingleToken.

        \param out the output stream.
        \param indent the indent for the next child Token.
        \param prefix the branch symbol before a entry.
     */
    void print(std::ostream &out, std::vector<std::string> &indent,
               const std::string &prefix = "") const override;

    /*! Sets the parent of a SingleToken.

        \param parent the parent Token.
     */
    void setParent(const std::shared_ptr<Token> &parent) override;

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

    /*! Releases a GroupToken's tokens into the parent.
     */
    void release() override;

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

    /*! Gets a pointer from the current SingleToken.

        \return a pointer to the Token.
        \throws FailedAllocException
     */
    std::shared_ptr<Token> getPtr() const override;

    /*! Prints out a GroupToken.

        \param out the output stream.
        \param indent the indent for the next child Token.
        \param prefix the branch symbol before a entry.
     */
    void print(std::ostream &out, std::vector<std::string> &indent,
               const std::string &prefix = "") const override;

    /*! Sets the parent of a GroupToken.

        \param parent the parent token.
     */
    void setParent(const std::shared_ptr<Token> &parent) override;

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

        \param fileName the string .YAML filename to load.
     */
    Tokenizer(const std::string &fileName);

    /*! Gets a deep copy of the vector of Tokens within the Tokenizer.

        \return a vector of Token pointers.
     */

    /*! Gets the size of the Tokenizer.

        \return a size_t value.
     */

    size_t size() const;

    /*! Gets a read-only reference to the tree of Tokens.

        \return a pointer to the token tree.
     */
    const std::shared_ptr<Token> &getTokens() const;

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

    /*! Processes an escape sequence.
     */
    void escape();

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

    /*! Processes literals in order of:
            - scalars
            - symbols
            - whitespace
     */
    void literal();

    /*! Peeks to the next character in the ifstream.

        \return a read-only character.
     */
    const char lookahead();

    /*! Processes a mapping Token.
        A mapping is defined as a key and value pair.
     */
    void mapping();

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

    /*! Prints out a tree of the Tokenizer.
     */
    void print(std::ostream &out) const;

    /*! Processes a quoted segment of Tokens.
     */
    void quoted();

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

    /*! Processes a sequence element Token.
     */
    void seqElement();

    /*! Processes a sequence Token.
     */
    void sequence();

    /*! Processes a single quote Token.
     */
    void singleQuote();

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

    /*! Friend function to print out the Tokenizer.
     */
    friend std::ostream &operator<<(std::ostream &out,
                                    const Tokenizer &tokenizer);

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
