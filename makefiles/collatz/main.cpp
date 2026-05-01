#include <complex>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numbers>

using namespace std;

complex<double> collatz_complex(complex<double> z) {
    return (z / 2.0) * (1.0 + cos(std::numbers::pi * z)) / 2.0 +
           (3.0 * z + complex<double>(1.0, 0.0)) * (1.0 - cos(std::numbers::pi * z)) / 2.0;
}

// Iteraciones hasta escape
int collatz_fractal(complex<double> z0) {
    complex<double> z = z0;
    int max_iter = 500;

    for (int i = 0; i < max_iter; i++) {
        z = collatz_complex(z);

        if (abs(z) > 60.0) {
            return i;
        }
    }
    return max_iter;
}

int main() {
    int width = 800;
    int height = 800;

    double xmin = -2.0, xmax = 2.0;
    double ymin = -2.0, ymax = 2.0;

    ofstream file("collatz.txt");
    file << fixed << setprecision(6);

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {

            double x = xmin + (xmax - xmin) * i / (width - 1);
            double y = ymin + (ymax - ymin) * j / (height - 1);

            complex<double> z(x, y);
            int value = collatz_fractal(z);

            file << x << " " << y << " " << value << "\n";
        }
        file << "\n";
    }

    file.close();
    return 0;
}