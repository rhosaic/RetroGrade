
#ifndef GRADE_H
#define GRADE_H

#include <string>

#include "letter_range.h"

struct Grade {
    using name_type = std::string;
    using score_type = Letter::bound_type;
    using weight_type = score_type;

    Grade(
        const name_type& name = {}, const score_type& score = {}, 
        const weight_type& weight = {}
    ) : m_name(name), m_score(score), m_weight(weight) {}

    score_type weighted_score() const { 
        return (m_score * (m_weight / LetterRange::RANGE_MAXIMUM));
    }

    name_type m_name;
    score_type m_score;
    weight_type m_weight;
};

#endif
