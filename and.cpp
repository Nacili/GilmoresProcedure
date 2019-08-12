#include "and.h"
#include "constants.h"
#include "forall.h"
#include "exists.h"

And::And(const Formula &op1, const Formula &op2)
    : BinaryConnective (op1, op2)
{
    
}

std::ostream &And::print(std::ostream &out) const
{
    return printImpl(out, "/\\");
}

Formula And::substitute(const Variable &v, const Term &t) const
{
    return substituteImpl<And>(v, t);
}

bool And::eval(const LStructure &structure, const Valuation &valuation) const
{
    return m_op1->eval(structure, valuation) && m_op2->eval(structure, valuation);
}

Formula And::simplify() const
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
    else if (BaseFormula::isOfType<False>(sop1) || BaseFormula::isOfType<False>(sop2))
    {
        return std::make_shared<False>();
    }
    else
    {
        return std::make_shared<And>(sop1, sop2);
    }
}

Formula And::nnf() const
{
    return std::make_shared<And>(m_op1->nnf(), m_op2->nnf());
}

Formula And::pullQuantifiers() const
{
    const Forall *fop1 = BaseFormula::isOfType<Forall>(m_op1);
    const Forall *fop2 = BaseFormula::isOfType<Forall>(m_op2);
    if (fop1 && fop2)
    {
        if (fop1->variable() == fop2->variable())
        {
            return std::make_shared<Forall>(fop1->variable(), 
                                            std::make_shared<And>(
                                                fop1->operand(), 
                                                fop2->operand())->pullQuantifiers());
        }
        else
        {
            Variable renamed = Quantifier::getUniqueVarName(fop1->operand(), fop2->operand());
            return std::make_shared<Forall>(renamed, std::make_shared<And>(
                                                fop1->operand()
                                                    ->substitute(fop1->variable(), std::make_shared<VariableTerm>(renamed)),
                                                fop2->operand()
                                                    ->substitute(fop2->variable(), std::make_shared<VariableTerm>(renamed))
                                                )->pullQuantifiers());
        }
    }
    else if (fop1)/*Vz (A(x->z) /\ B)*/
    {
        if (m_op2->hasVariable(fop1->variable(), true))
        {
            Variable renamed = Quantifier::getUniqueVarName(fop1->operand(), m_op2);
            return std::make_shared<Forall>(renamed, std::make_shared<And>(
                                                fop1->operand()->substitute(fop1->variable(), std::make_shared<VariableTerm>(renamed)), 
                                                m_op2)->pullQuantifiers());
        }
        else
        {
            return std::make_shared<Forall>(fop1->variable(), std::make_shared<And>(
                                                fop1->operand(), m_op2)->pullQuantifiers());
        }
    }
    else if (fop2) /* A /\ Vx B(x) */
    {
        if (m_op1->hasVariable(fop2->variable(), true))
        {
            Variable renamed = Quantifier::getUniqueVarName(fop2->operand(), m_op1);
            return std::make_shared<Forall>(renamed,  std::make_shared<And>(
                                                m_op1, 
                                                fop2->operand()->substitute(fop2->variable(), 
                                                                            std::make_shared<VariableTerm>(renamed))
                                                )->pullQuantifiers());
        }
        else
        {
            return std::make_shared<Forall>(fop2->variable(), std::make_shared<And>(m_op1, fop2->operand())->pullQuantifiers());
        }
    }
    
    const Exists *eop1 = BaseFormula::isOfType<Exists>(m_op1);
    const Exists *eop2 = BaseFormula::isOfType<Exists>(m_op2);
    if (eop1)/* Ex A(x) /\ B */
    {
        if (m_op2->hasVariable(eop1->variable(), true))
        {
            Variable renamed = Quantifier::getUniqueVarName(eop1->operand(), m_op2);
            return std::make_shared<Exists>(renamed, std::make_shared<And>(
                                                eop1->operand()->substitute(eop1->variable(), std::make_shared<VariableTerm>(renamed)), 
                                                m_op2)->pullQuantifiers());
        }
        else
        {
            return std::make_shared<Exists>(eop1->variable(), std::make_shared<And>(
                                                eop1->operand(), m_op2)->pullQuantifiers());
        }
    }
    else if (eop2)
    {
        if (m_op1->hasVariable(eop2->variable(), true))
        {
            Variable renamed = Quantifier::getUniqueVarName(eop2->operand(), m_op1);
            return std::make_shared<Exists>(renamed,  std::make_shared<And>(
                                                m_op1, 
                                                eop2->operand()->substitute(eop2->variable(), 
                                                                            std::make_shared<VariableTerm>(renamed))
                                                )->pullQuantifiers());
        }
        else
        {
            return std::make_shared<Exists>(eop2->variable(), std::make_shared<And>(m_op1, eop2->operand())->pullQuantifiers());
        }
    }
    
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

Formula And::prenex() const
{
    return std::make_shared<And>(m_op1->prenex(), m_op2->prenex())->pullQuantifiers();
}
