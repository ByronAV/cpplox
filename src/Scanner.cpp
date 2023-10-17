
#include "includes/Scanner.hpp"

Scanner::Scanner(const std::string& in_source) : source(in_source) {}

void Scanner::AddToken(const TokenType& type, void* literal)
{
    std::string text = source.substr(start, current - start); // TODO: Might need to fix the second parameter here
    tokens.push_back(std::make_unique<Token>(type, text, literal, line));
}

void Scanner::AddToken(const TokenType& type)
{
    AddToken(type, nullptr);
}

void Scanner::String()
{
    while(Peek() != '"' && !IsAtEnd())
    {
        if (Peek() == '\n') { line++; }
        Advance();
    }
    
    if (IsAtEnd()) {
        Error::SendError(line, "Unterminated string.");
        return;
    }

    // The closing "
    Advance();

    // Trim the surrounding quotes
    std::string value = source.substr(start + 1, current - start - 1); // TODO: Might need to fix the second parameter here
    AddToken(TokenType::STRING, std::move(&value)); // TODO: If value goes out of scope, do we have a dangling pointer or is the ownership transfered ?
}

void Scanner::Number()
{
    while(IsDigit(Peek())) { Advance(); }

    // Look for the fractional part
    if (Peek() == '.' && IsDigit(PeekNext()))
    {
        // First consume the .
        Advance();

        while (IsDigit(Peek())) { Advance(); }
    }
    auto number = std::stod(source.substr(start, current - start));
    AddToken(TokenType::NUMBER, std::move(&number));
}

void Scanner::Identifier()
{
    while (IsAlphaNumeric(Peek())) { Advance(); }

    std::string text = source.substr(start, current - start);
    auto it_type = std::find_if(keywords.begin(), keywords.end(),[&](const auto& entry){
        return entry.first == text;
    });
    if (it_type == keywords.end())
    { 
        TokenType type = TokenType::IDENTIFIER;
        AddToken(type);
        return;
    }

    AddToken((*it_type).second);
}

void Scanner::ScanToken()
{
    char c = Advance();

    switch(c) {
        case '(': AddToken(TokenType::LEFT_PAREN); break;
        case ')': AddToken(TokenType::RIGHT_PAREN); break;
        case '{': AddToken(TokenType::LEFT_BRACE); break;
        case '}': AddToken(TokenType::RIGHT_BRACE); break;
        case ',': AddToken(TokenType::COMMA); break;
        case '.': AddToken(TokenType::DOT); break;
        case '-': AddToken(TokenType::MINUS); break;
        case '+': AddToken(TokenType::PLUS); break;
        case ';': AddToken(TokenType::SEMICOLON); break;
        case '*': AddToken(TokenType::STAR); break;
        case '!':
            AddToken(Match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            AddToken(Match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            AddToken(Match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            AddToken(Match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        case '/':
            if (Match('/')) {
                // A comment goes untill the end of the line
                while (Peek() != '\n' && !IsAtEnd())
                    { Advance(); }
            } else {
                AddToken(TokenType::SLASH);
            }
            break;
        case ' ': [[fallthrough]];
        case '\r': [[fallthrough]];
        case '\t':
            // Ignore whitespace
            break;
        case '\n': line++; break;
        case '"': String(); break;
        default:
            if (IsDigit(c)) {
                Number();
            } else if (IsAlpha(c)) {
                Identifier();            
            } else {
                Error::SendError(line, "Unexpected character.");
            }
            break;
    }
}

std::vector<std::unique_ptr<Token>> const& Scanner::ScanTokens()
{
    while(!IsAtEnd())
    {
        start = current;
        ScanToken();
    }

    tokens.push_back(std::make_unique<Token>(TokenType::TEOF, "", nullptr, line));
    return tokens;
}

