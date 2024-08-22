
#ifndef COURSE_GRADE_H
#define COURSE_GRADE_H

#include <vector>

#include "grade.h"

class CourseGrade {
public:
    using list_type = std::vector<Grade>;

    CourseGrade(const list_type& grades = {}) : m_grades(grades) {}

    list_type grades() const { return m_grades; }

    Grade::score_type final_grade() const;

private:
    list_type m_grades;
};

#endif
