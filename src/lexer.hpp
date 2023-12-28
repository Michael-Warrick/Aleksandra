#pragma once
#include <iostream>

struct Token
{
    enum class Type
    {
        None,
        Keyword,
        Identifier,
        Number,
        Literal,
        Operator,
        Punctuation
    };

    enum class Number
    {
        None,
        Int32,
        Int64,
        Float32,
        Float64,
        Boolean
    };

    enum class Operator
    {
        NoneOperator,
        Add,
        Subtract,
        Multiply,
        Divide,
        Modulo,
        Assignment,
        Equality,
        NonEquality,
        Increment,
        Decrement,
        Negate,
        LessThan,
        LessThanOrEqual,
        GreaterThan,
        GreaterThanOrEqual,
        And,
        Or,
        LogicalAnd,
        LogicalOr,
        LogicalExclusiveOr,
        LogicalNot,
        OPERATOR_COUNT
    };

    enum class Keyword 
    {
        None,
        Import,
        Define,
        Function,
        If,
        Else,
        While,
        Integer,
        Integer32,
        Integer64,
        Float,
        Float32,
        Float64,
        Boolean,
        Void,
        Return,
        True,
        False,
        KEYWORD_COUNT
    };

    constexpr static const char *opperators[static_cast<size_t>(Operator::OPERATOR_COUNT)] = {
        "", "+", "-", "*", "/", "%", "=", "==", "!=", "++", "--", "!", "<", "<=", ">", ">=", "&&", "||", "&", "|", "^", "~"
    };

    constexpr static const char *keywords[static_cast<size_t>(Keyword::KEYWORD_COUNT)] = {
        "",
        "Import",
        "Define",
        "Function",
        "If",
        "Else",
        "While",
        "Integer",
        "Integer32",
        "Integer64",
        "Float",
        "Float32",
        "Float64",
        "Boolean",
        "Void",
        "Return",
        "True",
        "False"
    };

    Type type;
    std::string text;

    Token(Type type, std::string text);
};

class Lexer
{
public:
    Lexer(const std::string &source);

    const std::vector<Token> &GetTokens();
    void PrintTokens() const;

private:
    void tokenize();
    std::string tokenTypeToString(Token::Type type) const;

    bool isWhiteSpace(char character);
    bool isDigit(char character);
    bool isAlphaNumeric(char character);

    std::string sourceCode;
    std::vector<Token> tokens;
};