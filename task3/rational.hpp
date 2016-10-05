//
//  rational.hpp
//  C++(HomeTasks)
//
//  Created by Egor Safronov on 00.10.16.
//  Copyright © 2016 Egor Safronov. All rights reserved.
//

#ifndef rational_hpp
#define rational_hpp

class rational {
private:
    int num;
    int denom;
    int gcd(int temp1, int temp2);
    
public:
    rational(int num);
    rational(int num, int denom);
    rational operator +(rational const &temp);
    rational operator -(rational const &temp);
    rational operator *(rational const &temp);
    rational operator /(rational const &temp);
    int getNum() const;
    int getDenom() const;
    
    
};

#endif /* rational_hpp */
