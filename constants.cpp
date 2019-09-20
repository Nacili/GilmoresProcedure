#include "constants.h"


True::True()
  : AtomicFormula ()
{

}

std::ostream &True::print(std::ostream &out) const
{
    return out << "T";
}

bool True::eval(const LStructure &structure, const Valuation &valuation) const
{
    UNUSED_ARG(structure);
    UNUSED_ARG(valuation);
    return true;
}

void True::getConstants(ConstantSet &cts) const
{
    return;
}

void True::getFunctions(FunctionSet &cts) const
{
    return;
}

False::False()
  : AtomicFormula ()
{

}

std::ostream &False::print(std::ostream &out) const
{
    return out << "F";
}

bool False::eval(const LStructure &structure, const Valuation &valuation) const
{
    UNUSED_ARG(structure);
    UNUSED_ARG(valuation);
    return false;
}

LiteralListList False::listDNF()
{
    return {};
}


void False::getConstants(ConstantSet &cts) const
{
    return;
}

void False::getFunctions(FunctionSet &cts) const
{
    return;
}


LiteralListList True::listDNF()
{
    return {{}};
}


