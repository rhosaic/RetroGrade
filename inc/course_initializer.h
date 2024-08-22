
#ifndef COURSE_INITIALIZER
#define COURSE_INITIALIZER

#include <vector>

#include "course_grade.h"

class CourseInitializer {
public:
    using names_type = std::vector<Grade::name_type>;
    using scores_type = std::vector<Grade::score_type>;
    using weights_type = std::vector<Grade::weight_type>;

    CourseInitializer(
        const names_type& names = {}, const scores_type& scores = {}, 
        const weights_type& weights = {}
    ) : m_names(names), m_scores(scores), m_weights(weights) {}

    CourseGrade as_course() const;
    
private:
    names_type m_names;
    scores_type m_scores;
    weights_type m_weights;

    std::size_t minimum_size() const;
};

#endif
