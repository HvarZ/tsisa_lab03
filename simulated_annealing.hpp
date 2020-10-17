#ifndef TSISA_LAB03_SIMULATED_ANNEALING_HPP
#define TSISA_LAB03_SIMULATED_ANNEALING_HPP

#include <iostream>
#include <map>
#include <cmath>
#include <random>
#include <iomanip>
#include <string>

using std::cout;
using std::endl;

auto f(const double x) noexcept -> double {
    return pow(x, 2) * sin(x);
}

auto f_m(const double x) noexcept -> double {
    return pow(x, 2) * sin(x) * sin(5 * x);
}

auto P(const double delta_f, const double t_i) noexcept -> double {
    return std::exp((-delta_f)/t_i);
}

auto random(double a, double b) -> double {
    if (a > b) throw std::invalid_argument("Invalid segment");
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_real_distribution<double> rand(a, b);
    return rand(rng);
}

auto simulated_annealing(const double a, const double b, const double t_min, double t_max, double f(double))
                                                noexcept -> std::map<double,std::pair<double, double>> {
    std::map<double, std::pair<double, double>> result;
    auto x_min = random(a, b);
    while (t_max > t_min) {
        auto x_i = random(a, b);
        auto difference = f(x_i) - f(x_min);
        auto probability = 0.0;
        if (difference <= 0) {
            x_min = x_i;
            probability = 1;
        }
        else {
            auto temp = random(0, 1);
            probability = P(difference, t_max);
            if (temp < probability) {
                x_min = x_i;
            }
        }
        result[t_max] = {x_min, f(x_min)};
        t_max *= 0.95;
    }

    return result;
}

void print(const std::map<double, std::pair<double, double>>& result) noexcept {
    size_t counter = 0;
    cout << std::string(45, '-') << endl;
    cout << "|" << std::setw(10) << "N" << " |" << std::setw(10) << "T" << " |" << std::setw(10)
    << "x" << " |" << std::setw(8) << "f(x)" << endl;
    cout << std::string(45, '-') << endl;
    for(auto item = result.rbegin(); item != result.rend(); item++) {
        counter++;
        cout << "|" << std::setw(10) << counter << " |" << std::setw(10) << item->first
        << " |" << std::setw(10) << item->second.first << " |" << item->second.second << endl;
    }
    cout << std::string(45, '-') << endl;
    cout << "Result: Xmin = " << result.begin()->second.first << " | Fmin = " << result.begin() ->second.second << endl;
}

#endif //TSISA_LAB03_SIMULATED_ANNEALING_HPP
