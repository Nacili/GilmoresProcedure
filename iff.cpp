#include "iff.h"
#include "constants.h"
#include "not.h"
#include "and.h"
#include "or.h"

Iff::Iff(const Formula &op1, const Formula &op2)
    : BinaryConnective (op1, op2)
{
}

std::ostream &Iff::print(std::ostream &out) const
{
    return printImpl(out, "<=>");
}

Formula Iff::substitute(const Variable &v, const Term &t) const
{
    return substituteImpl<Iff>(v, t);
}

bool Iff::eval(const LStructure &structure, const Valuation &valuation) const
{
    return m_op1->eval(structure, valuation) == m_op2->eval(structure, valuation);
}

Formula Iff::simplify() const
{
    Formula sop1 = m_op1->simplify();
    Formula sop2 = m_op2->simplify();
    if (BaseFormula::isOfType<True>(sop1))
    {
        return sop2;
    }
    else if (BaseFormula::isOfType<True>(sop2))
    {
        return sop1;
    }
    else if (BaseFormula::isOfType<False>(sop1))
    {
        return std::make_shared<Not>(sop2)->simplify();
    }
    else if (BaseFormula::isOfType<False>(sop2))
    {
        return std::make_shared<Not>(sop2)->simplify();
    }
    else 
    {
        return std::make_shared<Iff>(sop1, sop2);
    }
}

Formula Iff::nnf() const
{
    return std::make_shared<And>(
                std::make_shared<Or>(
                    std::make_shared<Not>(m_op1)->nnf(), 
                    m_op2->nnf()),
                std::make_shared<Or>(
                    m_op1->nnf(), 
                    std::make_shared<Not>(m_op2)->nnf()));
}
