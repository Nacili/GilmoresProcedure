#ifndef UNARYCONNECTIVE_H
#define UNARYCONNECTIVE_H

#include "base_formula.h"

class UnaryConnective : public BaseFormula
{
public:
    UnaryConnective(const Formula &f);
    
    Formula operand() const { return m_op; }
    
    virtual unsigned complexity() const;
  
    virtual bool equalTo(const Formula & f) const;
  
    virtual void getVars(VariablesSet & vars, bool free = false) const;

    virtual void getConstants(ConstantSet & cts) const;

    virtual void getFunctions(FunctionSet & fs) const;

protected:
    Formula m_op;
};

#endif // UNARYCONNECTIVE_H
