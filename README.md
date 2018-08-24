# Metaball/Spheres Raytracer

Renders metaballs and spheres. Uses native C++17. Uses CUDA 9.0 and png++ to render and write pngs to file, respectively. I use ffmpeg or gifski to stich together videos and gifs. 

## Current Features and Methods

Renders metaballs and spheres using ray marching and raytracing, respectively. Metaball rendering is done by first checking if a ray will enter a proper bounding sphere, before inching a ray through the bounding sphere to determine where the isosurface lies. This task is parallelized with GPUs (embarrassingly parallel task). 

To create an interesting animation, metaballs are connected to each other with springs with various k values. We let the physics dictate the movement of the metaballs (each with a mass of 1kg) between frames. See GIF below:

![Metaball Gif](examples/out500.gif)

## Youtube Links


## Todo:

- [x] Finish writing this README...
- [ ] Implement Phong Speculars
- [ ] Implement Multiple light sources
- [ ] Add Youtube Links
- [ ] GPU rendering for parallelism

