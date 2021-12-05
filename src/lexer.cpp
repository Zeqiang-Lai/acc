#include <cstdlib>

#include "lexer.h"
#include "token.h"

void Lexer::skip_whitespace() {
    while (match(' ') || match('\t') || match('\r') || match('\n'));
}

void Lexer::skip_comment() {
    if (match('/')) {
        if (match('/')) {
            while (next() != '\n');
        } else if (match('*')) {
            while (true) {
                char ch = next();
                if (ch == '*' && peek() == '/') break;
            }
        } else {
            back();
        }
    }
}

Token Lexer::character() {
    char ch = next();
    if (ch == '\\') {
        switch (next()) {
            case 'n':
                ch = '\n';
                break;
            case 't':
                ch = '\t';
                break;
            case '\\':
                ch = '\\';
                break;
            default:
                cerr << "invalid escaped character" << endl;
                break;
        }
        expect('\'');
    } else {
        expect('\'');
    }
    return Token(TokenType::CHAR_CONST, ch);
}

Token Lexer::identifier() {
    vector<char> chs;
    char ch = previous();
    while (isalpha(ch) || isdigit(ch) || ch == '_') {
        chs.push_back(ch);
        ch = next();
    }
    back();
    string name(chs.begin(), chs.end());
    if (keywordmap.contains(name)) {
        return Token(keywordmap[name]);
    }
    chs.push_back('\0');
    string s(chs.begin(), chs.end());
    return Token(TokenType::ID, s);
}

Token Lexer::number() {
    vector<char> number;
    char ch = previous();
    while (isdigit(ch)) {
        number.push_back(ch);
        ch = next();
    }
    back();
    if (match('.')) {
        number.push_back('.');
        ch = next();
        while (isdigit(ch)) {
            number.push_back(ch);
            ch = next();
        }
        back();
        number.push_back('\0');
        return Token(TokenType::FLOAT_CONST, atof(number.data()));
    }
    number.push_back('\0');
    return Token(TokenType::INT_CONST, atoi(number.data()));
}

Token Lexer::lex() {
    skip_whitespace();
    skip_comment();
    skip_whitespace();

    //@formatter:off
    switch (next()) {
        case '>': return make_token(match('=') ? TokenType::GEQ : TokenType::GT);
        case '<': return make_token(match('=') ? TokenType::LEQ : TokenType::LT);
        case '=': return make_token(match('=') ? TokenType::EQ : TokenType::ASSIGN);
        case '!': return make_token(match('=') ? TokenType::NEQ : TokenType::LOGIC_NOT);
        case '+':
            if (match('=')) return make_token(TokenType::ADD_ASSIGN);
            else if (match('+')) return make_token(TokenType::INCREMENT);
            else return make_token(TokenType::ADD);
        case '-':
            if (match('=')) return make_token(TokenType::MINUS_ASSIGN);
            else if (match('-')) return make_token(TokenType::DECREMENT);
            else return make_token(TokenType::MINUS);
        case '*': return make_token(match('=') ? TokenType::MULTI_ASSIGN : TokenType::MULTI);
        case '/': return make_token(match('=') ? TokenType::DIV_ASSIGN : TokenType::DIV);
        case '%': return make_token(match('=') ? TokenType::MOD_ASSIGN : TokenType::MOD);
        case '&': return make_token(match('&') ? TokenType::LOGIC_AND : TokenType::AND);
        case '|': return make_token(match('|') ? TokenType::LOGIC_OR : TokenType::OR);
        case '^': return make_token(TokenType::XOR);
        case '~': return make_token(TokenType::NOT);
        case ',': return make_token(TokenType::COMMA);
        case ':': return make_token(TokenType::COLON);
        case '?': return make_token(TokenType::COND);
        case ';': return make_token(TokenType::SEMICOLON);
        case '(': return make_token(TokenType::LPAREN);
        case ')': return make_token(TokenType::RPAREN);
        case '[': return make_token(TokenType::LBRACKET);
        case ']': return make_token(TokenType::RBRACKET);
        case '{': return make_token(TokenType::LBRACE);
        case '}': return make_token(TokenType::RBRACE);
        case 'a' ... 'z': case 'A' ... 'Z': case '_': return identifier();
        case '0' ... '9': return number();
        case '\'': return character();
        case '\0': return make_token(TokenType::END);
        default: return make_token(TokenType::INVALID);
    }
    //@formatter:on
}

char Lexer::peek() {
    return code[idx];
}

char Lexer::next() {
    return code[idx++];
}

char Lexer::previous() {
    return code[idx - 1];
}

void Lexer::back() {
    idx--;
}

bool Lexer::match(char target) {
    if (peek() == target) {
        idx++;
        return true;
    }
    return false;
}

void Lexer::expect(char target) {
    if (!match(target))
        cerr << "expect " << target << endl;
}

Token Lexer::make_token(TokenType type) {
    return Token(type);
}

