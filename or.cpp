#include "or.h"
#include "constants.h"
#include "forall.h"
#include "exists.h"

Or::Or(const Formula &op1, const Formula &op2)
    : BinaryConnective (op1, op2)
{
    
}

std::ostream &Or::print(std::ostream &out) const
{
    return printImpl(out, "\\/");
}

Formula Or::substitute(const Variable &v, const Term &t) const
{
    return substituteImpl<Or>(v, t);
}

Formula Or::substitute(const Substitution &s) const
{
    return std::make_shared<Or>(m_op1->substitute(s), m_op2->substitute(s));
}

bool Or::eval(const LStructure &structure, const Valuation &valuation) const
{
    return m_op1->eval(structure, valuation) || m_op2->eval(structure, valuation);
}

Formula Or::simplify() const
{
    Formula sop1 = m_op1->simplify();
    Formula sop2 = m_op2->simplify();
    if (BaseFormula::isOfType<True>(sop1) || BaseFormula::isOfType<True>(sop2))
    {
        return std::make_shared<True>();
    }
    else if (BaseFormula::isOfType<False>(sop1))
    {
        return sop2;
    }
    else if (BaseFormula::isOfType<False>(sop2))
    {
        return sop1;
    }
    else
    {
        return std::make_shared<Or>(sop1, sop2);
    }
}

Formula Or::nnf() const
{
    GET_OPERANDS(op1, op2);
    return std::make_shared<Or>(op1->nnf(), op2->nnf());
}

Formula Or::pullQuantifiers() const
{
    const Exists *eop1 = BaseFormula::isOfType<Exists>(m_op1);
    const Exists *eop2 = BaseFormula::isOfType<Exists>(m_op2);
    if (eop1 && eop2)
    {
        if (eop1->variable() == eop2->variable())
        {
            return std::make_shared<Exists>(eop1->variable(), 
                                            std::make_shared<Or>(
                                                eop1->operand(),
                                                eop2->operand())->pullQuantifiers());
        }
        else
        {
            Variable renamed = Quantifier::getUniqueVarName(eop1->operand(), eop2->operand());
            return std::make_shared<Exists>(renamed,
                                            std::make_shared<Or>(
                                                eop1->operand()->substitute(eop1->variable(), std::make_shared<VariableTerm>(renamed)),
                                                eop2->operand()->substitute(eop2->variable(), std::make_shared<VariableTerm>(renamed))
                                                )->pullQuantifiers());
        }
    }
    else if (eop1)
    {
        if (m_op2->hasVariable(eop1->variable(), true))
        {
            Variable renamed = Quantifier::getUniqueVarName(eop1->operand(), m_op2);
            return std::make_shared<Exists>(renamed, std::make_shared<Or>(
                                                eop1->operand()->substitute(eop1->variable(), std::make_shared<VariableTerm>(renamed)), 
                                                m_op2)->pullQuantifiers());
        }
        else
        {
            return std::make_shared<Exists>(eop1->variable(), std::make_shared<Or>(
                                                eop1->operand(), m_op2)->pullQuantifiers());
        }
    }
    else if (eop2)
    {
        if (m_op1->hasVariable(eop2->variable(), true))
        {
            Variable renamed = Quantifier::getUniqueVarName(eop2->operand(), m_op1);
            return std::make_shared<Exists>(renamed,  std::make_shared<Or>(
                                                m_op1, 
                                                eop2->operand()->substitute(eop2->variable(), 
                                                                            std::make_shared<VariableTerm>(renamed))
                                                )->pullQuantifiers());
        }
        else
        {
            return std::make_shared<Exists>(eop2->variable(), std::make_shared<Or>(m_op1, eop2->operand())->pullQuantifiers());
        }
    }
    
    const Forall *fop1 = BaseFormula::isOfType<Forall>(m_op1);
    const Forall *fop2 = BaseFormula::isOfType<Forall>(m_op2);
    if (fop1)
    {
        if (m_op2->hasVariable(fop1->variable(), true))
        {
            Variable renamed = Quantifier::getUniqueVarName(fop1->operand(), m_op2);
            return std::make_shared<Forall>(renamed, std::make_shared<Or>(
                                                fop1->operand()->substitute(fop1->variable(), std::make_shared<VariableTerm>(renamed)), 
                                                m_op2)->pullQuantifiers());
        }
        else
        {
            return std::make_shared<Forall>(fop1->variable(), std::make_shared<Or>(
                                                fop1->operand(), m_op2)->pullQuantifiers());
        }
    }
    else if (fop2)
    {
        if (m_op1->hasVariable(fop2->variable(), true))
        {
            Variable renamed = Quantifier::getUniqueVarName(fop2->operand(), m_op1);
            return std::make_shared<Forall>(renamed,  std::make_shared<Or>(
                                                m_op1, 
                                                fop2->operand()->substitute(fop2->variable(), 
                                                                            std::make_shared<VariableTerm>(renamed))
                                                )->pullQuantifiers());
        }
        else
        {
            return std::make_shared<Forall>(fop2->variable(), std::make_shared<Or>(m_op1, fop2->operand())->pullQuantifiers());
        }
    }
    
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

Formula Or::prenex() const
{
    Formula pr_op1 = m_op1->prenex();
    Formula pr_op2 = m_op2->prenex();
    return std::make_shared<Or>(m_op1->prenex(), m_op2->prenex())->pullQuantifiers();
}

template<typename ListType>
ListType concatLists(const ListType &l1, const ListType &l2)
{
    ListType result;
    result.reserve(l1.size() + l2.size());
    std::copy(l1.cbegin(), l1.cbegin(), std::back_inserter(result));
    std::copy(l2.cbegin(), l2.cend(), std::back_inserter(result));
    return result;
}

LiteralListList Or::listDNF()
{
    GET_OPERANDS(op1, op2);
    return concatLists(op1->listDNF(), op2->listDNF());
}
