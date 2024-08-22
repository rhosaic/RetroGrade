
#include <iostream>
#include <fstream>

#include "../inc/menu.h"
#include "../inc/command_id.h"
#include "../inc/course_initializer.h"
#include "../inc/letter_range.h"

const std::string REPORT_FILENAME = "RetroGrade_Report.txt";
const std::size_t DEFAULT_PRECISION = 2;
const std::string INVALID_COMMAND = "Invalid command. Please enter another.";

const CourseInitializer::names_type DEFAULT_NAMES = {
    "Assignments", "Quizzes", "Midterm", "Final"
};

const CourseInitializer::weights_type DEFAULT_WEIGHTS = {30, 10, 30, 30};

const LetterRange DEFAULT_RANGES = {
    Letter("F", 60), Letter("D-", 64), Letter("D", 67), Letter("D+", 70),
    Letter("C-", 74), Letter("C", 77), Letter("C+", 80), Letter("B-", 84),
    Letter("B", 87), Letter("B+", 90), Letter("A-", 94), Letter("A", 100)
};

CourseInitializer::scores_type input_scores_from(
    const CourseInitializer::names_type& names
);

std::string with_precision(
    const std::size_t& precision, const Grade::score_type& score
);

std::string string_from(
    const CourseGrade& grades, const LetterRange& letters, 
    const std::size_t& precision
);

std::vector<Menu> split_menus(
    const Menu& menu, const std::size_t& maximumOptions
);

CourseGrade::list_type new_course(
    const CourseGrade::list_type& grades, const std::size_t& maximumOptions
);

CourseGrade edit_cycle(const CourseGrade& initialCourse);

CourseGrade import_from(const std::string& filename);

int main() {
    bool isNext;
    bool isQuit;
    CommandId::id_type command;
    CommandId input;
    CommandId import;
    CommandId quit;
    CommandId editScores;
    CommandId save;
    CommandId display;
    CommandId whatIf;
    CommandId toFile;
    CommandId queryRequirements;
    CourseGrade initialCourse;
    LetterRange currentRanges;

    isNext = false;
    isQuit = false;

    currentRanges = DEFAULT_RANGES;
    
    input = CommandId("(e)nter grades", 'e');
    import = CommandId("(i)mport from file", 'i');
    quit = CommandId("(q)uit", 'q');

    Menu initialize{input.m_name, import.m_name, quit.m_name};

    while (std::cin.good() && !(isNext || isQuit)) {
        std::cout   << '\n' << initialize.as_string(); 
        std::cin    >>  command;
        std::cout   << '\n';
        
        if (input.id_matches(command)) {
            initialCourse = CourseInitializer(
                DEFAULT_NAMES, input_scores_from(DEFAULT_NAMES), 
                DEFAULT_WEIGHTS
            ).as_course();

            isNext = true;
        } else if (import.id_matches(command)) {
            std::string filepath;
            std::cout   << "Please enter the full path to "
                        "RetroGrade_Report.txt\n";
            std::cin    >> filepath;

            initialCourse = import_from(filepath);
            isNext = true;
        } 
        else if (quit.id_matches(command)) {
            isQuit = true;
        } else {
            std::cout   << INVALID_COMMAND << '\n';
        }
    }

    isNext = false;

    editScores = CommandId("(e)dit scores", 'e');
    display = CommandId("(d)isplay current scores", 'd');
    save = CommandId("(s)ave and continue", 's');
    Menu modify{editScores.m_name, display.m_name, save.m_name, quit.m_name};

    while (std::cin.good() && !(isNext || isQuit)) {
        const std::size_t OPTIONS_MAXIMUM = 2;

        std::cout   << '\n';

        for (auto menu : split_menus(modify, OPTIONS_MAXIMUM)) {
            std::cout   << menu.as_string();
        }

        std::cin    >> command;

        if (editScores.id_matches(command)) {
            initialCourse = edit_cycle(initialCourse);
        } else if (display.id_matches(command)) {
            std::cout   << '\n' << string_from(
                            initialCourse, currentRanges, DEFAULT_PRECISION
                        );
        } else if (save.id_matches(command)) {
            isNext = true;
        } else if (quit.id_matches(command)) {
            isQuit = true;
        } else {
            std::cout   << INVALID_COMMAND << '\n';
        }
    }

    isNext = false;

    whatIf = CommandId("(w)hat-if analysis", 'w');
    toFile = CommandId("(g)enerate report", 'g');
    queryRequirements = CommandId("(c)heck passing requirements", 'c');
    Menu analyze{
        whatIf.m_name, toFile.m_name, queryRequirements.m_name, quit.m_name
    };

    while (std::cin.good() && !(isNext || isQuit)) {
        const std::size_t OPTIONS_MAXIMUM = 2;

        std::cout   << '\n';

        for (auto menu : split_menus(analyze, OPTIONS_MAXIMUM)) {
            std::cout   << menu.as_string();
        }

        std::cin    >> command;

        if (whatIf.id_matches(command)) {
            CourseGrade newCourse;

            newCourse = edit_cycle(initialCourse);
            std::cout   << "\nBefore changes:\n" << string_from(
                            initialCourse, currentRanges, DEFAULT_PRECISION
                        ) << '\n' << "With changes:\n" << string_from(
                            newCourse, currentRanges, DEFAULT_PRECISION
                        ) << '\n';
        } else if (toFile.id_matches(command)) {
            CommandId yes("(y)es", 'y');
            CommandId no("(n)o", 'n');

            Menu confirm{yes.m_name, no.m_name};

            std::cout   << "\nThis action will create/overwrite a file "
                        "named <" << REPORT_FILENAME 
                        << "> in the\ncurrent directory.\n";
            std::cout   << "\nContinue?\n\n" << confirm.as_string();
            std::cin    >> command;

            if (yes.id_matches(command)) {
                std::ofstream out;

                out.open(REPORT_FILENAME);
                out     << string_from(
                            initialCourse, currentRanges, DEFAULT_PRECISION
                        );

                out.close();
            }
        } else if (queryRequirements.id_matches(command)) {
            if (
                (initialCourse.grades().at(2).m_score > 0) 
                && (initialCourse.grades().at(3).m_score > 0)
            ) {
                std::cout   << "\nYou meet the requirements to earn a C.\n";
            } else {
                std::cout   << "\nYou do not meet the "
                            "requirements to earn a C.\n";
            }
        }
        else if (quit.id_matches(command)) {
            isQuit = true;
        } else {
            std::cout   << '\n' << INVALID_COMMAND << '\n';
        }
    }

    return 0;
}

