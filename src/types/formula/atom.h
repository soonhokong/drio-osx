/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#include "types/formula/term.h"

namespace shell{

enum atom_kind { Equality, Predicate };
        
/* Abstract base class for atomic formulas */
class atom {
protected:
    unsigned            a_kind;
public:
    atom_kind kind() const { return static_cast<atom_kind>(a_kind); }
    virtual bool val() const =0;
};

/* Equality type atomic formula */
enum equality_op { EQ, GT, LT, GTE, LTE };

class atom_eq : public atom {
protected:
    unsigned            a_op;
    const term*         a_lhs;
    const term*         a_rhs;
public:
    atom_eq(unsigned op, const term *lhs, const term *rhs);
    equality_op kind() const { return static_cast<equality_op>(a_op); }
    bool val() const;
};
}