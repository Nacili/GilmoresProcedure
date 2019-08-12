#ifndef IMP_H
#define IMP_H

#include "binary_connective.h"

class Imp : public BinaryConnective
{
public:
    Imp(const Formula &op1, const Formula &op2);
    
    virtual std::ostream& print(std::ostream & out) const;
    
    virtual Formula substitute(const Variable & v, const Term & t) const;
    
    virtual bool eval(const LStructure &structure, const Valuation &valuation) const;
    
    virtual Formula simplify() const;
    
    virtual Formula nnf() const;
};

#endif // IMP_H
