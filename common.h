#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <unordered_set>

#define UNUSED_ARG(x) ((void)x)

using Variable = std::string;
using FunctionSymbol = std::string;
using RelationSymbol = std::string;
using Arity = unsigned;
using FunctionSet = std::unordered_set<FunctionSymbol>;
using ConstantSet = std::unordered_set<FunctionSymbol>;
using VariablesSet = std::unordered_set<Variable>;

/* Reprezentacija bilo kog vrednosnog tipa */
#include <experimental/any>
using AnyType = std::experimental::any;
#define AnyTypeToType(type, x) std::experimental::any_cast<type>(x)

#endif // COMMON_H
