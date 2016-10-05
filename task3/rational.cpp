//
//  rational.cpp
//  C++(HomeTasks)
//
//  Created by Egor Safronov on 00.10.16.
//  Copyright © 2016 Egor Safronov. All rights reserved.
//

#include "rational.hpp"
//#include <algorithm>

rational::rational(int num) {
    this->num = num;
    denom = 1;
};

rational::rational(int num, int denom) {
    int temp = gcd(num, denom);
    this->num = num / temp;
    this->denom = denom / temp;
};

rational rational::operator +(rational const &temp) {
    return rational(num * temp.denom + temp.num * denom, denom * temp.denom);
};

rational rational::operator -(rational const &temp) {
    return rational(num * temp.denom - temp.num * denom, denom * temp.denom);
};

rational rational::operator *(rational const &temp) {
    return rational(num * temp.num, denom * temp.denom);
};

rational rational::operator /(rational const &temp) {
    return rational(num * temp.denom, denom * temp.num);
};

int rational::getNum() const {
    return num;
};

int rational::getDenom() const {
    return denom;
};

int rational::gcd(int temp1, int temp2) {
    /*
    while (temp2 > 0) {
        temp1 %= temp2;
        std::swap(temp1, temp2);
    }
    return temp1;
    */
    while ((temp1 > 0) && (temp2 > 0)) {
        if (temp1 > temp2) {
            temp1 %= temp2;
        } else {
            temp2 %= temp1;
        }
    }
    return temp1 + temp2;
}
