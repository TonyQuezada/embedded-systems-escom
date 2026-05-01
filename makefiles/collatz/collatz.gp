set terminal pngcairo size 1000,800 enhanced
set output "collatz.png"

unset key
unset xtics
unset ytics
unset border
unset colorbox

set size ratio -1
set xrange [-2:2]
set yrange [-2:2]

set object 1 rectangle from screen 0,0 to screen 1,1 \
    fillcolor rgb "black" behind

set pm3d map interpolate 3,3

set palette defined ( \
  0 "black", \
  1 "#220000", \
  2 "#550000", \
  3 "#aa0000", \
  4 "red", \
  5 "orange", \
  6 "yellow", \
  7 "white" )

set cbrange [0:70]

splot "collatz.txt" using 1:2:3 with pm3d
