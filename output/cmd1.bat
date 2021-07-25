cd E:\Education\raytracer-basic\build
cmake -G "MinGW Makefiles" ..
mingw32-make
cd ../output
.\RaytracerBasic.exe > image.ppm
pause