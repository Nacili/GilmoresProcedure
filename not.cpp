#include "not.h"
#include "constants.h"
#include "and.h"
#include "or.h"
#include "imp.h"
#include "iff.h"
#include "forall.h"
#include "exists.h"

Not::Not(const Formula &f)
    : UnaryConnective (f)
{
}

Formula Not::substitute(const Variable &v, const Term &t) const
{
    return std::make_shared<Not>(m_op->substitute(v, t));
}

Formula Not::substitute(const Substitution &s) const
{
    return std::make_shared<Not>(m_op->substitute(s));
}

std::ostream &Not::print(std::ostream &out) const
{
    out << "~(";
    m_op->print(out);
    return out << ")";
}

bool Not::eval(const LStructure &structure, const Valuation &valuation) const
{
    return !m_op->eval(structure, valuation);
}

Formula Not::simplify() const
{
    Formula sop = m_op->simplify();
    if (BaseFormula::isOfType<True>(sop))
    {
        return std::make_shared<False>();
    }
    else if (BaseFormula::isOfType<False>(sop))
    {
        return std::make_shared<True>();
    }
    else 
    {
        return std::make_shared<Not>(sop);
    }
}

Formula Not::nnf() const
{
    Formula op = m_op->nnf();
    if (BaseFormula::isOfType<Not>(op))
    {
        return op;
    }
    
    const And *aop = BaseFormula::isOfType<And>(op);
    if (aop)
    {
        GET_OPERANDS_EXT(aop, aop1, aop2);
        return std::make_shared<Or>(std::make_shared<Not>(aop1)->nnf(), std::make_shared<Not>(aop2)->nnf());
    }
    
    const Or *oop = BaseFormula::isOfType<Or>(op);
    if (oop)
    {
        GET_OPERANDS_EXT(oop, oop1, oop2);
        return std::make_shared<And>(std::make_shared<Not>(oop1)->nnf(), std::make_shared<Not>(oop2)->nnf());
    }
    
    const Imp *imop = BaseFormula::isOfType<Imp>(op);
    if (imop)
    {
        GET_OPERANDS_EXT(imop, imop1, imop2);
        return std::make_shared<And>(imop1->nnf(), std::make_shared<Not>(imop2)->nnf());
    }
    
    const Iff *ifop = BaseFormula::isOfType<Iff>(op);
    if (ifop)
    {
        GET_OPERANDS_EXT(ifop, ifop1, ifop2);
        return std::make_shared<Or>(std::make_shared<And>(
                                        ifop1->nnf(), std::make_shared<Not>(ifop2)->nnf()), 
                                    std::make_shared<And>(
                                        std::make_shared<Not>(ifop1)->nnf(), ifop2->nnf()));
    }
    
    const Forall *fop = BaseFormula::isOfType<Forall>(op);
    if (fop)
    {
        Formula fop1 = fop->operand();
        Variable var = fop->variable();
        return std::make_shared<Exists>(var, std::make_shared<Not>(fop1)->nnf());
    }
    
    const Exists *eop = BaseFormula::isOfType<Exists>(op);
    if (eop)
    {
        Formula eop1 = eop->operand();
        Variable var = eop->variable();
        return std::make_shared<Forall>(var, std::make_shared<Not>(eop1)->nnf());
    }
    
    return std::make_shared<Not>(op);
}


LiteralListList Not::listDNF()
{
    return {{std::const_pointer_cast<BaseFormula>(shared_from_this())}};
}

Formula Not::prenex()
{
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}
