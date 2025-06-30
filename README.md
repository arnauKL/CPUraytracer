# Ray tracer

>Project in development

A basic ray tracer, built by following the book [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html).


- Outputs the image to `stdout`.
- Runs on the CPU.
- No external dependencies (yet)

![Result image](doc/result.png)

## Motivation

The main goal of this project is to learn about realistic rendering techniques.  It doesn't have a GUI or any kind of interactivity, everything is hard-coded for now.

## Building

Linux:

```bash
git clone https://github.com/arnauKL/CPUraytracer.git
cd CPUraytracer
make
```


## Running

The image is output to standard output stream in PPM format.

```bash
./raytracer > result.ppm
```

It can be then viewed using _imv_ or some other image viewer that supports PPM, or converted to other image formats (ImageMagick):

```bash
magick result.ppm result.png
```
