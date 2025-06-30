#show figure: set block(breakable: true)
#show figure: it => {
  box(width: 90%, inset: 10pt, it)
}
#show figure.where(kind: raw): set figure(gap: 1.5em, supplement: "Frag. codi")

#set par(justify: true, first-line-indent: 2em)
#align(center)[
  #text(18pt)[Raytracing notes]
  #v(2em)
]


References: #link("https://raytracing.github.io/books/RayTracingInOneWeekend.html")[Raytracing In One Weekend]

== The project

The main goal of this project is to learn about realistic rendering techniques. I have been curious about ray tracing for a while so I'm building this very basic renderer to understand the basic principles. It doesn't have a GUI or any kind of interactivity, everything is hard-coded for now. In the future, I might expand it by adding ImGui or creating a GPU version once I learn about OpenGL, which is another world I want to learn about.

== Introduction

=== Rendering the image

The image will be rendered to `stdout` in PPM (portable pixmap) format (the 8 bit ASCII variant). This format is very basic and only needs a couple definitions up top before dumping the values of all the pixels:

#figure(
  ```
  P3
  # "P3" means this is a RGB color image in ASCII
  # "600 400" is the width and height of the image in pixels
  # "255" is the maximum value for each color
  # This, up through the "255" line below are the header.
  # Everything after that is the image data: RGB triplets.
  3 2
  255
  255 0   0
  0   255 0
  0   0   255
  ...
  ```,
  caption: [PPM format header]
)

This makes it very simple to output in C++, simply print the header and loop through every pixel printing its RGB values:

#figure(
  ```cpp
std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
  ```,
  caption: [Formatting it in C++.]
)


== Spheres

In order to find if a ray intersects with a sphere



== G
