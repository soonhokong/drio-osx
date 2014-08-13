add_library(formula function.cpp term.cpp atom.cpp connective.cpp quantifier.cpp formula.cpp var_scoped_env.cpp fmla_scoped_env.cpp expr.cpp)

target_link_libraries(formula SH_UTIL)