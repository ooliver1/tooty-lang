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

#include <regex>
#include <string>
#include <unordered_map>

const std::basic_regex<char> IDENT_RE{"^[a-zA-Z_][a-zA-Z0-9]*"};
const std::basic_regex<char> NUMBER_RE{"^[0-9]+"};
const std::basic_regex<char> STRING_RE{"^\"[^\"]*\""};
const std::basic_regex<char> CHAR_RE{"^'.'"};

const std::string SYMS = "()[]{}<>\\|/:;+-.*=!@&%~^";
const std::string NUMS = "0123456789";
const std::string IDENTS =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";

enum class TOKENS;

class Token {
  public:
    Token(std::string, int, int, TOKENS, std::string);
    int pos;
    int line;
    TOKENS type;
    std::string filename;
    std::string value = "NULL";
    std::string toString() const;
};

enum class TOKENS
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

const std::unordered_map<std::string, TOKENS> SYMBOLS = {
    {"(", TOKENS::LPAR},         {")", TOKENS::RPAR},
    {"[", TOKENS::LSQB},         {"]", TOKENS::RSQB},
    {"{", TOKENS::LBRACE},       {"}", TOKENS::RBRACE},
    {":", TOKENS::COLON},        {":=", TOKENS::COLONEQL},
    {";", TOKENS::SEMI},         {"+", TOKENS::PLUS},
    {"+=", TOKENS::PLSEQL},      {"-", TOKENS::MINUS},
    {"-=", TOKENS::MINUSEQL},    {"*", TOKENS::STAR},
    {"*=", TOKENS::STAREQL},     {"**", TOKENS::DBSTAR},
    {"**=", TOKENS::DBSTAREQL},  {"/", TOKENS::SLASH},
    {"/=", TOKENS::SLASHEQL},    {"//", TOKENS::DBSLASH},
    {"//=", TOKENS::DBSLASHEQL}, {"\\", TOKENS::BACKSLASH},
    {"|", TOKENS::PIPE},         {"||", TOKENS::DBPIPE},
    {"|=", TOKENS::PIPEQL},      {"&", TOKENS::AMPER},
    {"&&", TOKENS::DBAMPER},     {".", TOKENS::DOT},
    {"=", TOKENS::EQL},          {"==", TOKENS::DBEQL},
    {"===", TOKENS::TRPEQL},     {"!", TOKENS::EXCL},
    {"!=", TOKENS::NTEQUL},      {"!==", TOKENS::NTDBEQL},
    {"^", TOKENS::CARRET},       {"~", TOKENS::TILDE},
    {">", TOKENS::GREAT},        {">=", TOKENS::GREATEQL},
    {">>", TOKENS::DBGREAT},     {">>=", TOKENS::DBGREATEQL},
    {"<", TOKENS::LESS},         {"<=", TOKENS::LESSEQL},
    {"<<", TOKENS::DBLESS},      {"<<=", TOKENS::DBLESSEQL},
    {"%", TOKENS::PERC},         {"%=", TOKENS::PERCEQL},
    {"@", TOKENS::AT},           {"...", TOKENS::ELIP},
    {"#", TOKENS::CMT},          {"/*", TOKENS::MCMTS},
    {"*/", TOKENS::MCMTE},
};
