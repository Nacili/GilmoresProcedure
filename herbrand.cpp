#include "herbrand.h"

#include <memory>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>

HerbrandUniverse::HerbrandUniverse(Signature::Sptr signature, const Formula & formula)
    : m_signature(signature), m_formula(formula)
{
    m_formula->getFunctions(m_functions);
    ConstantSet cSet;
    m_formula->getConstants(cSet);

    for (auto i = cSet.begin(); i != cSet.end(); i++) {
        Term t = std::make_shared<FunctionTerm>(m_signature, *i, std::vector<Term>{});
        m_level.insert(t);
    }
//    if (m_level.size() == 0) {
//        std::cout << "No constants found, inserting unique..." << std::endl;
//        FunctionSymbol fs = m_signature->getUniqueFunctionSymbol();
//        m_signature->addFunctionSymbol(fs, 0);
//        m_level.insert(
//            std::make_shared<FunctionTerm>(m_signature, m_signature->getUniqueFunctionSymbol(), std::vector<Term>{})
//        );
//    }

//    for(FunctionSymbol cs : cSet){
//        Term t = std::make_shared<FunctionTerm>(m_signature, cs, std::vector<Term>{});
//        m_level.insert(t);
//    }

    if (m_level.size() == 0) {
        std::cout << "No constants found, inserting unique..." << std::endl;
        std::vector<Term> terms;
        m_level.insert(
            std::make_shared<FunctionTerm>(m_signature, m_signature->getNewUniqueConstant(), terms)
        );
    }
}

std::set<Term> HerbrandUniverse::getLevel() const
{
    return m_level;
}

void HerbrandUniverse::nextLevel()
{
    std::vector<Term> tmp;
    std::copy(m_level.begin(), m_level.end(), std::back_inserter(tmp));

    for (auto i = m_functions.begin(); i != m_functions.end(); i++){
        unsigned arity;
        m_signature->hasFunctionSymbol(*i, arity);

        do {
            std::vector<Term> operands;
            if (arity > tmp.size()) {
                operands = std::vector<Term>(tmp.begin(), tmp.end());
                for (size_t i = tmp.size(); i < arity; i++) {
                    operands.push_back(
                        std::make_shared<FunctionTerm>(
                            m_signature, m_signature->getNewUniqueConstant(), std::vector<Term>{}
                        )
                    );
                }
            } else {
                operands = std::vector<Term>(tmp.begin(), tmp.begin() + arity);
            }
            Term requestNewLevel = std::make_shared<FunctionTerm>(
                    m_signature,
                    *i,
                    operands
            );

            if (std::find_if(
                        m_level.begin(),
                        m_level.end(),
                        [requestNewLevel](const Term &el){ return el->equalTo(requestNewLevel); }) == m_level.end()) {
                m_level.insert(requestNewLevel);
            }
        } while (std::next_permutation(tmp.begin(), tmp.end()));
    }
}

std::ostream &operator<<(std::ostream &out, const HerbrandUniverse &hu)
{
    out << "Functions:" << "\n";
    out << "{ ";
    std::copy(
            hu.m_functions.begin(),
            hu.m_functions.end(),
            std::ostream_iterator<FunctionSymbol>(std::cout, ", ")
    );
    out << " }";

    out << "\n" << "Level:" << "\n";
    out << "{ ";
    std::copy(
            hu.m_level.begin(),
            hu.m_level.end(),
            std::ostream_iterator<Term>(std::cout, ", ")
    );
    out << " }";
    return out;
}
