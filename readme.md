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