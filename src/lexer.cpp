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

#include "tokens.hpp"

#include <cassert>
#include <list>
#include <regex>
#include <string>

using std::list;
using std::regex_search;
using std::smatch;
using std::string;

class Lexer {
  public:
    Lexer(string filename, string source);

  private:
    int pos = 0;
    int line = 0;
    string source;
    string filename;
    list<string> tokens;
    char getChar() const;
    Token processChar();
    Token processIdent();
    Token processString();
    Token processNumber();
    // Token processSymbol();
};

Lexer::Lexer(string filename, string source) {
    this->filename = filename;
    this->source = source;
}

char Lexer::getChar() const { return this->source.at(this->pos); }

Token Lexer::processIdent() {
    smatch m;
    string code = this->source.substr(this->pos);
    bool search = regex_search(code, m, IDENT_RE);
    assert(search);
    return Token{this->filename, this->line, this->pos, TOKENS::IDENT, m.str()};
};

Token Lexer::processString() {
    smatch m;
    string code = this->source.substr(this->pos);
    bool search = regex_search(code, m, STRING_RE);
    assert(search);
    return Token{this->filename, this->line, this->pos, TOKENS::STRING,
                 m.str()};
};

Token Lexer::processNumber() {
    smatch m;
    string code = this->source.substr(this->pos);
    bool search = regex_search(code, m, NUMBER_RE);
    assert(search);
    return Token{this->filename, this->line, this->pos, TOKENS::NUMBER,
                 m.str()};
};

Token Lexer::processChar() {
    smatch m;
    string code = this->source.substr(this->pos);
    bool search = regex_search(code, m, CHAR_RE);
    assert(search);
    return Token{this->filename, this->line, this->pos, TOKENS::CHAR, m.str()};
};
