#ifndef ATOMIC_FORMULA_H
#define ATOMIC_FORMULA_H

#include "base_formula.h"


class AtomicFormula : public BaseFormula
{
public:
    AtomicFormula();


    // BaseFormula interface
public:
    unsigned complexity() const;
    void getVars(VariablesSet &vars, bool free) const;
    // virtual void getConstants(ConstantSet & cts) const;
    // virtual void getFunctions(FunctionSet & fs) const;
    Formula substitute(const Variable &v, const Term &t) const;
    virtual Formula nnf() const;
    virtual Formula prenex();
    virtual Formula pullQuantifiers();
};

#endif // ATOMIC_FORMULA_H
