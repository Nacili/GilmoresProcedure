#include "exists.h"
#include "function_term.h"

#include <algorithm>
#include <iterator>

Exists::Exists(const Variable &var, const Formula &f)
    : Quantifier (var, f)
{
}

Formula Exists::substitute(const Variable &v, const Term &t) const
{
    return substituteImpl<Exists>(v, t);
}

std::ostream &Exists::print(std::ostream &out) const
{
    return printImpl(out, "E");
}

bool Exists::eval(const LStructure &structure, const Valuation &valuation) const
{
    Valuation cpyValuation = valuation;
    std::vector<AnyType> domainValues = structure.getDomain()->getValues();
    for (const AnyType &val : domainValues)
    {
        cpyValuation.setValue(m_var, val);
        if (m_op->eval(structure, cpyValuation))
        {
            return true;
        }
    }
    
    return false;
}

Formula Exists::simplify() const
{
    Formula sop = m_op->simplify();
    if (sop->hasVariable(m_var, true))
    {
        return std::make_shared<Exists>(m_var, sop);
    }
    else
    {
        return sop;
    }
}

Formula Exists::nnf() const
{
    return std::make_shared<Exists>(m_var, m_op->nnf());
}

Formula Exists::prenex() const
{
    return std::make_shared<Exists>(m_var, m_op->prenex());
}

Formula Exists::skolem(Signature::Sptr s, VariablesSet &&vars) const
{
    FunctionSymbol replacementSymbol = s->getUniqueFunctionSymbol();
    s->addFunctionSymbol(replacementSymbol, vars.size());
    std::vector<Term> terms;
    terms.reserve(vars.size());
    std::transform(vars.cbegin(), vars.cend(), std::back_inserter(terms), [&](const Variable &var)
    {
        return std::make_shared<VariableTerm>(var);
    });
    
    return m_op->substitute(m_var, std::make_shared<FunctionTerm>(s, replacementSymbol, terms))->skolem(s, std::move(vars));
}
