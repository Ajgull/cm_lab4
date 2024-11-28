#include "constants.h"

double f(double x) {
    double temp = 1 - 2 * x * cos(x);
    return temp;
}

double g(double x) {
    return 1.0 / (2.0 * cos(x));
}

double df(double x) {
    return -2 * (cos(x) - x * sin(x));
}

vector<double> dichotomy_method() {
    vector<double> roots;

    for (double left = a; left < b; left += delta) {
        double right = left + delta;

        if (f(left) * f(right) < 0) {
            double midpoint;
            while ((right - left) / 2.0 > delta) {
                midpoint = (left + right) / 2.0;

                if (f(midpoint) == 0.0) {
                    roots.push_back(midpoint);
                    break;
                }

                if (f(midpoint) * f(left) < 0) {
                    right = midpoint;
                }
                else {
                    left = midpoint;
                }
            }
            double root = (left + right) / 2.0;
            if (find(roots.begin(), roots.end(), root) == roots.end()) {
                roots.push_back(root);
            }
        }
    }

    return roots;
}

vector<double> chord_method() {
    vector<double> roots;

    for (double left = a; left < b; left += delta) {
        double right = left + delta;

        if (f(left) * f(right) < 0) {
            double x0 = left;
            double x1 = right;
            double x2;

            while (true) {
                x2 = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));

                if (fabs(x2 - x1) < delta || fabs(f(x2)) < delta || fabs(x2 - x0) < delta) {
                    break; // Условие остановки достигнуто
                }

                x0 = x1;
                x1 = x2;

                if (x2 < a || x2 > b || isnan(x2)) {
                    break; // Выход за пределы интервала
                }
            }

            if (find(roots.begin(), roots.end(), x2) == roots.end()) {
                roots.push_back(x2);
            }
        }
    }

    return roots;
}

vector<double> simple_iteration() {
    vector<double> roots;

    for (double left = a; left < b; left += delta) {
        double right = left + delta;

        if (f(left) * f(right) < 0) {
            double x_n = (left + right) / 2;
            double x_n1;

            while (true) {
                x_n1 = g(x_n);

                if (fabs(x_n1 - x_n) < delta || fabs(cos(x_n1)) < delta) {
                    if (find(roots.begin(), roots.end(), x_n1) == roots.end()) {
                        roots.push_back(x_n1);
                    }
                    break;
                }

                x_n = x_n1;
            }
        }
    }

    return roots;
}

vector<double> newton_method() {
    vector<double> roots;

    for (double left = a; left < b; left += delta) {
        double x_n = left;

        if (f(left) * f(left + delta) < 0) {
            for (int i = 0; i < 100; ++i) {
                if (df(x_n) == 0.0)
                    break; // Избегаем деления на ноль

                double x_n1 = x_n - f(x_n) / df(x_n);

                if (fabs(x_n1 - x_n) < delta && find(roots.begin(), roots.end(), x_n1) == roots.end()) {
                    roots.push_back(x_n1); // Добавляем найденный корень
                    break; // Выходим из цикла
                }

                x_n = x_n1; // Обновляем текущее значение
            }
        }
    }

    return roots;
}

// Метод секущих для нахождения всех корней
vector<double> secant_method() {
    vector<double> roots;

    for (double left = a; left < b; left += delta) {
        double right = left + delta;

        if (f(left) * f(right) < 0) { // Проверяем наличие корня в интервале
            double x0 = left;
            double x1 = right;
            double x2;

            while (true) {
                if (f(x1) == f(x0)) break; // Избегаем деления на ноль

                // Вычисляем новое приближение по методу секущих
                x2 = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));

                if (fabs(f(x2)) < delta || fabs(x2 - x1) < delta || fabs(f(x2)) < delta)
                    break;

                // Обновляем значения для следующей итерации
                x0 = x1;
                x1 = x2;

                // Проверка выхода за пределы интервала
                if (x2 < a || x2 > b || isnan(x2)) break;
            }

            if (find(roots.begin(), roots.end(), x2) == roots.end()) {
                roots.push_back(x2);
            }
        }
    }

    return roots;
}

void print(const vector<double>& roots, const string& method_name) {
    if (!roots.empty()) {
        cout << "Found roots using " << method_name << ": ";
        for (const double root : roots) {
            printf("%.4f ", root);
        }
        cout << endl;
    }
    else {
        cout << "No roots found using " << method_name << "." << endl;
    }
}

void first() {
    vector<double> bisection_roots = dichotomy_method();
    print(bisection_roots, "Dichotomy Method");

    vector<double> chord_roots = chord_method();
    print(chord_roots, "Chord Method");

    vector<double> iteration_roots = simple_iteration();
    print(iteration_roots, "Simple Iteration Method");

    vector<double> newton_roots = newton_method();
    print(newton_roots, "Newton's Method");

    vector<double> secant_roots = secant_method();
    print(secant_roots, "Secant Method");
}
