## Ray Casting  
**Input file format:** </br>
First line: N = number of polygon points </br>
Next (N) lines: polygon points coordinates </br> 
Line (N + 1): M number of points to check </br>
Next (N + 1 + M) lines: points coordinates 
**Compilation and Execution:** </br>
To compile the program, use the following command in the terminal:
```
$ g++ ray_casting.cpp -o ray_casting `sdl2-config --cflags --libs`
```

To run the program with input and output files, use the following command:
```
$ ./ray_casting ray_casting.in ray_casting.out
```

## Convex Hull
```
$ g++ convex_hull.cpp -o convex_hull `sdl2-config --cflags --libs`
```

```
$ ./convex_hull convex_hull.in convex_hull.out
```