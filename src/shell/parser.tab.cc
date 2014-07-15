/* A Bison parser, made by GNU Bison 2.7.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* First part of user declarations.  */

/* Line 279 of lalr1.cc  */
#line 38 "parser.tab.cc"


#include "parser.tab.hh"

/* User implementation prologue.  */

/* Line 285 of lalr1.cc  */
#line 46 "parser.tab.cc"
/* Unqualified %code blocks.  */
/* Line 286 of lalr1.cc  */
#line 24 "parser.yy"

    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include "driver.h"

    enum term_type { Real, Int };
    enum func_op { Add, Sub, Mult, Div, Neg, Pow };
    enum equality_op { EQ, GT, LT, GTE, LTE };
    enum cnct_type { And, Or, Implies };
    enum quant_type { Forall, Exists };


    static int yylex(shell::parser::semantic_type *yylval,
                    shell::scanner  &scanner,
                    shell::driver   &driver);


/* Line 286 of lalr1.cc  */
#line 69 "parser.tab.cc"


# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location) YYUSE(Type)
# define YY_REDUCE_PRINT(Rule)        static_cast<void>(0)
# define YY_STACK_PRINT()             static_cast<void>(0)

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

/* Line 353 of lalr1.cc  */
#line 8 "parser.yy"
namespace shell {
/* Line 353 of lalr1.cc  */
#line 165 "parser.tab.cc"

  /// Build a parser object.
  parser::parser (class scanner  &scanner_yyarg, class driver  &driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {
  }

  parser::~parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    std::ostream& yyo = debug_stream ();
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
        case 18: /* define */
/* Line 455 of lalr1.cc  */
#line 83 "parser.yy"
        { if (((*yyvaluep).str))  { delete (((*yyvaluep).str)); (((*yyvaluep).str)) = nullptr; } };
/* Line 455 of lalr1.cc  */
#line 235 "parser.tab.cc"
        break;
      case 23: /* var */
/* Line 455 of lalr1.cc  */
#line 83 "parser.yy"
        { if (((*yyvaluep).str))  { delete (((*yyvaluep).str)); (((*yyvaluep).str)) = nullptr; } };
/* Line 455 of lalr1.cc  */
#line 242 "parser.tab.cc"
        break;

	default:
	  break;
      }
  }

  void
  parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  inline bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    // State.
    int yyn;
    int yylen = 0;
    int yystate = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    static semantic_type yyval_default;
    semantic_type yylval = yyval_default;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
        YYCDEBUG << "Reading a token: ";
        yychar = yylex (&yylval, scanner, driver);
      }

    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yy_table_value_is_error_ (yyn))
	  goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    // Compute the default @$.
    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }

    // Perform the reduction.
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
          case 4:
/* Line 670 of lalr1.cc  */
#line 91 "parser.yy"
    { ; }
    break;

  case 5:
/* Line 670 of lalr1.cc  */
#line 92 "parser.yy"
    { ; }
    break;

  case 6:
/* Line 670 of lalr1.cc  */
#line 93 "parser.yy"
    { driver.eval_fmla(*(yysemantic_stack_[(2) - (1)].str)); }
    break;

  case 7:
/* Line 670 of lalr1.cc  */
#line 94 "parser.yy"
    { driver.eval_fmla(*(yysemantic_stack_[(5) - (1)].str)); driver.var_pop(); }
    break;

  case 8:
/* Line 670 of lalr1.cc  */
#line 95 "parser.yy"
    { driver.print_exp((yysemantic_stack_[(2) - (1)].ptr)); }
    break;

  case 9:
/* Line 670 of lalr1.cc  */
#line 96 "parser.yy"
    { driver.print_fmla((yysemantic_stack_[(2) - (1)].ptr)); }
    break;

  case 10:
/* Line 670 of lalr1.cc  */
#line 97 "parser.yy"
    { exit(0); }
    break;

  case 11:
/* Line 670 of lalr1.cc  */
#line 98 "parser.yy"
    { driver.print_exp((yysemantic_stack_[(3) - (2)].ptr)); }
    break;

  case 12:
/* Line 670 of lalr1.cc  */
#line 99 "parser.yy"
    { driver.print_env(); }
    break;

  case 13:
