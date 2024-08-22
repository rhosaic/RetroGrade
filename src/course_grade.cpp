
#include "../inc/course_grade.h"

Grade::score_type CourseGrade::final_grade() const {
    Grade::score_type finalGrade = {};

    for (auto grade : m_grades) {
        finalGrade += grade.weighted_score();
    }

    return finalGrade;
}
