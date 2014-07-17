add_executable(tst_formula formula.cpp)
target_link_libraries(tst_formula formula gtest)
add_test(tst_formula ${CMAKE_CURRENT_BINARY_DIR}/tst_formula)
