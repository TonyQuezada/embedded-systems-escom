# Author: Ciro Fabian Bermudez Marquez
# File: julia_set.gp
# Description: julia_set
# Run: gnuplot julia_set.gp

filename = "julia_set"
file = filename . ".txt"
select = 1

# Change the terminal from the command line
if (ARGC > 0) {
    select = ARG1 + 0
}

if (select == 1) {
# PNG Version
  print "PNG Mode Selected"
  reset
  unit = 3
  # use crop
  set terminal pngcairo size unit*640, unit*384 font "CMU Serif, 10" fontscale 1*unit*0.95 background rgb "#000000"
  set output filename . ".png"
}
if (select == 2) {
# PDF Version
  print "PDF Mode Selected"
  reset
  unit = 3
  set terminal pdfcairo size unit*5in, unit*3in font "CMU Serif, 10" fontscale 0.5*unit background rgb "#000000" 
  set output filename . ".pdf"
}
if (select == 3) {
# LaTeX Version
  print "LaTeX Mode Selected"
  reset
  unit = 3
  set terminal epslatex standalone color size unit*5in, unit*3in background rgb "#000000" 
  set output filename . ".tex"
}

# Disable x-axis
unset xtics
unset xlabel

# Disable y-axis
unset ytics
unset ylabel

# Disable the border completely
set border 0

# Disable legend
unset key

#set palette defined ( 0 'blue', 45 'yellow')
#set palette rgbformula -7,2,-7
#set palette rgb 7,5,15;


# Set color palette
set palette rgb 21,22,23;
set size square
unset colorbox

plot file using 1:2:3 with image \
     #,file using 1:2:(sprintf("%g",$3) ) with labels

# Restore default values
reset
set terminal qt
set output

