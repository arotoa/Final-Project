#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COLON,
    COLON_DASH,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    END,
    UNDEFINED

};

class Token
{
private:
    TokenType tokenType;
    std::string info;
    int lineNum;

public:
    Token(TokenType type, std::string description, int line);

    std::string getTypeInString();
    std::string toString();
    TokenType getType();
    std::string getInfo();

};

#endif
