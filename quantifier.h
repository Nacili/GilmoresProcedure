#ifndef QUANTIFIER_H
#define QUANTIFIER_H

#include <cstdint>

#include "base_formula.h"
#include "common.h"
#include "variable_term.h"

class Quantifier : public BaseFormula
{
private:
    static uint64_t s_UniqueCounter;
    
public:
    Quantifier(const Variable &var, const Formula &f);
    
    virtual unsigned complexity() const;
    
    virtual bool equalTo(const Formula & f) const;
    
    virtual void getVars(VariablesSet & vars, bool free = false) const;
    
    inline Formula operand() const { return m_op; }
    
    inline Variable variable() const { return m_var; }
    
    /**
     * @brief getUniqueVarName - vraca promenljivu koja se ne nalazi ni u formuli ni u termu
     * 
     * @details Koristi se prilikom zamene promeljive termom, kada term kojim se menja sadrzi
     * promenljivu koja se javlja kvantifikovana (vezana) u formuli.
     * @param f - formula
     * @param t - term
     * @return jedinstvena promenljiva
     */
    template <typename T1, typename T2>
    static Variable getUniqueVarName(const T1 &t1, const T2 &t2);
    
protected:
    std::ostream& printImpl(std::ostream & out, const std::string &symbol) const;
    
    template <typename Derived>
    Formula substituteImpl(const Variable & v, const Term & t) const;
    
protected:
    /**
     * @brief m_var je kvatifikovana promenljiva
     */
    Variable m_var;
    /**
     * @brief m_op je potformula na koju se kvantor primenjuje
     */
    Formula m_op;
};

template <typename T1, typename T2>
Variable Quantifier::getUniqueVarName(const T1 &t1, const T2 &t2)
{
    Variable unique;
    do {
      unique = "uv" + std::to_string(s_UniqueCounter++);
    } while (t1->hasVariable(unique) || t2->hasVariable(unique));
    return unique;
}

template <typename Derived>
Formula Quantifier::substituteImpl(const Variable &v, const Term &t) const
{
    /* ako je promenljiva koja se menja jednaka kvantifikovanoj ignorisemo zamenu */
    if (v == m_var)
    {
        return std::const_pointer_cast<BaseFormula>(shared_from_this());
    }
    else
    {
        /* ako term sadrzi kvantifikovanu promenljivu moramo je preimenovati u potformuli */
        if (t->hasVariable(m_var))
        {
            Variable rename = getUniqueVarName(std::const_pointer_cast<BaseFormula>(shared_from_this()), t);
            Formula renamedOp = m_op->substitute(m_var, std::make_shared<VariableTerm>(rename));
            return std::make_shared<Derived>(rename, renamedOp->substitute(v, t));
        }
        else
        {
            /* u suprotnom zamena se izvrsava na uobicajen nacin */
            return std::make_shared<Derived>(m_var, m_op->substitute(v, t));
        }
    }
}

#endif // QUANTIFIER_H