/* Line 670 of lalr1.cc  */
#line 102 "parser.yy"
    { (yyval.ptr) = driver.mk_fmla_eq(EQ,(yysemantic_stack_[(3) - (1)].ptr),(yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 14:
/* Line 670 of lalr1.cc  */
#line 103 "parser.yy"
    { (yyval.ptr) = driver.mk_fmla_eq(GT,(yysemantic_stack_[(3) - (1)].ptr),(yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 15:
/* Line 670 of lalr1.cc  */
#line 104 "parser.yy"
    { (yyval.ptr) = driver.mk_fmla_eq(LT,(yysemantic_stack_[(3) - (1)].ptr),(yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 16:
/* Line 670 of lalr1.cc  */
#line 105 "parser.yy"
    { (yyval.ptr) = driver.mk_fmla_eq(GTE,(yysemantic_stack_[(3) - (1)].ptr),(yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 17:
/* Line 670 of lalr1.cc  */
#line 106 "parser.yy"
    { (yyval.ptr) = driver.mk_fmla_eq(LTE,(yysemantic_stack_[(3) - (1)].ptr),(yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 18:
/* Line 670 of lalr1.cc  */
#line 107 "parser.yy"
    { (yyval.ptr) = (yysemantic_stack_[(3) - (2)].ptr); }
    break;

  case 20:
/* Line 670 of lalr1.cc  */
#line 111 "parser.yy"
    { (yyval.ptr) = driver.mk_fmla_neg((yysemantic_stack_[(2) - (2)].ptr)); }
    break;

  case 21:
/* Line 670 of lalr1.cc  */
#line 112 "parser.yy"
    { (yyval.ptr) = driver.mk_fmla_cnct(And, (yysemantic_stack_[(3) - (1)].ptr), (yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 22:
/* Line 670 of lalr1.cc  */
#line 113 "parser.yy"
    { (yyval.ptr) = driver.mk_fmla_cnct(Or, (yysemantic_stack_[(3) - (1)].ptr), (yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 23:
/* Line 670 of lalr1.cc  */
#line 114 "parser.yy"
    { (yyval.ptr) = driver.mk_fmla_cnct(Implies, (yysemantic_stack_[(3) - (1)].ptr), (yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 24:
/* Line 670 of lalr1.cc  */
#line 115 "parser.yy"
    { (yyval.ptr) = driver.mk_fmla_quant(Forall, *(yysemantic_stack_[(3) - (2)].str), (yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 25:
/* Line 670 of lalr1.cc  */
#line 116 "parser.yy"
    { (yyval.ptr) = driver.mk_fmla_quant(Exists, *(yysemantic_stack_[(3) - (2)].str), (yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 26:
/* Line 670 of lalr1.cc  */
#line 117 "parser.yy"
    { (yyval.ptr) = (yysemantic_stack_[(3) - (2)].ptr); }
    break;

  case 27:
/* Line 670 of lalr1.cc  */
#line 120 "parser.yy"
    { driver.set_var(*(yysemantic_stack_[(3) - (1)].str), (yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 28:
/* Line 670 of lalr1.cc  */
#line 121 "parser.yy"
    { driver.mk_var(*(yysemantic_stack_[(2) - (2)].str), Real); }
    break;

  case 29:
/* Line 670 of lalr1.cc  */
#line 122 "parser.yy"
    { driver.mk_var(*(yysemantic_stack_[(2) - (2)].str), Int); }
    break;

  case 30:
/* Line 670 of lalr1.cc  */
#line 123 "parser.yy"
    { driver.set_fmla(*(yysemantic_stack_[(2) - (2)].str)); }
    break;

  case 31:
/* Line 670 of lalr1.cc  */
#line 124 "parser.yy"
    { driver.set_fmla(*(yysemantic_stack_[(3) - (1)].str),(yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 32:
/* Line 670 of lalr1.cc  */
#line 125 "parser.yy"
    { driver.error("Not a valid formula"); }
    break;

  case 33:
/* Line 670 of lalr1.cc  */
#line 128 "parser.yy"
    { driver.var_push(); driver.set_var(*(yysemantic_stack_[(3) - (1)].str), (yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 34:
/* Line 670 of lalr1.cc  */
#line 129 "parser.yy"
    { driver.set_var(*(yysemantic_stack_[(5) - (3)].str), (yysemantic_stack_[(5) - (5)].ptr)); }
    break;

  case 36:
/* Line 670 of lalr1.cc  */
#line 133 "parser.yy"
    { (yyval.ptr) = driver.mk_func(Neg, (yysemantic_stack_[(2) - (2)].ptr)); }
    break;

  case 37:
/* Line 670 of lalr1.cc  */
#line 134 "parser.yy"
    { (yyval.ptr) = driver.mk_func(Add, (yysemantic_stack_[(3) - (1)].ptr), (yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 38:
/* Line 670 of lalr1.cc  */
#line 135 "parser.yy"
    { (yyval.ptr) = driver.mk_func(Sub, (yysemantic_stack_[(3) - (1)].ptr), (yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 39:
/* Line 670 of lalr1.cc  */
#line 136 "parser.yy"
    { (yyval.ptr) = driver.mk_func(Mult, (yysemantic_stack_[(3) - (1)].ptr), (yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 40:
/* Line 670 of lalr1.cc  */
#line 137 "parser.yy"
    { (yyval.ptr) = driver.mk_func(Div, (yysemantic_stack_[(3) - (1)].ptr), (yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 41:
/* Line 670 of lalr1.cc  */
#line 138 "parser.yy"
    { (yyval.ptr) = driver.mk_func(Pow, (yysemantic_stack_[(3) - (1)].ptr), (yysemantic_stack_[(3) - (3)].ptr)); }
    break;

  case 42:
/* Line 670 of lalr1.cc  */
#line 139 "parser.yy"
    { (yyval.ptr) = (yysemantic_stack_[(3) - (2)].ptr); }
    break;

  case 43:
/* Line 670 of lalr1.cc  */
#line 142 "parser.yy"
    { (yyval.ptr) = driver.mk_const((yysemantic_stack_[(1) - (1)].num)); }
    break;

  case 44:
/* Line 670 of lalr1.cc  */
#line 143 "parser.yy"
    { (yyval.ptr) = driver.mk_var(*(yysemantic_stack_[(1) - (1)].str)); }
    break;


/* Line 670 of lalr1.cc  */
#line 687 "parser.tab.cc"
      default:
        break;
      }

    /* User semantic actions sometimes alter yychar, and that requires
       that yytoken be updated with the new translation.  We take the
       approach of translating immediately before every use of yytoken.
       One alternative is translating here after every semantic action,
       but that translation would be missed if the semantic action
       invokes YYABORT, YYACCEPT, or YYERROR immediately after altering
       yychar.  In the case of YYABORT or YYACCEPT, an incorrect
       destructor might then be invoked immediately.  In the case of
       YYERROR, subsequent parser actions might lead to an incorrect
       destructor call or verbose syntax error message before the
       lookahead is translated.  */
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yytranslate_ (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	if (yychar == yyempty_)
	  yytoken = yyempty_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[1] = yylloc;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */
        if (yychar <= yyeof_)
          {
            /* Return failure if at end of input.  */
            if (yychar == yyeof_)
              YYABORT;
          }
        else
          {
            yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
            yychar = yyempty_;
          }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[1] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (!yy_pact_value_is_default_ (yyn))
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	  YYABORT;

	yyerror_range[1] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[2] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      {
        /* Make sure we have latest lookahead translation.  See comments
           at user semantic actions for why this is necessary.  */
        yytoken = yytranslate_ (yychar);
        yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval,
                     &yylloc);
      }

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystate_stack_.height ())
      {
        yydestruct_ ("Cleanup: popping",
                     yystos_[yystate_stack_[0]],
                     &yysemantic_stack_[0],
                     &yylocation_stack_[0]);
        yypop_ ();
      }

    return yyresult;
    }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (yychar != yyempty_)
          {
            /* Make sure we have latest lookahead translation.  See
               comments at user semantic actions for why this is
               necessary.  */
            yytoken = yytranslate_ (yychar);
            yydestruct_ (YY_NULL, yytoken, &yylval, &yylloc);
          }

        while (1 < yystate_stack_.height ())
          {
            yydestruct_ (YY_NULL,
                         yystos_[yystate_stack_[0]],
                         &yysemantic_stack_[0],
                         &yylocation_stack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (int, int)
  {
    return YY_("syntax error");
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char parser::yypact_ninf_ = -32;
  const short int
  parser::yypact_[] =
  {
       142,   -18,   -17,    -6,   -13,   -12,    -5,    43,     8,    10,
     -32,     6,    43,   -32,    -6,    57,   -32,   -32,    34,    29,
      86,   -32,   -32,   -32,   -32,    20,   124,    -6,    -6,   -32,
      43,    79,   -32,   -32,    31,    -6,    43,    28,    37,     9,
      93,   -32,   -32,    -6,    -6,    -6,   -32,   -32,    43,    43,
      43,    43,    43,    43,    43,    43,    43,   -32,    43,    20,
      20,   112,   -32,    47,    20,   124,   144,   -32,   -32,   -32,
      20,    20,    20,   144,   144,   144,   144,   144,     2,     2,
      28,    28,   144,    42,   -31,    43,   -32,    58,   144,    50,
      43,   144
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  parser::yydefact_[] =
  {
         0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      43,    44,     0,     4,     0,     0,     2,    19,     0,     0,
       0,    35,    28,    29,    44,    20,     0,     0,     0,    30,
       0,     0,    12,    10,     6,     0,     0,    36,    19,     0,
       0,     1,     3,     0,     0,     0,     9,     5,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     8,     0,    24,
      25,     0,    11,     0,    31,    32,    27,    18,    26,    42,
      21,    22,    23,    14,    15,    16,    17,    13,    37,    38,
      39,    40,    41,     0,     0,     0,     7,     0,    33,     0,
       0,    34
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  parser::yypgoto_[] =
  {
       -32,   -32,    69,    72,    -1,   -32,   -32,     0,   -32
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  parser::yydefgoto_[] =
  {
        -1,    15,    16,    17,    18,    19,    84,    26,    21
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char parser::yytable_ninf_ = -1;
  const unsigned char
  parser::yytable_[] =
  {
        20,    86,    25,    87,     3,    22,    23,    31,     4,     5,
      27,    28,    37,    39,    40,    20,    10,    24,    29,    12,
      43,    44,    45,    34,    35,    14,    59,    60,    55,    56,
      61,    43,    44,    45,    64,    65,    66,    58,    32,    36,
      33,    68,    70,    71,    72,    43,    44,    45,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    41,    82,    47,
       1,     2,    63,    58,    46,    10,    24,     3,    12,    67,
      83,     4,     5,     6,    30,    85,     7,     8,     9,    10,
      11,    89,    12,    90,    42,    88,    38,    13,    14,     0,
      91,    48,    49,    50,    51,    52,     0,     0,    48,    49,
      50,    51,    52,    53,    54,    55,    56,     0,     0,    62,
      53,    54,    55,    56,    58,     0,    57,    53,    54,    55,
      56,    58,     0,     0,     0,    69,     0,     0,    58,    48,
      49,    50,    51,    52,     0,     0,    53,    54,    55,    56,
       0,     0,     0,     0,    69,     1,     2,    58,    53,    54,
      55,    56,     3,     0,     0,     0,     4,     5,     6,    58,
       0,     7,     8,     9,    10,    11,     0,    12,    53,    54,
      55,    56,    13,    14,     0,     0,     0,     0,     0,    58
  };

  /* YYCHECK.  */
  const signed char
  parser::yycheck_[] =
  {
         0,    32,     3,    34,    10,    23,    23,     7,    14,    15,
      23,    23,    12,    14,    14,    15,    22,    23,    23,    25,
      11,    12,    13,    17,    18,    31,    27,    28,    26,    27,
      30,    11,    12,    13,    35,    35,    36,    35,    30,    33,
      30,    32,    43,    44,    45,    11,    12,    13,    48,    49,
      50,    51,    52,    53,    54,    55,    56,     0,    58,    30,
       3,     4,    31,    35,    30,    22,    23,    10,    25,    32,
      23,    14,    15,    16,    31,    33,    19,    20,    21,    22,
      23,    23,    25,    33,    15,    85,    14,    30,    31,    -1,
      90,     5,     6,     7,     8,     9,    -1,    -1,     5,     6,
       7,     8,     9,    24,    25,    26,    27,    -1,    -1,    30,
      24,    25,    26,    27,    35,    -1,    30,    24,    25,    26,
      27,    35,    -1,    -1,    -1,    32,    -1,    -1,    35,     5,
       6,     7,     8,     9,    -1,    -1,    24,    25,    26,    27,
      -1,    -1,    -1,    -1,    32,     3,     4,    35,    24,    25,
      26,    27,    10,    -1,    -1,    -1,    14,    15,    16,    35,
      -1,    19,    20,    21,    22,    23,    -1,    25,    24,    25,
      26,    27,    30,    31,    -1,    -1,    -1,    -1,    -1,    35
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  parser::yystos_[] =
  {
         0,     3,     4,    10,    14,    15,    16,    19,    20,    21,
      22,    23,    25,    30,    31,    37,    38,    39,    40,    41,
      43,    44,    23,    23,    23,    40,    43,    23,    23,    23,
      31,    43,    30,    30,    17,    18,    33,    43,    39,    40,
      43,     0,    38,    11,    12,    13,    30,    30,     5,     6,
       7,     8,     9,    24,    25,    26,    27,    30,    35,    40,
      40,    43,    30,    31,    40,    43,    43,    32,    32,    32,
      40,    40,    40,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    23,    42,    33,    32,    34,    43,    23,
      33,    43
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,    43,    45,    42,    47,   279,   280,
      10,    40,    41,    61,    44,    94
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  parser::yyr1_[] =
  {
         0,    36,    37,    37,    38,    38,    38,    38,    38,    38,
      38,    38,    38,    39,    39,    39,    39,    39,    39,    40,
      40,    40,    40,    40,    40,    40,    40,    41,    41,    41,
      41,    41,    41,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    44,    44
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  parser::yyr2_[] =
  {
         0,     2,     1,     2,     1,     2,     2,     5,     2,     2,
       2,     3,     2,     3,     3,     3,     3,     3,     3,     1,
       2,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     3,     3,     3,     5,     1,     2,     3,     3,     3,
       3,     3,     3,     1,     1
  };

#if YYDEBUG
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const parser::yytname_[] =
  {
    "$end", "error", "$undefined", "realnum", "intnum", "GT", "LT", "GTE",
  "LTE", "EQ", "t_not", "t_and", "t_or", "implies", "forall", "exists",
  "formula", "eval", "define", "print", "printenv", "quit", "number",
  "var", "'+'", "'-'", "'*'", "'/'", "UMINUS", "UNOT", "'\\n'", "'('",
  "')'", "'='", "','", "'^'", "$accept", "line", "stmt", "eq_op", "lgc",
  "assignment", "tmp_var", "exp", "term", YY_NULL
  };


  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const parser::rhs_number_type
  parser::yyrhs_[] =
  {
        37,     0,    -1,    38,    -1,    37,    38,    -1,    30,    -1,
      41,    30,    -1,    23,    17,    -1,    23,    17,    31,    42,
      32,    -1,    43,    30,    -1,    40,    30,    -1,    21,    30,
      -1,    19,    43,    30,    -1,    20,    30,    -1,    43,     9,
      43,    -1,    43,     5,    43,    -1,    43,     6,    43,    -1,
      43,     7,    43,    -1,    43,     8,    43,    -1,    31,    39,
      32,    -1,    39,    -1,    10,    40,    -1,    40,    11,    40,
      -1,    40,    12,    40,    -1,    40,    13,    40,    -1,    14,
      23,    40,    -1,    15,    23,    40,    -1,    31,    40,    32,
      -1,    23,    33,    43,    -1,     3,    23,    -1,     4,    23,
      -1,    16,    23,    -1,    23,    18,    40,    -1,    23,    18,
      43,    -1,    23,    33,    43,    -1,    42,    34,    23,    33,
      43,    -1,    44,    -1,    25,    43,    -1,    43,    24,    43,
      -1,    43,    25,    43,    -1,    43,    26,    43,    -1,    43,
      27,    43,    -1,    43,    35,    43,    -1,    31,    43,    32,
      -1,    22,    -1,    23,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  parser::yyprhs_[] =
  {
         0,     0,     3,     5,     8,    10,    13,    16,    22,    25,
      28,    31,    35,    38,    42,    46,    50,    54,    58,    62,
      64,    67,    71,    75,    79,    83,    87,    91,    95,    98,
     101,   104,   108,   112,   116,   122,   124,   127,   131,   135,
     139,   143,   147,   151,   153
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned char
  parser::yyrline_[] =
  {
         0,    87,    87,    88,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   102,   103,   104,   105,   106,   107,   110,
     111,   112,   113,   114,   115,   116,   117,   120,   121,   122,
     123,   124,   125,   128,   129,   132,   133,   134,   135,   136,
     137,   138,   139,   142,   143
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      30,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      31,    32,    26,    24,    34,    25,     2,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    33,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    35,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    28,
      29
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int parser::yyeof_ = 0;
  const int parser::yylast_ = 179;
  const int parser::yynnts_ = 9;
  const int parser::yyempty_ = -2;
  const int parser::yyfinal_ = 41;
  const int parser::yyterror_ = 1;
  const int parser::yyerrcode_ = 256;
  const int parser::yyntokens_ = 36;

  const unsigned int parser::yyuser_token_number_max_ = 280;
  const parser::token_number_type parser::yyundef_token_ = 2;

/* Line 1141 of lalr1.cc  */
#line 8 "parser.yy"
} // shell
/* Line 1141 of lalr1.cc  */
#line 1199 "parser.tab.cc"
/* Line 1142 of lalr1.cc  */
#line 147 "parser.yy"


// C++ Code:

void 
shell::parser::error( const shell::parser::location_type &l,
                      const std::string &err_message )
{
   std::cerr << "Error: " << err_message << "\n"; 
}

#include "scanner.h"

static int yylex( shell::parser::semantic_type *yylval,
                  shell::scanner  &scanner,
                  shell::driver   &driver ){
   return(scanner.yylex(yylval));
}
