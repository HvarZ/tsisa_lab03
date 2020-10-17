#include "simulated_annealing.hpp"
int main() {


    cout << "Вариант 15" << endl;
    cout << "Функция y = x^2 * sin(x)" << endl;
    cout << "Интервал [9, 12]" << endl;
    auto result = simulated_annealing(9, 12, 0.1, 10000, f);
    print(result);


    cout << endl << endl;
    cout << "Функция y = x^2 * sin(x) * sin(5 * x)" << endl;
    cout << "Интервал [9, 12]" << endl;
    auto result_m = simulated_annealing(9, 12, 0.1, 10000, f_m);
    print(result_m);
    return 0;
}
