//
//  rational.h
//  C++(HomeTasks)
//
//  Created by Egor Safronov on 05.10.16.
//  Copyright © 2016 Egor Safronov. All rights reserved.
//

#ifndef rational_h
#define rational_h

class rational {
private:
    int num;
    int denom;
    // Find greatest common divisor
    int gcd(int temp1, int temp2);
    
public:
    // Create new rational from integer
    rational(int num);
    
    // Create new rational from numerator and denominator
    rational(int num, int denom);
    
    // Do addition of another rational
    rational operator +(rational const &temp) const;
    
    // Do substraction of another rational
    rational operator -(rational const &temp) const;
    
    // Do multiplication of another rational
    rational operator *(rational const &temp) const;
    
    // Do division of another rational
    rational operator /(rational const &temp) const;
    
    // Return numerator
    int getNum() const;
    
    // Return denomenator
    int getDenom() const;
    
    
};

#endif /* rational_h */
