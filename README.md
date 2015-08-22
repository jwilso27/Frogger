#Frogger

This project began as a final project for a computer science course.
The project was written in C, as C was the subject of the course.
We were provided with gfx3.c and gfx3.h to have functions to create the graphics for the game.

##Requirements

This program requires the stdio.h, math.h, and unstid.h C libraries as well as X11 and gcc to compile.

##Play

####Clone

```
git clone https://github.com/jwilso27/Frogger.git
```

####Compile

Linux:

```
make linux

make clean
```

Mac with X11 (Dependent on location of X11 library):

```
make mac

make clean
```

##Bugs

Due to time constraints (and realizing the night before the project was due that frogs standing on floating logs move with the log across water), the frog jumps rather than moving smoothly across the water.
This will be fixed soon.

##Future

I would like to rewrite this in C++ as a separate project.

##Acknowledgments

This project was originally written with fellow student Sara Cunningham.
