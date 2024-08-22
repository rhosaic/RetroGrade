
#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <initializer_list>

#include "command_id.h"

class Menu {
public:
    using option_type = CommandId::name_type;
    using list_type = std::vector<option_type>;

    Menu(const std::initializer_list<option_type>& options = {});
    Menu(const list_type& options) : m_options(options) {}

    std::string as_string(
        const std::size_t padding = 2, const char& vertical_border = '=',
        const std::string& horizontal_border = "|", 
        const std::string& seperator = "|"
    ) const;

    list_type options() const { return m_options; }

private:
    list_type m_options;

    std::size_t menu_length(
        const std::size_t& padding, 
        const std::size_t& horizontal_border_length, 
        const std::size_t& seperator_length
    ) const;
};

#endif
