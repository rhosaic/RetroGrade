
#include "../inc/menu.h"
#include <cstddef>
#include <string>

Menu::Menu(const std::initializer_list<option_type>& options) {
    for (auto option : options) {
        m_options.push_back(option);
    }
}

std::string Menu::as_string(
    const size_t padding, const char& vertical_border,
    const std::string& horizontal_border, const std::string& seperator
) const {
    std::string formatted;
    std::size_t optionIndex;
    std::size_t optionsSize;

    optionsSize = m_options.size();

    formatted += (
        std::string(
            menu_length(
                padding, horizontal_border.size(), seperator.size()
            ), vertical_border
        ) + '\n' + horizontal_border
    );

    for (optionIndex = 0; optionIndex < optionsSize; ++optionIndex) {
        std::string optionEnd;
        std::string spacing;

        optionEnd = (optionIndex == (optionsSize - 1)) 
            ? horizontal_border : seperator;
        
        spacing = std::string(padding, ' ');

        formatted += (
            spacing + m_options.at(optionIndex) + spacing + optionEnd
        );
    }

    formatted += (
        '\n' + std::string(
            menu_length(
                padding, horizontal_border.size(), seperator.size()
            ), vertical_border
        ) + '\n'
    );

    return formatted;
}

std::size_t Menu::menu_length(
    const std::size_t& padding, 
    const std::size_t& horizontal_border_length, 
    const std::size_t& seperator_length
) const {
    std::size_t menuLength = {};

    menuLength += horizontal_border_length;

    for (auto option : m_options) {
        menuLength 
            += ((2 * padding) + option.length() + seperator_length);
    }

    menuLength += (horizontal_border_length - seperator_length);

    return menuLength;
}
