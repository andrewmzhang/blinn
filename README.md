# Metaball/Spheres Raytracer

Renders metaballs and spheres. Uses C++. No external libraries (as of yet). Project is still being improved on. This is also an excuse for me to learn more C++.

## Current Features and Methods

Renders metaballs and spheres using ray marching and raytracing, respectively. Metaball rendering is done by first checking if a ray will enter a proper bounding sphere, before inching a ray through the bounding sphere to determine where the isosurface lies. This task is parallelized with OpenMP. 

To create an interesting animation, metaballs are connected to each other with springs with various k values. We let the physics dictate the movement of the metaballs (each with a mass of 1kg) between frames. See video below:

![Metaball Gif](examples/out500.gif)



## Todo:

- [ ] Finish writing this README...
- [ ] Multi-node cluster computing. Current metaball rendering takes a bit too long (4 cores ~ 6 sec), rendering frames are parallizable, however 
