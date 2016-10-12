//
//  lazy_string.cpp
//  C++(HomeTasks)
//
//  Created by Egor Safronov on 00.10.16.
//  Copyright © 2016 Egor Safronov. All rights reserved.
//

#include "lazy_string.h"
#include <fstream>

using namespace std;

lazy_string::lazy_string() {
    this->beg = 0;
    this->len = 0;
    this->sh_s = make_shared<string>("");
}

lazy_string::lazy_string(string &s) {
    this->beg = 0;
    this->len = s.length();
    this->sh_s = make_shared<string>(s);
}

lazy_string::lazy_string(shared_ptr<string> sh, size_t beg, size_t len) {
    this->sh_s = sh;
    this->beg = beg;
    this->len = len;
}

size_t lazy_string::size() const {
    return this->len;
}

size_t lazy_string::length() const {
    return this->len;
}

char lazy_string::at(size_t pos) const {
    return (*(this->sh_s))[this->beg + pos];
}

char lazy_string::operator[](size_t pos) const {
    return (*(this->sh_s))[this->beg + pos];
}

istream &operator>>(istream &input, lazy_string &l_s) {
    auto temp = make_shared<string>();
    input >> *temp;
    l_s.beg = 0;
    l_s.len = (*temp).length();
    l_s.sh_s = temp;
    return input;
}

ostream &operator<<(ostream &output, lazy_string &l_s) {
    for (size_t i = l_s.beg; i < l_s.beg + l_s.len; i++) {
        output << l_s[i];
    }
    return output;
}

lazy_string lazy_string::substr(size_t pos, size_t len) {
    size_t temp;
    if (pos + len > this->len) {
        temp = this->len - pos;
    } else {
        temp = len;
    }
    return lazy_string(this->sh_s, this->beg + pos, temp);
}

lazy_string::operator std::string() {
    return (*(this->sh_s)).substr(beg, len);
}

lazy_string::lazy_char::lazy_char(lazy_string *l_s, size_t i) : lazy_s(l_s), pos(i) {}

lazy_string::lazy_char lazy_string::at(size_t pos) {
    return lazy_char(this, pos);
}

lazy_string::lazy_char lazy_string::operator[](size_t pos) {
    return lazy_char(this, pos);
}

lazy_string::lazy_char::operator char() const {
    return (*(lazy_s->sh_s))[lazy_s->beg + this->pos];
}

lazy_string::lazy_char &lazy_string::lazy_char::operator=(char c) {
    if (lazy_s->sh_s.use_count() > 1) {
        lazy_s->sh_s = make_shared<string>(lazy_s->sh_s->substr(lazy_s->beg, lazy_s->len));
        lazy_s->beg = 0;
    }
    (*lazy_s->sh_s)[lazy_s->beg + lazy_s->len] = c;
    return *this;
}
