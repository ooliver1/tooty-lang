/*
SPDX -License-Identifier: MIT
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

#include <cstring>
#include <iostream>
#include <list>
#include <stdio.h>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::list;
using std::string;
using std::strstr;
using std::vector;

struct Flags {
    string path;
    vector<string> files;
    bool version = false;
    bool help = false;
    string helpCmd = "";
    bool error = false;
    string errorMsg = "";
};

Flags getFlags(int argc, char **argv);

int main(int argc, char **argv) {
    Flags flags = getFlags(argc, argv);
    cout << flags.version << endl;
    return 0;
}

Flags getFlags(int argc, char **argv) {
    Flags flags;
    for (int i = 0; i < argc; i++) { // base iterator
        string arg{argv[i]};
        if (i == 0) { // first arg
            flags.path = arg;
        }
        else if (arg.size() > 1 && arg[0] == '-') {
            list<string> args;
            if (arg.size() == 1) { // -a
                args.push_back(arg.substr(1, string::npos));
            }
            else if (arg[1] == '-') { // --aa
                args.push_back(arg.substr(2, string::npos));
            }
            else if (arg.size() > 1) { // -abc
                for (char c: arg) {
                    args.push_back(string{c});
                }
            }
            for (const string &f: args) { // second iterator for "-abc"
                if (f == "v" || f == "version") {
                    flags.version = true;
                    return flags;
                }
                else if (f == "h" || f == "help") {
                    flags.help = true;
                    flags.helpCmd = string{argv[i + 1]};
                    i++;
                }
                else {
                    flags.error = true;
                    flags.errorMsg = "Unknown flag: " + arg;
                }
            }
        }
    }
    return flags;
}
