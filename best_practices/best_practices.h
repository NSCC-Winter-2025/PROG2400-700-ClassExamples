#ifndef _BEST_PRACTICES_H
#define _BEST_PRACTICES_H

#include <string>

class BestPractices {
    enum class ENUMS : int { ENUM_1 = 1, ENUM_2 = 2, ENUM_3 = 3, ENUM_4 = 4, ENUM_5 = 5 };
    const std::string CONSTANT_STRING = "CONSTANT_STRING";
    std::string _member_variable = "MEMBER_VARIABLE";
public:
    BestPractices() = default;
    virtual ~BestPractices();

    void member_function();
};

#endif