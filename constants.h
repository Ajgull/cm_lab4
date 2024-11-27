#pragma once
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double a = 0;
const double b = 2;
const double delta = 0.001;

double f(double x) {
	double temp = 1 - 2 * x * cos(x);
	return temp;
}
