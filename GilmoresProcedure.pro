TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    signature.cpp \
    valuation.cpp \
    lstructure.cpp \
    base_term.cpp \
    variable_term.cpp \
    function_term.cpp \
    base_formula.cpp \
    atomic_formula.cpp \
    atom.cpp \
    constants.cpp \
    domain.cpp \
    quantifier.cpp \
    exists.cpp \
    forall.cpp \
    unary_connective.cpp \
    not.cpp \
    binary_connective.cpp \
    and.cpp \
    imp.cpp \
    or.cpp \
    iff.cpp

HEADERS += \
    signature.h \
    common.h \
    valuation.h \
    lstructure.h \
    base_term.h \
    variable_term.h \
    function_term.h \
    base_formula.h \
    atomic_formula.h \
    atom.h \
    constants.h \
    domain.h \
    quantifier.h \
    exists.h \
    forall.h \
    unary_connective.h \
    not.h \
    binary_connective.h \
    and.h \
    imp.h \
    or.h \
    iff.h \
    first_order_logic.h
