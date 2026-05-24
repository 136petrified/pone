/* Created:  2026-05-23
 * Modified: 2026-05-23
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace pone::TOML {

/* Abstract base class for tokens.
 */

/* Token class. */
class Token : public std::enable_shared_from_this<Token> {
  public:
    enum class Type {
        ARRAY,
        ASSIGN,
        COMMA,
        COMMENT,
        DOUBLE_QUOTE,
        LEFT_BRACKET,
        LITERAL,
        MAPPING,
        NL,
        NUMSIGN,
        QUOTED,
        RIGHT_BRACKET,
        ROOT,
        SINGLE_QUOTE,
        TABLE,
        WS,
    };

    enum class Class { GROUP, SINGLE };

    // +--------------------------------+
    // + Token constructors             +
    // +--------------------------------+

    /* Default Token constructor.
     *
     * @note This constructor is deleted.
     */
    Token() = delete;

    /* Token constructor.
     *
     * @param parent the parent Token.
     * @param name the string name.
     */

    Token(const std::shared_ptr<Token> &parent, const std::string &name);

    /* Token constructor.
     *
     * @param parent the parent Token.
     * @param name the string name.
     * @param cls the Token class.
     */
    Token(const std::shared_ptr<Token> &parent, const std::string &name,
          const Class &cls);

    /* Token constructor.
     *
     * @param parent the parent Token.
     * @param name the string name.
     * @param type the Token type.
     */
    Token(const std::shared_ptr<Token> &parent, const std::string &name,
          const Type &type);

    /* Token constructor.
     *
     * @param parent the parent Token.
     * @param name the string name.
     * @param class the Token class.
     * @param type the Token type.
     */
    Token(const std::shared_ptr<Token> &parent, const std::string &name,
          const Class &cls, const Type &type);

    // +--------------------------------+
    // + Token functions                +
    // +--------------------------------+

    /* Gets the class of a Token.
     *
     * @return an enum value of type Token::Class.
     * @sa Token::Class
     */
    Class getClass() const;

    /* Gets the depth of a Token.
     *
     * @return an int value.
     */
    int getDepth() const;

    /* Gets the name of a Token.
     *
     * @return a read-only reference to the Token name.
     */
    const std::string &getName() const;

    /* Gets the parent of a Token.
     *
     * @return a read-only reference to the parent Token pointer.
     */
    const std::shared_ptr<Token> &getParent() const;

    /* Gets the type of a Token.
     *
     * @return an enum value of type Token::Type.
     * @sa Token::Type
     */
    Type getType() const;

    /* Prints out a Token entry.
     * @note Helper function. Do not call directly.
     *
     * @param out the output stream.
     * @param indent the indent for the next child Token.
     * @param prefix the branch symbol before an entry.
     */
    void printEntry(std::ostream &out, std::vector<std::string> &indent,
                    const std::string &prefix) const;

    /* Sets the depth of a Token.
     * If parent is null, set to 0, otherwise depth(parent) + 1.
     */
    void setDepth();

    /* Sets the name of a Token.
     *
     * @return the string name.
     */
    std::string setName() const;

    /* Sets the type of a Token.
     * @param type the type assigned to the Token.
     * @sa Token::Type
     */
    void setType(const Type &type);

    /* Pure virtual token destructor */
    virtual ~Token() = 0;

    // +--------------------------------+
    // + Token virtual functions        +
    // +--------------------------------+

    /* Pure virtual function for making a deep copy of a Token pointer.
     *
     * @param parent the parent Token.
     * @return a shared_ptr of the Token copy.
     */
    virtual std::shared_ptr<Token>
    clone(std::shared_ptr<Token> parent) const = 0;

    /* Pure virtual function for getting a pointer from the current Token.
     *
     * @return a pointer to the Token.
     * @throws FailedAllocException
     */
    virtual std::shared_ptr<Token> getPtr() const = 0;

    /* Pure virtual function for printing out every Token.
     *
     * @param out the output stream.
     * @param indent the indent for the next child Token.
     * @param prefix the branch symbol before a entry.
     */
    virtual void print(std::ostream &out, std::vector<std::string> &indent,
                       const std::string &prefix) const = 0;

    /* Pure virtual function for setting the parent of a Token.
     *
     * @return parent the parent Token.
     */
    virtual void setParent(const std::shared_ptr<Token> &parent) = 0;

