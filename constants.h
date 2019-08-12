#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "atomic_formula.h"

class True : public AtomicFormula
{
public:
    True();
    
    virtual std::ostream& print(std::ostream & out) const;
    
    virtual bool eval(const LStructure &structure, const Valuation &valuation) const;
};

class False : public AtomicFormula
{
public:
    False();
    
    virtual std::ostream& print(std::ostream & out) const;
    
    virtual bool eval(const LStructure &structure, const Valuation &valuation) const;
};

#endif // CONSTANTS_H
