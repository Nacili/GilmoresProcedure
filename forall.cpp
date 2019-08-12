#include "forall.h"

Forall::Forall(const Variable &var, const Formula &f)
    : Quantifier (var, f)
{
}

std::ostream &Forall::print(std::ostream &out) const
{
    return printImpl(out, "V");
}

Formula Forall::substitute(const Variable &v, const Term &t) const
{
    return substituteImpl<Forall>(v, t);
}

bool Forall::eval(const LStructure &structure, const Valuation &valuation) const
{
    Valuation cpyValuation = valuation;
    std::vector<AnyType> domainValues = structure.getDomain()->getValues();
    for (const AnyType &val : domainValues)
    {
        cpyValuation.setValue(m_var, val);
        if (!m_op->eval(structure, cpyValuation))
        {
            return false;
        }
    }
    
    return true;
}

Formula Forall::simplify() const
{
    Formula sop = m_op->simplify();
    if (sop->hasVariable(m_var, true))
    {
        return std::make_shared<Forall>(m_var, sop);
    }
    else
    {
        return sop;
    }
}

Formula Forall::nnf() const
{
    return std::make_shared<Forall>(m_var, m_op->nnf());
}

Formula Forall::prenex() const
{
    return std::make_shared<Forall>(m_var, m_op->prenex());
}

Formula Forall::skolem(Signature::Sptr s, VariablesSet &&vars) const
{
    vars.insert(m_var);
    return std::make_shared<Forall>(m_var, m_op->skolem(s, std::move(vars)));
}
