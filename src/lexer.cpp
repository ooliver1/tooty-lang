/*
SPDX-License-Identifier: MIT
Tooty-lang - A compiled and iterpreted language written in C++

MIT License

Copyright (c) 2021-present Oliver Wilkes

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "lexer.hpp"

#include "exceptions.hpp"
#include "tokens.hpp"

#include <cassert>
#include <ctype.h>
#include <iostream>
#include <list>
#include <regex>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::list;
using std::out_of_range;
using std::regex_search;
using std::smatch;
using std::string;
using std::vector;

Lexer::Lexer(string filename, string source) {
    this->filename = filename;
    this->source = source;
}

char Lexer::getChar() const {
    try {
        return this->source.at(this->pos);
    }
    catch (const out_of_range &) {
        return EOF;
    }
}

char Lexer::nextChar(int offset) const {
    try {
        return this->source.at(this->pos + offset);
    }
    catch (const out_of_range &) {
        return EOF;
    }
}

bool Lexer::next() const {
    try {
        this->source.at(this->pos);
        return true;
    }
    catch (const out_of_range &) {
        return false;
    }
}
Token Lexer::processIdent() {
    smatch m;
    string code = this->source.substr(this->pos);
    bool search = regex_search(code, m, IDENT_RE);
    assert(search);
    int tmp = this->pos;
    this->pos += m.length();
    return Token{this->filename, this->line, tmp, TOKENS::IDENT, m.str()};
}

Token Lexer::processString() {
    smatch m;
    string code = this->source.substr(this->pos);
    bool search = regex_search(code, m, STRING_RE);
    assert(search);
    int tmp = this->pos;
    this->pos += m.length();
    return Token{this->filename, this->line, tmp, TOKENS::STRING, m.str()};
}

Token Lexer::processNumber() {
    smatch m;
    string code = this->source.substr(this->pos);
    bool search = regex_search(code, m, NUMBER_RE);
    assert(search);
    int tmp = this->pos;
    this->pos += m.length();
    return Token{this->filename, this->line, tmp, TOKENS::NUMBER, m.str()};
}

Token Lexer::processChar() {
    smatch m;
    string code = this->source.substr(this->pos);
    bool search = regex_search(code, m, CHAR_RE);
    assert(search);
    int tmp = this->pos;
    this->pos += m.length();
    return Token{this->filename, this->line, tmp, TOKENS::CHAR, m.str()};
}

Token Lexer::processSymbol() {
    char c = this->getChar();
    char c2 = this->nextChar(1);
    if (c2 == EOF) {
        try {
            int tmp = this->pos;
            this->pos++;
            return Token(this->filename, this->line, tmp, SYMBOLS.at(string{c}),
                         "");
        }
        catch (const out_of_range &e) {
            this->pos--;
            throw UnknownToken{this->filename, this->line, this->pos,
                               "Unknown symbol: " + c};
        }
    }
    char c3 = this->nextChar(2);
    if (c3 == EOF) {
        try {
            int tmp = this->pos;
            this->pos += 2;
            return Token(this->filename, this->line, tmp,
                         SYMBOLS.at(string{string() + c + c2}), "");
        }
        catch (const out_of_range &e) {
            this->pos -= 2;
            throw UnknownToken{this->filename, this->line, this->pos,
                               "Unknown symbol: " + c + c2};
        }
    }
    try {
        int tmp = this->pos;
        this->pos += 3;
        return Token(this->filename, this->line, tmp,
                     SYMBOLS.at(string{string() + c + c2 + c3}), "");
    }
    catch (const out_of_range &e) {
        this->pos -= 3;
        try {
            int tmp = this->pos;
            this->pos += 2;
            return Token(this->filename, this->line, tmp,
                         SYMBOLS.at(string{string() + c + c2}), "");
        }
        catch (const out_of_range &e) {
            this->pos -= 2;
            try {
                int tmp = this->pos;
                this->pos++;
                return Token(this->filename, this->line, tmp,
                             SYMBOLS.at(string{string() + c}), "");
            }
            catch (const out_of_range &e) {
                throw UnknownToken{this->filename, this->line, this->pos,
                                   "Unknown symbol: " + c};
            }
        }
    }
}

vector<Token> Lexer::tokenize() {
    vector<Token> tokens;
    while (this->next()) {
        char c = this->getChar();
        if (c == EOF) {
            break;
        }
        if (isspace(c)) {
            if (c == '\n') {
                this->line++;
            }
            this->pos++;
            continue;
        }
        if (c == '"') {
            tokens.push_back(this->processString());
        }
        if (c == '\'') {
            tokens.push_back(this->processChar());
        }
        if (SYMS.find(c) != string::npos) {
            tokens.push_back(this->processSymbol());
        }
        if (NUMS.find(c) != string::npos) {
            tokens.push_back(this->processNumber());
        }
        if (IDENTS.find(c) != string::npos) {
            tokens.push_back(this->processIdent());
        }
    }
    return tokens;
}
