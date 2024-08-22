
#include "../inc/letter_range.h"

Letter::name_type LetterRange::assign_letter(
    const Letter::bound_type& score
) const {
    Letter::name_type letter;
    list_type::const_iterator position;

    position = m_letters.begin();

    while ((score > position->m_bound) && (position != m_letters.end())) {
        ++position;
    }

    return position->m_name;
}

LetterRange::list_type LetterRange::sort_letters(
    const list_type& letters
) const {
    list_type sorted;
    list_type unsorted;
    list_type::const_iterator minimum;
    list_type::const_iterator position;

    unsorted = letters;

    while (unsorted.size() != 0) {
        minimum = position = unsorted.begin();

        while (position != unsorted.end()) {
            if (minimum->m_bound > position->m_bound) {
                minimum = position;
            }

            ++position;
        }

        sorted.push_back(*minimum);
        unsorted.erase(minimum);
    }

    return sorted;
}
