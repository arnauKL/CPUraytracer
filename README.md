# Raytracer

>Project in development


Basic raytracer, built by following the book [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) to learn more about realistic rendering techniques.

- Outputs the image to `stdout`.
- Runs on the CPU.
- No external dependencies (yet)

![Result image](result.png)

## Building

Linux + g++:

```bash
g++ src/main.cpp -o raytracer
```

## Running

Image is output to standard output stream in `ppm` format.

```bash
./raytracer > result.ppm
```

It can be then viewed using _imv_ or some other image viewer that supports ppm, or converted to other image formats:

```bash
magick result.ppm result.png
```
