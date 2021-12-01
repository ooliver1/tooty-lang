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

#include <algorithm>
#include <cassert>
#include <ctype.h>
#include <iostream>
#include <list>
#include <memory>
#include <regex>
#include <string>

using std::count;
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
        return source.at(this->pos - 1);
    }
    catch (const out_of_range &) {
        return EOF;
    }
}

char Lexer::nextChar(int offset) const {
    try {
        return source.at(this->pos + offset - 1);
    }
    catch (const out_of_range &) {
        return EOF;
    }
}

bool Lexer::next() const {
    try {
        source.at(this->pos - 1);
        return true;
    }
    catch (const out_of_range &) {
        return false;
    }
}
Token Lexer::processIdent() {
    smatch m;
    string code = source.substr(this->pos - 1);
    bool search = regex_search(code, m, IDENT_RE);
    if (search) {
        int tmp = this->pos;
        int tmp2 = this->lpos;
        this->pos += m.length();
        this->lpos += m.length();
        return Token{this->filename, this->line,    tmp,
                     tmp2,           TOKENS::IDENT, m.str()};
    }
    else {
        throw UnknownToken(this->filename, this->line, this->lpos,
                           string("Unknown symbol (id): '") + this->getChar()
                               + '\'');
    }
}

Token Lexer::processString() {
    smatch m;
    string code = source.substr(this->pos - 1);
    bool search = regex_search(code, m, STRING_RE);
    if (search) {
        int tmp = this->pos;
        int tmp2 = this->lpos;
        this->pos += m.length();
        this->lpos += m.length();
        return Token{this->filename, this->line,     tmp,
                     tmp2,           TOKENS::STRING, m.str()};
    }
    else {
        throw UnknownToken(this->filename, this->line, this->lpos,
                           string("Unknown symbol (str): '") + this->getChar()
                               + '\'');
    }
}

Token Lexer::processNumber() {
    smatch m;
    string code = source.substr(this->pos - 1);
    bool search = regex_search(code, m, NUMBER_RE);
    if (search) {
        int tmp = this->pos;
        int tmp2 = this->lpos;
        this->pos += m.length();
        this->lpos += m.length();
        return Token{this->filename, this->line,     tmp,
                     tmp2,           TOKENS::NUMBER, m.str()};
    }
    else {
        throw UnknownToken(this->filename, this->line, this->lpos,
                           string("Unknown symbol (num): '") + this->getChar()
                               + '\'');
    }
}

Token Lexer::processChar() {
    smatch m;
    string code = source.substr(this->pos - 1);
    bool search = regex_search(code, m, CHAR_RE);
    if (search) {
        int tmp = this->pos;
        int tmp2 = this->lpos;
        this->pos += m.length();
        this->lpos += m.length();
        return Token{this->filename, this->line,   tmp,
                     tmp2,           TOKENS::CHAR, m.str()};
    }
    else {
        throw UnknownToken(this->filename, this->line, this->lpos,
                           string("Unknown symbol (char): '") + this->getChar()
                               + '\'');
    }
}

Token Lexer::processSymbol() {
    char c = this->getChar();
    char c2 = this->nextChar(1);
    if (c2 == EOF) {
        try {
            int tmp = this->pos;
            int tmp2 = this->lpos;
            this->pos++;
            this->lpos++;
            return Token(this->filename, this->line, tmp, tmp2,
                         SYMBOLS.at(string{c}), "");
        }
        catch (const out_of_range &e) {
            this->pos--;
            this->lpos--;
            throw UnknownToken{this->filename, this->line, this->lpos,
                               string("Unknown symbol (sym-1): '") + c + '\''};
        }
    }
    char c3 = this->nextChar(2);
    if (c3 == EOF) {
        try {
            int tmp = this->pos;
            int tmp2 = this->lpos;
            this->pos += 2;
            this->lpos += 2;
            return Token(this->filename, this->line, tmp, tmp2,
                         SYMBOLS.at(string{string() + c + c2}), "");
        }
        catch (const out_of_range &e) {
            this->pos -= 2;
            this->lpos -= 2;
            throw UnknownToken{this->filename, this->line, this->lpos,
                               string("Unknown symbol (sym-2): '") + c + '\''
                                   + c2};
        }
    }
    try {
        int tmp = this->pos;
        int tmp2 = this->lpos;
        this->pos += 3;
        this->lpos += 3;
        return Token(this->filename, this->line, tmp, tmp2,
                     SYMBOLS.at(string{string() + c + c2 + c3}), "");
    }
    catch (const out_of_range &e) {
        this->pos -= 3;
        this->lpos -= 3;
        try {
            int tmp = this->pos;
            int tmp2 = this->lpos;
            this->pos += 2;
            this->lpos += 2;
            return Token(this->filename, this->line, tmp, tmp2,
                         SYMBOLS.at(string{string() + c + c2}), "");
        }
        catch (const out_of_range &e) {
            this->pos -= 2;
            this->lpos -= 2;
            try {
                int tmp = this->pos;
                int tmp2 = this->lpos;
                this->pos++;
                this->lpos++;
                return Token(this->filename, this->line, tmp, tmp2,
                             SYMBOLS.at(string{string() + c}), "");
            }
            catch (const out_of_range &e) {
                this->pos--;
                this->lpos--;
                throw UnknownToken{this->filename, this->line, this->lpos,
                                   string("Unknown symbol (sym-1): '") + c
                                       + '\''};
            }
        }
    }
}

