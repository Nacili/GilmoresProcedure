#include "imp.h"
#include "constants.h"
#include "not.h"
#include "or.h"

Imp::Imp(const Formula &op1, const Formula &op2)
    : BinaryConnective (op1, op2)
{
    
}

std::ostream &Imp::print(std::ostream &out) const
{
    return printImpl(out, "=>");
}

Formula Imp::substitute(const Variable &v, const Term &t) const
{
    return substituteImpl<Imp>(v, t);
}

Formula Imp::substitute(const Substitution &s) const
{
    return std::make_shared<Imp>(m_op1->substitute(s), m_op2->substitute(s));
}

bool Imp::eval(const LStructure &structure, const Valuation &valuation) const
{
    return !m_op1->eval(structure, valuation) || m_op2->eval(structure, valuation);
}

Formula Imp::simplify() const
{
    Formula sop1 = m_op1->simplify();
    Formula sop2 = m_op2->simplify();
    if (BaseFormula::isOfType<True>(sop1))
    {
        return sop2;
    }
    else if (BaseFormula::isOfType<False>(sop1) || BaseFormula::isOfType<True>(sop2))
    {
        return std::make_shared<True>();
    }
    else if (BaseFormula::isOfType<False>(sop2))
    {
        return std::make_shared<Not>(sop1)->simplify();
    }
    else
    {
        return std::make_shared<Imp>(sop1, sop2);
    }
}

Formula Imp::nnf() const
{
    GET_OPERANDS(op1, op2);
    return std::make_shared<Or>(std::make_shared<Not>(op1)->nnf(), op2->nnf());
}


LiteralListList Imp::listDNF()
{
    throw std::runtime_error("You can't use DNF with IMP");
}