CourseInitializer::scores_type input_scores_from(
    const CourseInitializer::names_type& names
) {
    CourseInitializer::scores_type scores;

    std::cout   << "Enter percentage grade for:\n";

    for (auto name : names) {
        Grade::score_type score;

        std::cout   << ' ' << name << ": ";
        std::cin    >> score;

        scores.push_back(score);
    }

    return scores;
}

std::string with_precision(
    const std::size_t& precision, const Grade::score_type& score
) {
    std::string formatted;
    std::string raw;
    std::size_t decimalPosition;

    raw = std::to_string(score);
    decimalPosition = raw.find_first_of('.');

    formatted += (
        raw.substr(0, decimalPosition) 
        + raw.substr(decimalPosition, precision + 1)
    );

    return formatted;
}

std::string string_from(
    const CourseGrade& course, const LetterRange& letters, 
    const std::size_t& precision
) {
    const std::size_t COLUMN_WIDTH = 20;
    const std::size_t COLUMN_COUNT = 4;
    const std::string HEADER_PREFIX = "| ";
    const std::string GRADE_PREFIX = "> ";
    const std::vector<std::string> HEADERS = {
        "Category", "Score", "Weight", "Weighted Score"
    };
    const std::string FINAL_HEADER = "Final Grade: "; 

    std::string formatted;
    Grade::score_type finalScore;

    formatted += (std::string((COLUMN_WIDTH * COLUMN_COUNT), '=') + '\n');

    for (auto header : HEADERS) {
        formatted += (
            HEADER_PREFIX + header + std::string(
                (COLUMN_WIDTH - header.size() - HEADER_PREFIX.size()), ' '
            )
        );
    }

    formatted += '\n';

    for (auto grade : course.grades()) {
        std::string nameSubstring;
        std::string scoreSubstring;
        std::string weightSubstring;

        nameSubstring = grade.m_name.substr(0, COLUMN_WIDTH);
        scoreSubstring = with_precision(
            precision, grade.m_score).substr(0, COLUMN_WIDTH
        );
        weightSubstring = with_precision(
            precision, grade.m_weight).substr(0, COLUMN_WIDTH
        );

        formatted += (
            GRADE_PREFIX + nameSubstring
            + std::string((COLUMN_WIDTH - nameSubstring.size()), ' ')
            + scoreSubstring 
            + std::string((COLUMN_WIDTH - scoreSubstring.size()), ' ')
            + weightSubstring
            + std::string((COLUMN_WIDTH - weightSubstring.size()), ' ')
            + with_precision(precision, grade.weighted_score()) + '\n'
        );
    }

    finalScore = course.final_grade();

    formatted += (std::string((COLUMN_WIDTH * COLUMN_COUNT), '=') + '\n');
    formatted += (
        FINAL_HEADER + with_precision(precision, finalScore) + '%' 
        + " (" + letters.assign_letter(finalScore) + ")\n"
    );
    formatted += (std::string((COLUMN_WIDTH * COLUMN_COUNT), '=') + '\n');

    return formatted;
}

