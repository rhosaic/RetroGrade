
#include "../inc/course_initializer.h"

CourseGrade CourseInitializer::as_course() const {
    std::size_t listIndex;
    CourseGrade::list_type grades;

    for(listIndex = 0; listIndex < minimum_size(); ++listIndex) {
        grades.push_back(
            Grade(
                m_names.at(listIndex), m_scores.at(listIndex), 
                m_weights.at(listIndex)
            )
        );
    }

    return CourseGrade(grades);
}

std::size_t CourseInitializer::minimum_size() const {
    std::vector<std::size_t>::const_iterator minimum;
    std::vector<std::size_t>::const_iterator position;
    std::vector<std::size_t> sizes;

    sizes.push_back(m_names.size());
    sizes.push_back(m_scores.size());
    sizes.push_back(m_weights.size());

    minimum = position = sizes.begin();
    ++position;

    while (position != sizes.end()) {
        if (*minimum > *position) {
            minimum = position;
        }

        ++position;
    }

    return *minimum;
}
