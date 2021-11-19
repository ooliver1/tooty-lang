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

#include <list>
#include <string>

using std::list;
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
    Token processIdent() const;
    Token processString() const;
    Token processNumber() const;
    Token processSymbol() const;
};

Lexer::Lexer(string filename, string source) {
    this->filename = filename;
    this->source = source;
}

char Lexer::getChar() const { return this->source.at(this->pos); }