std::vector<Menu> split_menus(
    const Menu& menu, const std::size_t& maximumOptions
) {
    std::vector<Menu> menus;
    Menu::list_type options;
    std::size_t optionCount = {};

    for (auto option : menu.options()) {
        options.push_back(option);
        ++optionCount;

        if (optionCount == maximumOptions) {
            menus.push_back(Menu(options));
            options.clear();
            optionCount = 0;
        }
    }

    if (options.size() != 0) {
        menus.push_back(Menu(options));
    }

    return menus;
}

CourseGrade::list_type new_course(
    const CourseGrade::list_type& grades, const std::size_t& maximumOptions
) {
    Menu::list_type options;
    std::size_t gradeIndex;
    bool isValid;
    std::size_t selection;
    Grade::score_type newScore;
    Grade newGrade;
    CourseGrade::list_type newGrades;

    isValid = false;

    while (!isValid) {
        for (gradeIndex = 0; gradeIndex < grades.size(); ++gradeIndex) {
            Menu::option_type option;

            option += (
                '(' + std::to_string(gradeIndex) + ") " 
                + grades.at(gradeIndex).m_name
            );

            options.push_back(option);
        }

        std::cout   << '\n';

        for (auto menu : split_menus(Menu(options), maximumOptions)) {
            std::cout   << menu.as_string();
        }

        options.clear();

        std::cout   << "Enter the number of the grade you wish to edit: ";
        std::cin    >> selection;

        isValid = (selection < grades.size());

        if (isValid) {
            CourseGrade::list_type::const_iterator position;

            newGrades = grades;
            position = (newGrades.begin() + selection);

            std::cout   << "Enter the new score: ";
            std::cin    >> newScore;

            newGrade = Grade(position->m_name, newScore, position->m_weight);

            newGrades.erase(position);
            newGrades.emplace(position, newGrade);
        } else {
            std::cout   << '\n' << INVALID_COMMAND << '\n';
        }
    }
    
    return newGrades;
}

CourseGrade edit_cycle(const CourseGrade& initialCourse) {
    const std::size_t GRADE_OPTIONS_MAXIMUM = 4;
    CommandId::id_type command;
    CommandId continueEdit;
    CommandId finishedEdit;
    CourseGrade course;
    bool isFinished;

    continueEdit = CommandId("(c)ontinue editing", 'c');
    finishedEdit = CommandId("(f)inished editing", 'f');
    Menu editing{continueEdit.m_name, finishedEdit.m_name};

    isFinished = false;
    course = initialCourse;

    course = CourseGrade(
        new_course(course.grades(), GRADE_OPTIONS_MAXIMUM)
    );

    while (std::cin.good() && !isFinished) {
        std::cout   << '\n' << editing.as_string();
        std::cin    >> command;

        if (continueEdit.id_matches(command)) {
            course = CourseGrade(
                new_course(
                    course.grades(), GRADE_OPTIONS_MAXIMUM
                )
            );
        } else if (finishedEdit.id_matches(command)) {
            isFinished = true;
        } else {
            std::cout   << '\n' << INVALID_COMMAND << '\n';
        }
    }

    return course;
}

CourseGrade import_from(const std::string& filename) {
    CourseGrade::list_type grades;
    std::string info;
    int check;

    std::ifstream in;
    in.open(filename);

    check = in.peek();

    while (check != '>') {
        getline(in, info);
        check = in.peek();
    }

    while (check == '>') {
        char start;
        Grade::name_type name;
        Grade::score_type score;
        Grade::weight_type weight;

        in  >> start >> name >> score >> weight;
        getline(in, info);
        grades.push_back(Grade(name, score, weight));

        check = in.peek();
    }

    in.close();

    return CourseGrade(grades);
}
