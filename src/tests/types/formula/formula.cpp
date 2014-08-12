/* Author: Soonho Kong <soonhok@cs.cmu.edu>
 * Copyright 2014 Soonho Kong
 */
#include "gtest/gtest.h"
#include "types/formula/term.h"
#include "types/formula/function.h"
#include "types/formula/formula.h"
#include "types/formula/atom.h"
#include "types/formula/connective.h"
#include <pthread.h>

using namespace shell;

TEST(term, constructors) {
    // Constant constructors
    term zero = mk_const(0);
    term one = mk_const(1);
    term n_one = mk_const(-1);
    term decimal = mk_const(0.1);
    EXPECT_EQ(0, zero.val());
    EXPECT_EQ(1, one.val());
    EXPECT_EQ(-1, n_one.val());
    EXPECT_EQ(0.1, decimal.val());
    EXPECT_EQ(term_kind::Constant, zero.kind());

    // Variable constructors
    set_var("uninitiated", term_type::Int);
    set_var("zero", zero);
    set_var("one", one);
    set_var("n_one", n_one);
    set_var("decimal", decimal);
    EXPECT_EQ(0, mk_var("uninitiated").val());
    EXPECT_EQ(0, mk_var("zero").val());
    EXPECT_EQ(1, mk_var("one").val());
    EXPECT_EQ(-1, mk_var("n_one").val());
    EXPECT_EQ(0.1, mk_var("decimal").val());
    EXPECT_ANY_THROW(mk_var("not_in_map").val());
    EXPECT_EQ(term_kind::Variable, mk_var("zero").kind());

    // Function constructors
    term two = mk_func(func_op::Add, one, one);
    term n_two = mk_func(func_op::Neg, two);
    EXPECT_EQ(2, two.val());
    EXPECT_EQ(-2, n_two.val());

    printf("Fault\n");
}

TEST(term, rounding){
    // Variable rounding
    term one_fourth = mk_const(.25);
    term one_half = mk_const(.5);
    term three_fourth = mk_const(.75);

    // Declaring variable types
    set_var("real", term_type::Real);
    set_var("int", term_type::Int);

    set_var("real", one_fourth);
    set_var("int", one_fourth);
    EXPECT_EQ(.25, mk_var("real").val());
    EXPECT_EQ(0, mk_var("int").val());

    set_var("real", one_half);
    set_var("int", one_half);
    EXPECT_EQ(.5, mk_var("real").val());
    EXPECT_EQ(1, mk_var("int").val());

    set_var("real", three_fourth);
    set_var("int", three_fourth);
    EXPECT_EQ(.75, mk_var("real").val());
    EXPECT_EQ(1, mk_var("int").val());
}

TEST(formula, constructors){
    // Equality constructors
    term one  = mk_const(1);

    fmla equal = mk_fmla_eq(equality_op::EQ, one, one);
    fmla less = mk_fmla_eq(equality_op::LT, one, one);
    EXPECT_EQ(true, equal.val());
    EXPECT_EQ(false, less.val());

    // Connective constructors
    fmla _and = mk_fmla_cnct(cnct_op::And, equal, less);
    fmla _or = mk_fmla_cnct(cnct_op::Or, equal, less);
    EXPECT_EQ(false, _and.val());
    EXPECT_EQ(true, _or.val());

    // Negation constructors
    fmla neg_false = mk_fmla_neg(_and);
    fmla neg_true = mk_fmla_neg(_or);
    EXPECT_EQ(true, neg_false.val());
    EXPECT_EQ(false, neg_true.val());

    // Quantifier constructors
    /***** TODO(jichaos) *****/

    // Custom formula constructors
    set_fmla("uninitiated");
    set_fmla("fmla", neg_true);
    EXPECT_EQ(neg_true.raw() , fmla_lookup("fmla").raw());
    EXPECT_NE(neg_false.raw() , fmla_lookup("fmla").raw());
    EXPECT_ANY_THROW(fmla_lookup("uninitiated"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
