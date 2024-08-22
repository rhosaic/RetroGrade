
#ifndef COMMAND_ID_H
#define COMMAND_ID_H

#include <string>

struct CommandId {
    using name_type = std::string;
    using id_type = char;

    CommandId(const name_type& name = {}, const id_type& id = {}) 
        : m_name(name), m_id(id) {}

    bool id_matches(const id_type& check) { return (check == m_id); }

    name_type m_name;
    id_type m_id;
};

#endif
