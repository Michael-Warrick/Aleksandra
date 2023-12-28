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
    int index = 0;  // Counter for the position in the vector
    for (const auto &token : tokens)
    {
        std::string typeString = tokenTypeToString(token.type);
        std::cout << "Token[" << index << "]:\n" << "\tType: " << typeString << "\n" << "\tText: \"" << token.text << "\"" << std::endl;
        
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
    case Token::Type::Punctuation:
        return "Punctuation";
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
    return std::isdigit(character) >= 0 && std::isdigit(character) <= 9;
}

bool Lexer::isAlphaNumeric(char character)
{
    return (character >= 'a' && character <= 'z') ||
           (character >= 'A' && character <= 'Z') ||
           (character >= '0' && character <= '9') ||
           character == '_';
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

    auto ungetCharacter = [&]() 
    {
        if (position > 0)
        {
            --position;
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

    while (currentCharacter != EOF)
    {
        currentCharacter = getNextCharacter();

        while (isWhiteSpace(currentCharacter))
        {
            currentCharacter = getNextCharacter();
        }

        if (isAlphaNumeric(currentCharacter))
        {
            std::string tokenString;

            while (isAlphaNumeric(currentCharacter))
            {
                tokenString += currentCharacter;
                currentCharacter = getNextCharacter();
            }

            if (currentCharacter == ';')
            {
                ungetCharacter();
            }

            // Default to Identifier
            Token::Type tokenType = Token::Type::Identifier;

            // Check if is a Keyword before submitting Token to the list
            for (int i = 0; i < static_cast<size_t>(Token::Keyword::KEYWORD_COUNT); ++i)
            {
                if (tokenString == Token::keywords[i])
                {
                    tokenType = Token::Type::Keyword;
                    break; // Found a match!
                }
            }

            tokens.push_back(Token(tokenType, tokenString));
        }
        else if (currentCharacter == ';')
        {
            tokens.push_back(Token(Token::Type::Punctuation, std::string(1, currentCharacter)));
            currentCharacter = getNextCharacter();
        }
    }
}