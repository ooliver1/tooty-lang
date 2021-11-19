/*
SPDX - License - Identifier: MIT
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

#include <cstdio>
#include <regex>
#include <string>
#include <unordered_map>

using std::basic_regex;
using std::snprintf;
using std::string;
using std::to_string;
using std::unordered_map;

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

const unordered_map<string, TOKENS> SYMBOLS = {
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

const basic_regex<char> IDENT_RE{"/^[a-zA-Z_][a-zA-Z0-9]*/"};
const basic_regex<char> NUMBER_RE{"/^[0-9]+/"};
const basic_regex<char> STRING_RE{"/^\"[^\"]*\"/"};
const basic_regex<char> CHAR_RE{"/^'.'/"};

const string SYM = "()[]{}<>\\|/:;+-.*=!@&%~^";
const string NUMS = "0123456789";
const string IDENT = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";

class Token {
  public:
    int pos;
    TOKENS type;
    string filename;
    string value = "NULL";
    string toString() const;
};

string Token::toString() const {
    char *buf = 0;
    snprintf(buf, 0, "<Token %s:%s type=%s value=%s>", this->filename,
             this->pos, this->type, this->value);
    return string{buf};
}
