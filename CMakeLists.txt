include_directories(${CMAKE_CURRENT_LIST_DIR})

add_executable(Proba ${CMAKE_CURRENT_LIST_DIR}/main.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/common.h
                 ${CMAKE_CURRENT_LIST_DIR}/base_term.h
                 ${CMAKE_CURRENT_LIST_DIR}/base_term.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/signature.h
                 ${CMAKE_CURRENT_LIST_DIR}/signature.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/variable_term.h
                 ${CMAKE_CURRENT_LIST_DIR}/variable_term.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/function_term.h
                 ${CMAKE_CURRENT_LIST_DIR}/function_term.cpp

                 ${CMAKE_CURRENT_LIST_DIR}/base_formula.h
                 ${CMAKE_CURRENT_LIST_DIR}/base_formula.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/atomic_formula.h
                 ${CMAKE_CURRENT_LIST_DIR}/atomic_formula.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/atom.h
                 ${CMAKE_CURRENT_LIST_DIR}/atom.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/constants.h
                 ${CMAKE_CURRENT_LIST_DIR}/constants.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/unary_connective.h
                 ${CMAKE_CURRENT_LIST_DIR}/unary_connective.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/not.h
                 ${CMAKE_CURRENT_LIST_DIR}/not.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/binary_connective.h
                 ${CMAKE_CURRENT_LIST_DIR}/binary_connective.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/and.h
                 ${CMAKE_CURRENT_LIST_DIR}/and.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/or.h
                 ${CMAKE_CURRENT_LIST_DIR}/or.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/imp.h
                 ${CMAKE_CURRENT_LIST_DIR}/imp.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/iff.h
                 ${CMAKE_CURRENT_LIST_DIR}/iff.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/quantifier.h
                 ${CMAKE_CURRENT_LIST_DIR}/quantifier.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/forall.h
                 ${CMAKE_CURRENT_LIST_DIR}/forall.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/exists.h
                 ${CMAKE_CURRENT_LIST_DIR}/exists.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/domain.h
                 ${CMAKE_CURRENT_LIST_DIR}/domain.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/valuation.h
                 ${CMAKE_CURRENT_LIST_DIR}/valuation.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/lstructure.h
                 ${CMAKE_CURRENT_LIST_DIR}/lstructure.cpp

                 ${CMAKE_CURRENT_LIST_DIR}/herbrand.h
                 ${CMAKE_CURRENT_LIST_DIR}/herbrand.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/first_order_logic.h
                 ${CMAKE_CURRENT_LIST_DIR}/gilmore.h
                 ${CMAKE_CURRENT_LIST_DIR}/gilmore.cpp
                 )