    // +--------------------------------+
    // + SingleToken virtual functions  +
    // +--------------------------------+

    /* A virtual function to the string data from a SingleToken.
     *
     * @return a read-only string reference of the data.
     */
    virtual const std::string &getData() const;

    /* A virtual function to set the string data of a SingleToken.
     *
     * @param data a string representing SingleToken data.
     */
    virtual void setData(const std::string &data);
    // End of basic SingleToken functions

    // +--------------------------------+
    // + GroupToken virtual functions   +
    // +--------------------------------+

    /* A virtual function for erasing all of the Tokens within a GroupToken.
     */
    virtual void clear();

    // TODO: Check if this is viable
    // virtual void detach();

    /* A virtual function to copy the root vector of Tokens.
     */
    virtual std::vector<std::shared_ptr<Token>> copy() const;

    /* A virtual function for getting a vector of a Tokens within a
     * GroupToken.
     *
     * @return a read-only vector reference of Token pointers.
     */
    virtual const std::vector<std::shared_ptr<Token>> &getTokens() const;

    /* A virtual function for inserting a Token to a GroupToken.
     *
     * @param token an rvalue reference to a Token pointer.
     */
    virtual void insert(std::shared_ptr<Token> token);

    /* A virtual function. Checks if a GroupToken is empty.
     *
     * @return true if empty, false otherwise.
     */
    virtual bool empty() const;

    /* A virtual function. Releases a GroupToken's Tokens into the parent.
     */
    virtual void release();

    /* A virtual function. The size of a GroupToken.
     *
     * @return a size_t value.
     */
    virtual size_t size() const;

  protected:
    Class m_class;
    int m_depth = 0; // root will always have depth = 0
    std::string m_name;
    std::shared_ptr<Token> m_parent;
    Type m_type;
};

/* Token class for single-storage Tokens
 *
 * @sa Token
 */
class SingleToken : public Token {
    // +--------------------------------+
    // + SingleToken data members       +
    // +--------------------------------+

    std::string m_data;

  public:
    // +--------------------------------+
    // + SingleToken constructors       +
    // +--------------------------------+

    /* Default SingleToken constructor.
     *
     * @note This constructor is deleted.
     * @sa Token
     */
    SingleToken() = delete;

    /* SingleToken constructor.
     *
     * @param parent the parent Token.
     * @param type the assigned type of SingleToken.
     * @sa Token
     */
    SingleToken(const std::shared_ptr<Token> &parent, const Token::Type &type);

    /* SingleToken constructor.
     *
     * @param parent the parent Token.
     * @param type the assigned type of SingleToken.
     * @param data a read-only string reference of the Token's data.
     * @sa Token
     */
    SingleToken(const std::shared_ptr<Token> &parent, const Token::Type &type,
                const std::string &data);

    /* SingleToken constructor.
     *
     * @param parent the parent Token.
     * @param type the assigned type of SingleToken.
     * @param data a string rvalue reference of the Token's data.
     * @sa Token
     */
    SingleToken(const std::shared_ptr<Token> &parent, const Token::Type &type,
                std::string &&data);

    /* SingleToken copy constructor.
     *
     * @param other the SingleToken to copy from.
     * @sa Token
     */
    SingleToken(const SingleToken &other);

    /* SingleToken copy assignment.
     *
     * @param other the SingleToken to copy from.
     * @sa Token
     */
    SingleToken &operator=(const SingleToken &other);

    // +--------------------------------+
    // + SingleToken functions          +
    // +--------------------------------+

    /* Gets string data from a SingleToken.
     *
     * @return a read-only string reference SingleToken data.
     * @sa Token
     */
    const std::string &getData() const override;

    /* Sets string data for a SingleToken.
     *
     * @param data a string representing SingleToken data.
     * @sa Token
     */
    void setData(const std::string &data) override;

    /* SingleToken destructor.
     */
    ~SingleToken();

    // +----------------------------------+
    // + Overriden functions from Token   +
    // +----------------------------------+

    /* Creates a deep copy of a SingleToken pointer.
     *
     * @param parent the parent Token.
     * @returns a shared_ptr of the Token copy.
     * @sa Token
     */
    std::shared_ptr<Token> clone(std::shared_ptr<Token> parent) const override;

    /* Gets a pointer from the current SingleToken.
     *
     * @return a pointer to the Token.
     * @throws FailedAllocException
     */
    std::shared_ptr<Token> getPtr() const override;

