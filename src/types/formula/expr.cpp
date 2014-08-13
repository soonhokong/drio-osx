/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include "types/formula/expr.h"
namespace shell{

expr mk_expr(expr_cell *ptr){
    expr temp;
    temp.m_ptr = ptr;
    return temp;
}

}
