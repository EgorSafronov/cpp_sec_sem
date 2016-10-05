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
    int gcd(int temp1, int temp2);
    
public:
    rational(int num);
    rational(int , int denom);
    rational operator +(rational const &temp) const;
    rational operator -(rational const &temp) const;
    rational operator *(rational const &temp) const;
    rational operator /(rational const &temp) const;
    int getNum() const;
    int getDenom() const;
    
    
};

#endif /* rational_h */
