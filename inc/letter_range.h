
#ifndef LETTER_RANGE_H
#define LETTER_RANGE_H

#include <vector>
#include <initializer_list>

#include "letter.h"

class LetterRange {
public:
    using score_type = Letter::bound_type;
    using list_type = std::vector<Letter>;

    static constexpr score_type RANGE_MAXIMUM = 100;

    LetterRange(const std::initializer_list<Letter>& letters = {}) 
        : m_letters(sort_letters(letters)) {}

    LetterRange(const list_type& letters) 
        : m_letters(sort_letters(letters)) {}

    Letter::name_type assign_letter(const Letter::bound_type& score) const;
    
    list_type sort_letters(const list_type& letters) const;

    list_type m_letters;
};

#endif