vector<Token> Lexer::tokenize() {
    bool ignore_nl = false;
    vector<Token> tokens{};
    vector<char> brackets{};
    while (next()) {
        char c = this->getChar();
        if (c == EOF) {
            break;
        }
        else if (isspace(c)) {
            if (c == '\n') {
                int tmp = this->pos;
                int tmp2 = this->lpos;
                int tmp3 = this->line;
                for (int i = 1; this->nextChar(i) == '\n'; i++) {
                    this->line++;
                    this->pos++;
                }
                this->pos++;
                this->line++;
                this->lpos = 1;
                if (!ignore_nl) {
                    tokens.push_back(Token{this->filename, tmp3, tmp, tmp2,
                                           TOKENS::NL, string("\n")});
                }
            }
            else {
                this->lpos++;
                this->pos++;
            }
        }
        else if (c == '#') {
            smatch m;
            string code = source.substr(this->pos - 1);
            bool search = regex_search(code, m, CMT_RE);
            if (search) {
                this->pos += m.length();
                this->lpos = 0;
                this->line++;
            }
            else {
                throw UnknownToken{this->filename, this->line, this->lpos,
                                   string("Unknown symbol (cmt): '") + c
                                       + '\''};
            }
        }
        else if (c == '/' and this->nextChar(1) == '*') {
            smatch m;
            string code = source.substr(this->pos - 1);
            bool search = regex_search(code, m, MULTI_CMT_RE);
            if (search) {
                this->pos += m.length();
                string::iterator b = m.str().begin();
                string::iterator e = m.str().end();
                int newlines = count(b, e, '\n');
                this->line += newlines;
                size_t found = m.str().find_last_of('\n');
                if (found != string::npos) {
                    this->lpos += (m.str().length() - found);
                }
            }
            else {
                throw UnknownToken{this->filename, this->line, this->lpos,
                                   string("Unknown symbol (m-cmt): '") + c
                                       + '\''};
            }
        }
        else if (c == '"') {
            tokens.push_back(processString());
        }
        else if (c == '\'') {
            tokens.push_back(processChar());
        }
        else if (SYMS.find(c) != string::npos) {
            tokens.push_back(processSymbol());
            switch (c) {
                case '(':
                case '[':
                case '{':
                    if (brackets.size() > MAXLEVEL) {
                        throw TooManyBrackets(
                            this->filename, this->line, this->lpos,
                            string("Too many brackets, MAXLEVEL is"
                                   + MAXLEVEL));
                    }
                    brackets.push_back(c);
                    break;
                case ')':
                case ']':
                case '}':
                    if (brackets.empty()) {
                        throw UnmatchedBracket(
                            this->filename, this->line, this->lpos,
                            string("Bracket mismatch, there is no opening"));
                    }
                    if (!((brackets.back() == '(' && c == ')')
                          || (brackets.back() == '[' && c == ']')
                          || (brackets.back() == '{' && c == '}'))) {
                        throw UnmatchedBracket(
                            this->filename, this->line, this->lpos,
                            string("Bracket mismatch, expected '")
                                + brackets.back() + "'");
                    }
                    brackets.pop_back();
                    break;
            }
            switch (c) {
                case '(':
                case '[':
                    ignore_nl = true;
                    break;
                case ')':
                case ']':
                    if (!(count(brackets.begin(), brackets.end(), '(')
                          || count(brackets.begin(), brackets.end(), '['))) {
                        ignore_nl = false;
                    }
                    else if ((brackets.back() == '(' && c == ')')
                             || (brackets.back() == '[' && c == ']')
                             || (brackets.back() == '{' && c == '}')) {
                        ignore_nl = false;
                    }
                    break;
            }
        }
        else if (NUMS.find(c) != string::npos) {
            tokens.push_back(processNumber());
        }
        else if (IDENTS.find(c) != string::npos) {
            tokens.push_back(processIdent());
        }
        else {
            throw UnknownToken{this->filename, this->line, this->lpos,
                               string("Unknown symbol: '") + c + '\''};
        }
    }
    return tokens;
}
