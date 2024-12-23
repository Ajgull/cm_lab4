#include "constants.h"

double F(double x, double y) {
    return 1 - (pow(x, 2) - 1) * (pow(y, 2) - 1) * (x * exp(y) + y * exp(x));
}

double dFdx(double x, double y) {
    return ((y * y * y - y) * (-x * x - 2 * x + 1) * exp(x) +
        (3 * exp(y) - 3 * y * y * exp(y)) * x * x +
        y * y * exp(y) - exp(y));
}

double dFdy(double x, double y) {
    return ((x * x * x - x) * (-y * y - 2 * y + 1) * exp(y) +
        (3 * exp(x) - 3 * x * x * exp(x)) * y * y +
        x * x * exp(x) - exp(x));
}

void simpleIteration(double& x, double& y) {
    double newX, newY;
    do {
        newX = x +fabs( exp(-y) * dFdx(x, y) / (80));
        newY = y + fabs( exp(-x) * dFdy(x, y) / (90));

        newX = max(0.0, min(1.0, newX));
        newY = max(0.0, min(1.0, newY));

        if (fabs(newX - x) < delta && fabs(newY - y) < delta)
            break;

        x = newX;
        y = newY;
    } while (true);
}

void second() {
    setlocale(LC_ALL, "rus");
    double x = 0.4; 
    double y = 0.4; 

    simpleIteration(x, y);

    cout << fixed << setprecision(5);
    cout << "Минимум функции достигается в точке: (" << x << ", " << y << ")" << endl;
    cout << "Значение функции в этой точке: " << F(x, y) << endl;

}