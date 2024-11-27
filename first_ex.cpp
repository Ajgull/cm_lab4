#include "constants.h"


// Метод бисекции для нахождения всех корней
vector<double> dichotomy_method(double (*func)(double), double a, double b, double delta) {
    vector<double> roots;

    for (double left = a; left < b; left += delta) {
        double right = left + delta;

        if (func(left) * func(right) < 0) {
            double midpoint;
            while ((right - left) / 2.0 > delta) {
                midpoint = (left + right) / 2.0;

                if (func(midpoint) == 0.0) {
                    roots.push_back(midpoint);
                    break;
                }

                if (func(midpoint) * func(left) < 0) {
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

void  first() {
    vector<double> roots = dichotomy_method(f, a, b, delta);

    if (!roots.empty()) {
        cout << "Found roots: ";
        for (double root : roots) {
            cout << root << " ";
        }
        cout << endl;
    }
    else {
        cout << "No roots found in the given interval." << endl;
    }

}
