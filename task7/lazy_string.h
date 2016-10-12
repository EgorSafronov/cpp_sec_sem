//
//  lazy_string.hpp
//  C++(HomeTasks)
//
//  Created by Egor Safronov on 00.10.16.
//  Copyright © 2016 Egor Safronov. All rights reserved.
//

#ifndef lazy_string_h
#define lazy_string_h

#include <string>
#include <memory>
#include <mutex>
#include <thread>
#include <atomic>

using namespace std;

class locks {
private:
    mutex mut;
    atomic<int> readers;
    
public:
    locks();
    locks(const locks &lock);
    void lockRead();
    void lockWrite();
    void unlockRead();
    void unlockWrite();
    
};

class lazy_string {
    struct lazy_char {
        friend class lazy_string;
    private:
        const size_t pos;
        lazy_string * const lazy_s;
        lazy_char(lazy_string *l_s, size_t pos);
        
    public:
        operator char() const;
        lazy_char &operator=(char c);
    };
    
private:
    size_t beg, len;
    shared_ptr<string> sh_s;
    lazy_string(const shared_ptr<locks> lock, shared_ptr<string> sh, size_t begin, size_t len);
    shared_ptr<locks> lock;
    
public:
    //Create new empty lazy_string
    lazy_string();
    
    //Create new lazy_string from string
    lazy_string(string &s);
    
    //Return length of lazy_string
    size_t size() const;
    
    //Return length of lazy_string
    size_t length() const;
    
    //Return a symbol at position "pos"
    char at(size_t pos) const;
    lazy_char at(size_t pos);
    
    //Return a symbol at position "pos"
    char operator[](size_t pos) const;
    lazy_char operator[](size_t pos);
    
    //Read lazy_string from istream
    friend istream &operator >> (istream &input, lazy_string &l_s);
    
    //Write lazy_string to ostream
    friend ostream &operator << (ostream &output, lazy_string &l_s);
    
    //Return a part of lasy_string from "pos" to "pos + len". If this lazy_string is shorter than
    //"pos + len", suffix of lazy_string starting from "pos" will be returned
    lazy_string substr(size_t pos, size_t len);
    
    //Return string copy of lazy_string
    operator string();
};


#endif /* lazy_string_h */
