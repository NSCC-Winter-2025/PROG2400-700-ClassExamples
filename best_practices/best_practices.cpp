#include <iostream>
#include "best_practices.h"

BestPractices::~BestPractices() {
    std::cout << "BestPractices::~BestPractices()" << std::endl;
}

void BestPractices::member_function() {
  std::cout << "BestPractices::member_function()" << std::endl;
}
