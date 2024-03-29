#ifndef FUNCTIONTERM_H
#define FUNCTIONTERM_H

#include "base_term.h"
#include "signature.h"

#include <vector>

class FunctionTerm : public BaseTerm
{
public:
    FunctionTerm(Signature::Sptr signature, const FunctionSymbol &symbol, const std::vector<Term> &terms = {});
    
    inline const FunctionSymbol& symbol() const { return m_symbol; }
    
    inline const std::vector<Term>& operands() const { return m_terms; }
    
    virtual std::ostream& print(std::ostream &out) const;
    
    virtual bool equalTo(const Term &oth) const;
    
    virtual void getVariables(VariablesSet &vset) const;
    
    virtual bool hasVariable(const Variable &v) const;
    
    virtual Term substitute(const Variable &v, const Term &t) const;
    
    virtual Term substitute(const Substitution &s) const;
    
    virtual AnyType eval(const LStructure &structure, const Valuation &valuation) const;

    virtual void getConstants(ConstantSet & cs) const;

    virtual void getFunctions(FunctionSet & fs) const;
private:
    /**
     * @brief m_signature je signatura kojoj funkcijski simbol pripada
     */
    Signature::Sptr m_signature;
    /**
     * @brief m_symbol je funkcijski simbol, na primer "+"
     */
    FunctionSymbol m_symbol;
    /**
     * @brief m_terms je vektor operanada, na primer funkcijski term arnosti 3 ima vektor duzine 3
     */
    std::vector<Term> m_terms; 
};

#endif // FUNCTIONTERM_H
