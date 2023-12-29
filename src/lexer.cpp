#include "lexer.hpp"

Token::Token(Type type, std::string text)
{
    Token::type = type;
    Token::text = text;
}

Lexer::Lexer(const std::string &source)
{
    sourceCode = source;
    tokenize();
}

const std::vector<Token> &Lexer::GetTokens()
{
    return tokens;
}

void Lexer::PrintTokens() const
{
    int index = 0; // Counter for the position in the vector
    for (const auto &token : tokens)
    {
        std::string typeString = tokenTypeToString(token.type);
        std::cout << "Token[" << index << "]:\n"
                  << "\tType: " << typeString << "\n"
                  << "\tText: \"" << token.text << "\"" << std::endl;

        ++index;
    }
}

std::string Lexer::tokenTypeToString(Token::Type type) const
{
    switch (type)
    {
    case Token::Type::Identifier:
        return "Identifier";
    case Token::Type::Keyword:
        return "Keyword";
    case Token::Type::Number:
        return "Number";
    case Token::Type::Literal:
        return "Literal";
    case Token::Type::Punctuation:
        return "Punctuation";
    case Token::Type::Operator:
        return "Operator";
    default:
        return "Unknown";
    }
}

bool Lexer::isWhiteSpace(char character)
{
    return character == ' ' || character == '\t' || character == '\n' || character == '\r';
}

bool Lexer::isDigit(char character)
{
    return character >= '0' && character <= '9';
}

bool Lexer::isAlphaNumeric(char character)
{
    return (character >= 'a' && character <= 'z') ||
           (character >= 'A' && character <= 'Z') ||
           (character >= '0' && character <= '9') ||
           character == '_';
}

bool Lexer::isPunctuation(char character)
{
    return character == ';';
}

bool Lexer::isBrace(char character)
{
    return character == '{' || character == '}' || character == '(' || character == ')';
}

void Lexer::tokenize()
{
    size_t position = 0;
    char currentCharacter = ' ';

    auto getNextCharacter = [&]() -> char
    {
        if (position < sourceCode.length())
        {
            return sourceCode[position++];
        }
        else
        {
            return EOF;
        }
    };

    auto peekNextCharacter = [&]() -> char
    {
        if (position < sourceCode.length())
        {
            return sourceCode[position];
        }
        else
        {
            return EOF;
        }
    };

    currentCharacter = getNextCharacter(); // Initialize the first character

    while (currentCharacter != EOF)
    {
        if (isWhiteSpace(currentCharacter))
        {
            // Skip whitespace
            currentCharacter = getNextCharacter();
            continue;
        }

        // Numbers
        if (isDigit(currentCharacter))
        {
            std::string number;

            do
            {
                number += currentCharacter;
                currentCharacter = getNextCharacter();
            } while (isDigit(currentCharacter));

            tokens.push_back(Token(Token::Type::Number, number));

            // If the current character after number is a punctuation or brace, tokenize it.
            if (isPunctuation(currentCharacter) || isBrace(currentCharacter))
            {
                tokens.push_back(Token(Token::Type::Punctuation, std::string(1, currentCharacter)));
                currentCharacter = getNextCharacter();
                continue;
            }
        }

        if (isAlphaNumeric(currentCharacter))
        {
            // Handle alphanumeric (identifiers and keywords)
            std::string tokenString;
            do
            {
                tokenString += currentCharacter;
                currentCharacter = getNextCharacter();
            } while (isAlphaNumeric(currentCharacter));

            Token::Type tokenType = Token::Type::Identifier;
            // Check for keywords
            for (int i = 0; i < static_cast<size_t>(Token::Keyword::KEYWORD_COUNT); ++i)
            {
                if (tokenString == Token::keywords[i])
                {
                    tokenType = Token::Type::Keyword;
                    break; // Found a keyword
                }
            }

            tokens.push_back(Token(tokenType, tokenString));

            // Don't immediately fetch the next character if it's punctuation or brace
            if (isPunctuation(currentCharacter) || isBrace(currentCharacter))
            {
                continue;
            }
        }

        // Strings
        if (currentCharacter == '"')
        {
            std::string literal;

            currentCharacter = getNextCharacter();
            while (currentCharacter != '"' && currentCharacter != EOF)
            {
                literal += currentCharacter;
                currentCharacter = getNextCharacter();
            }

            tokens.push_back(Token(Token::Type::Literal, literal));
            currentCharacter = getNextCharacter();
            continue;
        }

        // Arrow Operator
        if (currentCharacter == '-' && peekNextCharacter() == '>')
        {
            tokens.push_back(Token(Token::Type::Operator, "->"));
            getNextCharacter(); // Consume '>'
            currentCharacter = getNextCharacter();
            continue;
        }

        // Namespace Operator
        if (currentCharacter == ':' && peekNextCharacter() == ':')
        {
            tokens.push_back(Token(Token::Type::Operator, "::"));
            getNextCharacter(); // Consume the second ':'
            currentCharacter = getNextCharacter();
            continue;
        }

        // Punctuation
        if (isPunctuation(currentCharacter) || isBrace(currentCharacter))
        {
            // Handle punctuation and braces
            tokens.push_back(Token(Token::Type::Punctuation, std::string(1, currentCharacter)));
            currentCharacter = getNextCharacter();
        }
        else
        {
            currentCharacter = getNextCharacter();
        }
    }
}