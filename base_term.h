#ifndef BASETERM_H
#define BASETERM_H

#include "common.h"
#include "lstructure.h"
#include "valuation.h"

#include <memory>
#include <iostream>
#include <map>

class BaseTerm;

using Term = std::shared_ptr<BaseTerm>;

using Substitution = std::map<Variable, Term>;

class BaseTerm : public std::enable_shared_from_this<BaseTerm>
{
public:
    /**
     * @brief BaseTerm konstruktor
     */
    BaseTerm();
    
    /**
     * @brief print - stampa term u C++ stream
     * @param out - izlazni stream
     * @return referencu na izmenjeni stream
     */
    virtual std::ostream& print(std::ostream &out) const = 0;
    
    /**
     * @brief equalTo - provera sintaksne jednakosti dva terma
     * @param oth - term sa kojim se tekuci objekat poredi
     * @return true ako su sintaksno jednaki, false inace
     */
    virtual bool equalTo(const Term &oth) const = 0;
    
    /**
     * @brief getVariables - dohvatanje svih promenljivih koje se javljaju u termu
     * @param vset - skup promenljivih na koji se nadovezuju promenljive ovog terma
     */
    virtual void getVariables(VariablesSet &vset) const = 0;
    
    /**
     * @brief hasVariable - provera da li term sadrzi promenljivu
     * @param v
     * @return 
     */
    virtual bool hasVariable(const Variable &v) const = 0;
    
    /**
     * @brief substitute - zamena promenljive 'v' sa termom 't' u tekucem termu
     * @param v - promenljiva koja se menja
     * @param t - term kojim se promenljiva menja
     * @return izmenjeni term
     */
    virtual Term substitute(const Variable &v, const Term &t) const = 0;
    
    virtual Term substitute(const Substitution &s) const = 0;
    
    /**
     * @brief eval - racuna vrednost terma u tekucoj valuaciji i interpretaciji (rezultujuca vrednost je vrednost iz domena)
     * @param structure - konkretna interpretacija
     * @param valuation - konkretna valuacija
     * @return vrednost terma
     */
    virtual AnyType eval(const LStructure &structure, const Valuation &valuation) const = 0;
    
    /**
     * @brief ~BaseTerm destruktor
     */
    virtual ~BaseTerm();

    // for Herbrand
    virtual void getConstants(ConstantSet & cs) const = 0;
    virtual void getFunctions(ConstantSet & fs) const = 0;
};

bool operator==(const Term &lhs, const Term &rhs);

std::ostream& operator<<(std::ostream &out, const Term &t);

#endif // BASETERM_H
