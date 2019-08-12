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
