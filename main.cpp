#include <iostream>
#include "calculator.h"

int main()
{
    Calculator calc;
    std::cout << "5 + 6 = " << calc.Add(5, 6) << std::endl;
    return 0;
}