    /** Prints out every SingleToken.
     *
     * @param out the output stream.
     * @param indent the indent for the next child Token.
     * @param prefix the branch symbol before a entry.
     */
    void print(std::ostream &out, std::vector<std::string> &indent,
               const std::string &prefix = "") const override;

    /* Sets the parent of a SingleToken.
     *
     * @param parent the parent Token.
     */
    void setParent(const std::shared_ptr<Token> &parent) override;
};

/*  func(Token &) means that you
 *  should pass the reference before making it read access
 *  only
 */

/* Token class for Tokens that contain nested Tokens.
 *
 * @sa Token
 */
class GroupToken : public Token {
    // +--------------------------------+
    // + GroupToken data members        +
    // +--------------------------------+

    // NOTE: This allows for a Token to be made up of Tokens
    std::vector<std::shared_ptr<Token>> m_tokens;
    size_t m_size;

  public:
    // +--------------------------------+
    // + GroupToken constructors        +
    // +--------------------------------+

    /* Default GroupToken constructor.
     *
     * @note This constructor is deleted.
     * @sa Token
     */
    GroupToken() = delete;

    /* GroupToken constructor.
     *
     * @param parent the parent Token.
     * @param type the assigned type of GroupToken.
     * @sa Token
     */
    GroupToken(const std::shared_ptr<Token> &parent, const Token::Type &type);

    /* GroupToken copy constructor.
     *
     * @param other the GroupToken to copy from.
     * @sa Token
     */
    GroupToken(const GroupToken &other);

    /* GroupToken move constructor.
     *
     * @param other an rvalue reference to the GroupToken to move from.
     * @sa Token
     */
    GroupToken(GroupToken &&other) noexcept;

    /* GroupToken copy assignment.
     *
     * @param other the GroupToken to copy from.
     * @sa Token
     */
    GroupToken &operator=(const GroupToken &other);

    /* GroupToken move assignment.
     *
     * @param other an rvalue reference to the GroupToken to move from.
     * @sa Token
     */
    GroupToken &operator=(GroupToken &&other) noexcept;

    // +--------------------------------+
    // + GroupToken functions           +
    // +--------------------------------+

    /* Clears all the elements from a GroupToken.
     *
     * @sa Token
     */
    void clear() override;

    /* Makes a copy of the root vector of Tokens
     *
     * @return a vector of Token pointers.
     */
    std::vector<std::shared_ptr<Token>> copy() const override;

    /*! Gets the vector of Tokens within a GroupToken.
     *
     * @return a read-only vector reference of Token pointers.
     * @sa Token
     */
    const std::vector<std::shared_ptr<Token>> &getTokens() const override;

    // NOTE: Cannot use std::shared_ptr<Token> & due to clone()
    //       requirement of rvalue argument

    /* Inserts a Token into a GroupToken.
     *
     * @param token a Token pointer.
     * @sa Token
     */
    void insert(std::shared_ptr<Token> token) override;

    /* Checks if a GroupToken is empty.
     *
     * @return true if empty, false otherwise.
     * @sa Token
     */
    bool empty() const override;

    /* Releases a GroupToken's tokens into the parent.
     */
    void release() override;

    /* Gets the size of a GroupToken.
     *
     * @return a size_t value.
     * @sa Token
     */
    size_t size() const override;

    /* GroupToken destructor.
     */
    ~GroupToken();

    // +----------------------------------+
    // + Overriden functions from Token   +
    // +----------------------------------+

    /* Creates a deep copy of a GroupToken pointer.
     *
     * @param parent the parent Token.
     * @return a shared_ptr to the GroupToken copy.
     * @sa Token
     */
    std::shared_ptr<Token> clone(std::shared_ptr<Token> parent) const override;

    /* Gets a pointer from the current SingleToken.
     *
     * @return a pointer to the Token.
     * @throws FailedAllocException
     */
    std::shared_ptr<Token> getPtr() const override;

    /* Prints out a GroupToken.
     *
     * @param out the output stream.
     * @param indent the indent for the next child Token.
     * @param prefix the branch symbol before a entry.
     */
    void print(std::ostream &out, std::vector<std::string> &indent,
               const std::string &prefix = "") const override;

    /* Sets the parent of a GroupToken.
     *
     * @param parent the parent token.
     */
    void setParent(const std::shared_ptr<Token> &parent) override;
};

} // namespace pone::TOML
