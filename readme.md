## Ray Casting  
**Input file format:** </br>
First line: N = number of polygon points </br>
Next (N) lines: polygon points coordinates </br> 
Line (N + 1): M number of points to check </br>
Next (N + 1 + M) lines: points coordinates 
**Compilation and Execution:** </br>
To compile the program, use the following command in the terminal:
```
$ g++ ray_casting.cpp -o run `sdl2-config --cflags --libs`
```

To run the program with input and output files, use the following command:
```
$ ./run ray_casting.in ray_casting.out
```
