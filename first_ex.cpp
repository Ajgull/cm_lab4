#include "constants.h"


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

vector<double> chord_method(double (*func)(double)) {
    vector<double> roots;

    for (double left = a; left < b; left += delta) {
        double right = left + delta;

        if (func(left) * func(right) < 0) {
            // ���� ���� ������ ����� left � right, ��������� ����� ����
            double x0 = left;
            double x1 = right;
            double x2;

            while (true) {
                // ������� ����� �����������
                x2 = x1 - func(x1) * (x1 - x0) / (func(x1) - func(x0));

                // ��������� ������� ���������
                if (fabs(x2 - x1) < delta || fabs(func(x2)) < delta || fabs(x2 - x0) < delta) {
                    break; // ������� ��������� ����������
                }

                // ��������� �������� ��� ��������� ��������
                x0 = x1;
                x1 = x2;

                // �������� ������ �� ������� ���������
                if (x2 < a || x2 > b || isnan(x2)) {
                    break; // ����� �� ������� ���������
                }
            }

            // ��������� ��������� ������ � ������, ������� ����������
            if (find(roots.begin(), roots.end(), x2) == roots.end()) {
                roots.push_back(x2);
            }
        }
    }

    return roots;
}

void print(const vector<double>& roots) {
    if (!roots.empty()) {
        printf("Found roots: ");
        for (const double root : roots) {
            printf("%.10f ", root); // ���������� %f ��� ������ double
        }
        printf("\n"); // ������� �� ����� ������
    }
}

void  first() {
    vector<double> bisection = dichotomy_method();
    print(bisection);

    vector<double> chord = chord_method(f);
    print(chord);
}
