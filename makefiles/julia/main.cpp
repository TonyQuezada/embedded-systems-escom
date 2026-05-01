#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <fstream>

double mandelbrot (const double& real, const double& imag) {
  
  // (-0.70176) (-0.3842)
  // (-0.835)  (-0.2321)
  // (0.4)  (-0.325)
  double z_real = real;
  double z_imag = imag;

  int iter = 45;
  double max_iter = static_cast<double>(iter);

  double zn_real; double zn_imag;
  for (int n = 0; n < iter; n++) {

    zn_real = (z_real * z_real) - (z_imag * z_imag) + (-0.70176);
    zn_imag = 2.0 * z_real * z_imag + (-0.3842);

    if ( zn_real*zn_real + zn_imag*zn_imag > 4.0 ) {
      return static_cast<double>(n);
    }

    z_real = zn_real;
    z_imag = zn_imag;

  }

  return max_iter;
}

int main(int argc, char** argv) {
  double x0 = -0.0;
  double r = 1.8;
  double points = 500;

  std::string filename = "julia_set.txt";
  std::ofstream outfile;
  outfile.open(filename);

  // Set fixed-point notation and precision
  outfile << std::fixed << std::setprecision(5);

  for (double y = -r; y < r; y += (r+r)/(points-1.0)) {
    for (double x = x0-r; x < x0+r; x += (r+r)/(points-1.0)) {
      outfile << std::setw(8) << x << ", " 
              << std::setw(8) << y << ", " 
              << std::setw(8) <<  mandelbrot(x,y) <<
              std::endl;

    }
    outfile << std::endl;
  }

  outfile.close();

  return 0;
}
