#ifndef BASEFORMULA_H
#define BASEFORMULA_H

#include "common.h"
#include "base_term.h"

#include <iostream>
#include <memory>

class BaseFormula;

using Formula = std::shared_ptr<BaseFormula>;

typedef std::vector<Formula> LiteralList;
typedef std::vector<LiteralList> LiteralListList;

LiteralListList makePairs(const LiteralListList & c1, const LiteralListList & c2);

class BaseFormula : public std::enable_shared_from_this<BaseFormula>
{
public:
    BaseFormula();
    
    virtual ~BaseFormula();
    
    virtual std::ostream& print(std::ostream & out) const = 0;
    
    virtual unsigned complexity() const = 0;
  
    virtual bool equalTo(const Formula & f) const;
  
    virtual void getVars(VariablesSet & vars, bool free = false) const = 0;

    virtual void getConstants(ConstantSet & cts) const = 0;

    virtual void getFunctions(FunctionSet & fs) const = 0;
  
    bool hasVariable(const Variable & v, bool free = false) const;
  
    virtual bool eval(const LStructure &structure, const Valuation &valuation) const = 0;
  
    virtual Formula substitute(const Variable & v, const Term & t) const = 0;
    
    virtual Formula substitute(const Substitution &s) const;
    
    virtual Formula simplify() const;
    
    virtual Formula nnf() const;
    
    virtual Formula pullQuantifiers() const;
    
    virtual Formula prenex() const;
    
    virtual Formula skolem(Signature::Sptr s, VariablesSet &&vars = {}) const;

    Formula removeUniversalQ(const Formula & f);

    virtual LiteralListList listDNF() = 0;
    
    template <typename Derived>
    static inline const Derived* isOfType(const Formula &f)
    {
        return dynamic_cast<const Derived*>(f.get());
    }
    
};


std::ostream& operator<<(std::ostream &out, const Formula &f);

#endif // BASEFORMULA_H
