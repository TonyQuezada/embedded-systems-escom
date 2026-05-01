/*
 * main.cpp
 * Genera datos de senales matematicas y produce una imagen JPG usando gnuplot.
 * Flujo: C++ genera .dat -> C++ crea script .gp -> gnuplot renderiza el JPG
 */
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>

int main() {
    std::cout << "=== Generador de Imagen JPG via gnuplot ===" << std::endl;

    const std::string dat_file = "/output/datos.dat";
    std::ofstream dat(dat_file);
    if (!dat.is_open()) {
        std::cerr << "Error: no se pudo crear " << dat_file << std::endl;
        return 1;
    }
    dat << "# x   seno   coseno   amortiguada\n";
    for (int i = 0; i <= 360; i++) {
        double x   = i * M_PI / 180.0;
        double s   = std::sin(x);
        double c   = std::cos(x);
        double amp = std::exp(-x / 8.0) * std::sin(4.0 * x);
        dat << x << " " << s << " " << c << " " << amp << "\n";
    }
    dat.close();
    std::cout << "Datos escritos en: " << dat_file << std::endl;

    const std::string gp_file = "/output/plot.gp";
    std::ofstream gp(gp_file);
    gp << "set terminal jpeg size 900,600 enhanced font 'Arial,11'\n";
    gp << "set output '/output/imagen_generada.jpg'\n";
    gp << "set title 'Senales matematicas - C++ con gnuplot'\n";
    gp << "set xlabel 'x (radianes)'\n";
    gp << "set ylabel 'Amplitud'\n";
    gp << "set grid\n";
    gp << "set key top right\n";
    gp << "set style line 1 lc rgb '#e74c3c' lw 2\n";
    gp << "set style line 2 lc rgb '#3498db' lw 2\n";
    gp << "set style line 3 lc rgb '#2ecc71' lw 2\n";
    gp << "plot '" << dat_file << "' using 1:2 with lines ls 1 title 'seno(x)', \\\n";
    gp << "     '" << dat_file << "' using 1:3 with lines ls 2 title 'coseno(x)', \\\n";
    gp << "     '" << dat_file << "' using 1:4 with lines ls 3 title 'amortiguada'\n";
    gp.close();
    std::cout << "Script gnuplot: " << gp_file << std::endl;

    std::string cmd = "gnuplot " + gp_file;
    int ret = std::system(cmd.c_str());
    if (ret != 0) { std::cerr << "Error gnuplot." << std::endl; return 1; }

    std::cout << "Imagen guardada: /output/imagen_generada.jpg" << std::endl;
    std::cout << "Proceso completado correctamente." << std::endl;
    return 0;
}
