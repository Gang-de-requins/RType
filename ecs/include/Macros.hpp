#ifndef MACROS_HPP
#define MACROS_HPP

#include <bitset>

using EntityID = std::size_t;

using ComponentTypeID = std::size_t;
constexpr ComponentTypeID MAX_COMPONENTS = 64;

using ArchetypeID = std::bitset<MAX_COMPONENTS>;

#endif /* MACROS_HPP */