
reset
complex(x,y) = x*{1,0}+y*{0,1}
mandel(x,y,z,n) = (abs(z)>2.0 || n>=100) ? \
n : mandel(x,y,z*z+complex(x,y),n+1)
set xrange [-1.5:0.5]
set yrange [-1:1]
set logscale z
set isosample 50
set hidden3d
set contour
splot mandel(x,y,{0,0},0) notitle
pause -1
