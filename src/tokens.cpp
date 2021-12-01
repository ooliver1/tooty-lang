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

#include "lexer.hpp"

#include <string>

using std::strcat;
using std::string;
using std::to_string;

Token::Token(string filename, int line, int pos, int lpos, TOKENS type,
             string value) {
    this->pos = pos;
    this->lpos = lpos;
    this->line = line;
    this->type = type;
    this->filename = filename;
    if (!value.empty()) {
        if (value == string("\n")) {
            this->value = "\\n";
        }
        else {
            this->value = value;
        }
    }
}

static const char *types[] = {
    "IDENT",      "NUMBER",     "STRING",    "CHAR",    "LPAR",     "RPAR",
    "LSQB",       "RSQB",       "LBRACE",    "RBRACE",  "COLON",    "COLONEQL",
    "SEMI",       "PLUS",       "PLSEQL",    "MINUS",   "MINUSEQL", "STAR",
    "STAREQL",    "DBSTAR",     "DBSTAREQL", "SLASH",   "SLASHEQL", "DBSLASH",
    "DBSLASHEQL", "BACKSLASH",  "PIPE",      "DBPIPE",  "PIPEQL",   "AMPER",
    "DBAMPER",    "DOT",        "EQL",       "DBEQL",   "TRPEQL",   "EXCL",
    "NTEQUL",     "NTDBEQL",    "CARRET",    "TILDE",   "GREAT",    "GREATEQL",
    "DBGREAT",    "DBGREATEQL", "LESS",      "LESSEQL", "DBLESS",   "DBLESSEQL",
    "PERC",       "PERCEQL",    "AT",        "ELIP",    "NL",       "COMMA",
    "ARROW"};

string Token::toString() const {
    string t;
    t += "<Token ";
    t += this->filename;
    t += ":";
    t += to_string(this->line);
    t += ":";
    t += to_string(this->lpos);
    t += " (";
    t += to_string(this->pos);
    t += ") ";
    t += "type=";
    t += types[int{this->type}];
    t += " value=";
    t += this->value;
    t += ">";
    return t;
}
