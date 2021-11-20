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

#pragma once

class Token {
  public:
    Token(string, int, int, TOKENS, string);
    int pos;
    int line;
    TOKENS type;
    string filename;
    string value = "NULL";
    string toString() const;
};

enum TOKENS
{
    IDENT,      // abc
    NUMBER,     // 123
    STRING,     // "aaa"
    CHAR,       // 'a'
    LPAR,       // (
    RPAR,       // )
    LSQB,       // [
    RSQB,       // ]
    LBRACE,     // {
    RBRACE,     // }
    COLON,      // :
    COLONEQL,   // :=
    SEMI,       // ;
    PLUS,       // +
    PLSEQL,     // +=
    MINUS,      // -
    MINUSEQL,   // -=
    STAR,       // *
    STAREQL,    // *=
    DBSTAR,     // **
    DBSTAREQL,  // **=
    SLASH,      // /
    SLASHEQL,   // /=
    DBSLASH,    // //
    DBSLASHEQL, // //=
    BACKSLASH,  // "\"
    PIPE,       // |
    DBPIPE,     // ||
    PIPEQL,     // |=
    AMPER,      // &
    DBAMPER,    // &&
    DOT,        // .
    EQL,        // =
    DBEQL,      // ==
    TRPEQL,     // ===
    EXCL,       // !
    NTEQUL,     // !=
    NTDBEQL,    // !==
    CARRET,     // ^
    TILDE,      // ~
    GREAT,      // >
    GREATEQL,   // >=
    DBGREAT,    // >>
    DBGREATEQL, // >>=
    LESS,       // <
    LESSEQL,    // <=
    DBLESS,     // <<
    DBLESSEQL,  // <<=
    PERC,       // %
    PERCEQL,    // %=
    AT,         // @
    ELIP,       // ...
    CMT,        // #
    MCMTS,      // /*
    MCMTE       // */
};
