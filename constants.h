#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "atomic_formula.h"

class True : public AtomicFormula
{
public:
    True();

    virtual std::ostream& print(std::ostream & out) const;
    virtual bool eval(const LStructure &structure, const Valuation &valuation) const;
    virtual void getConstants(ConstantSet & cts) const;
    virtual void getFunctions(FunctionSet & fs) const;
    LiteralListList listDNF();
};

class False : public AtomicFormula
{
public:
    False();

    virtual std::ostream& print(std::ostream & out) const;
    virtual void getConstants(ConstantSet & cts) const;
    virtual void getFunctions(FunctionSet & fs) const;
    virtual bool eval(const LStructure &structure, const Valuation &valuation) const;
    LiteralListList listDNF();
};

#endif // CONSTANTS_H
