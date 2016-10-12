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
    this->lock = make_shared<locks>();
}

lazy_string::lazy_string(string &s) {
    this->beg = 0;
    this->len = s.length();
    this->sh_s = make_shared<string>(s);
    this->lock = make_shared<locks>();
}

lazy_string::lazy_string(const shared_ptr<locks> lock, shared_ptr<string> sh, size_t beg, size_t len) {
    this->lock = lock;
    this->sh_s = sh;
    this->beg = beg;
    this->len = len;
}

size_t lazy_string::size() const {
    this->lock->lockRead();
    size_t temp = this->len;
    this->lock->unlockRead();
    return temp;
}

size_t lazy_string::length() const {
    this->lock->lockRead();
    size_t temp = this->len;
    this->lock->unlockRead();
    return temp;
}

char lazy_string::at(size_t pos) const {
    this->lock->lockRead();
    char temp_char = (*(this->sh_s))[this->beg + pos];
    this->lock->unlockRead();
    return temp_char;
}

char lazy_string::operator[](size_t pos) const {
    this->lock->lockRead();
    char temp_char = (*(this->sh_s))[this->beg + pos];
    this->lock->unlockRead();
    return temp_char;
}

istream &operator>>(istream &input, lazy_string &l_s) {
    l_s.lock->lockWrite();
    auto temp = make_shared<string>();
    auto temp_l_s = l_s;
    input >> *temp;
    l_s.beg = 0;
    l_s.len = (*temp).length();
    l_s.sh_s = temp;
    l_s.lock = make_shared<locks>();
    temp_l_s.lock->unlockWrite();
    return input;
}

ostream &operator<<(ostream &output, lazy_string &l_s) {
    l_s.lock->lockRead();
    for (size_t i = l_s.beg; i < l_s.beg + l_s.len; i++) {
        output << l_s[i];
    }
    l_s.lock->unlockRead();
    return output;
}

lazy_string lazy_string::substr(size_t pos, size_t len) {
    this->lock->lockRead();
    size_t temp;
    if (pos + len > this->len) {
        temp = this->len - pos;
    } else {
        temp = len;
    }
    size_t temp_beg = this->beg;
    shared_ptr<string> temp_sh_s = this->sh_s;
    shared_ptr<locks> temp_lock = this->lock;
    this->lock->unlockRead();
    return lazy_string(temp_lock , temp_sh_s, temp_beg + pos, temp);
}

lazy_string::operator std::string() {
    this->lock->lockRead();
    string temp = this->sh_s->substr(beg, len);
    this->lock->unlockRead();
    return temp;
}

lazy_string::lazy_char::lazy_char(lazy_string *l_s, size_t i) : lazy_s(l_s), pos(i) {}

lazy_string::lazy_char lazy_string::at(size_t pos) {
    this->lock->lockRead();
    lazy_char temp_lc = lazy_char(this, pos);
    this->lock->unlockRead();
    return temp_lc;
}

lazy_string::lazy_char lazy_string::operator[](size_t pos) {
    this->lock->lockRead();
    lazy_char temp_lc = lazy_char(this, pos);
    this->lock->unlockRead();
    return temp_lc;
}

lazy_string::lazy_char::operator char() const {
    lazy_s->lock->lockRead();
    char temp_char = (*(lazy_s->sh_s))[lazy_s->beg + this->pos];
    lazy_s->lock->unlockRead();
    return temp_char;
}

lazy_string::lazy_char &lazy_string::lazy_char::operator=(char c) {
    lazy_s->lock->lockWrite();
    shared_ptr<locks> temp_lock = lazy_s->lock;
    if (lazy_s->sh_s.use_count() > 1) {
        lazy_s->sh_s = make_shared<string>(lazy_s->sh_s->substr(lazy_s->beg, lazy_s->len));
        lazy_s->beg = 0;
        lazy_s->lock = make_shared<locks>();
    }
    (*lazy_s->sh_s)[lazy_s->beg + lazy_s->len] = c;
    temp_lock->unlockWrite();
    return *this;
}

locks::locks() {
    this->readers = 0;
}

locks::locks(const locks &lock) {
    this->readers = 0;
}

void locks::lockRead() {
    this->mut.lock();
    this->readers++;
    this->mut.unlock();
}

void locks::lockWrite() {
    this->mut.lock();
    while (this->readers > 0) {
        this_thread::yield();
    }
}

void locks::unlockRead() {
    this->readers--;
}

void locks::unlockWrite() {
    this->mut.unlock();
}
