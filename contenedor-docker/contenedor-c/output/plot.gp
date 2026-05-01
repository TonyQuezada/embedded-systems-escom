set terminal jpeg size 900,600 enhanced font 'Arial,11'
set output '/output/imagen_generada.jpg'
set title 'Senales matematicas - C++ con gnuplot'
set xlabel 'x (radianes)'
set ylabel 'Amplitud'
set grid
set key top right
set style line 1 lc rgb '#e74c3c' lw 2
set style line 2 lc rgb '#3498db' lw 2
set style line 3 lc rgb '#2ecc71' lw 2
plot '/output/datos.dat' using 1:2 with lines ls 1 title 'seno(x)', \
     '/output/datos.dat' using 1:3 with lines ls 2 title 'coseno(x)', \
     '/output/datos.dat' using 1:4 with lines ls 3 title 'amortiguada'
