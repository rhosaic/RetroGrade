
#ifndef LETTER_H
#define LETTER_H

#include <string>

struct Letter {
    using name_type = std::string;
    using bound_type = double;

    Letter(const name_type& name = {}, const bound_type& bound = {}) 
        : m_name(name), m_bound(bound) {}

    name_type m_name;
    bound_type m_bound;
};

#endif
