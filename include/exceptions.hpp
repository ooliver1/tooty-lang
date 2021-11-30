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

#include <cstring>
#include <exception>
#include <string>

class InvalidSyntax: public std::exception {
  public:
    const std::string lpos;
    const std::string line;
    const std::string file;
    const std::string message;
    explicit InvalidSyntax(const std::string file, const int line,
                           const int lpos, std::string message)
        : file(file), line(std::to_string(line)), lpos(std::to_string(lpos)),
          message(message){};
    virtual const char *what() const throw() {
        std::string m;
        m += this->file;
        m += ":";
        m += this->line;
        m += ":";
        m += this->lpos;
        m += ": ";
        m += this->message;
        return m.c_str();
    }
};

class UnknownToken: public InvalidSyntax {
  public:
    explicit UnknownToken(const std::string file, const int line, const int pos,
                          std::string message)
        : InvalidSyntax(file, line, pos, message){};
};
