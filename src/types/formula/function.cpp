/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#include <string>
#include <cmath>
#include "types/formula/function.h"

namespace shell{

term_func::term_func(const unsigned op, const term *arg1):
    m_op(op),
    m_num_args(1),
    arg1(arg1){};

term_func::term_func(const unsigned op, const term *arg1, const term *arg2):
    m_op(op),
    m_num_args(2),
    arg1(arg1),
    arg2(arg2){};

double term_func::val() const {
    switch (m_op){
        case Add:
            return arg1->val() + arg2->val();
        case Sub:
            return arg1->val() - arg2->val();
        case Mult:
            return arg1->val() * arg2->val();
        case Div:
            return arg1->val() / arg2->val();
        case Pow:
            return std::pow(arg1->val(), arg2->val());
        case Neg:
            return arg1->val() * -1;
    }
    //Should never reach here
    return 0;
}
}