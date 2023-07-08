## Prerequisites

Before running this project, make sure you have the SDL2 library installed on your system.

### Installation Instructions

Please follow the steps below to install the SDL2 library: </br>

1. Visit the SDL2 website at [https://www.libsdl.org](https://www.libsdl.org).</br>
2. Download the appropriate SDL2 library package for your operating system.</br>
3. Follow the installation instructions provided by SDL2 for your specific platform.</br>
4. Once the SDL2 library is successfully installed, you can proceed with running the project.</br>

If you encounter any issues during the installation process, please refer to the SDL2 documentation or seek support from the SDL2 community.</br>


## Ray Casting  

**Input file format:** </br>
First line: N = number of polygon points </br>
Next (N) lines: polygon points coordinates </br> 
Line (N + 1): M number of points to check </br>
Next (N + 1 + M) lines: points coordinates </br>

**Compilation and Execution:** </br>
Compile the program
```
$ g++ ray_casting.cpp -o ray_casting `sdl2-config --cflags --libs`
```

Run the program
```
$ ./ray_casting ray_casting.in ray_casting.out
```
![Ray Casting](https://github.com/ClaudiuLBS/geometric-algorithms/raw/master/images/RayCasting.png)

## Convex Hull

**Input file format:** </br>
One point per line</br>

**Compilation and Execution:** </br>
Compile the program
```
$ g++ convex_hull.cpp -o convex_hull `sdl2-config --cflags --libs`
```

Run the program
```
$ ./convex_hull convex_hull.in convex_hull.out
```
![Convex Hull](https://github.com/ClaudiuLBS/geometric-algorithms/raw/master/images/ConvexHull.png)
