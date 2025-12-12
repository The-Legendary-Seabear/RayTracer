RayTracer

Introduction

RayTracer is a C++ ray tracing engine that renders realistic 3D scenes. It demonstrates core graphics concepts like ray-object intersections, recursive reflections, shading models, and anti-aliasing. The project compiles and runs on Windows using Visual Studio.

Features

- Ray casting per pixel with configurable camera
- Primitive shapes: spheres and planes
- Materials: diffuse, reflective, and refractive
- Recursive reflections and refractions
- Anti-aliasing with supersampling for smooth edges

Requirements:
- Visual Studio 2019 or newer
- C++17 or later
- Optional: external libraries (SDL2, GLM, etc.)

Build Instructions

1. Clone the repository:
git clone https://github.com/The-Legendary-Seabear/RayTracer.git

2. Open RayTracer.sln in Visual Studio
3. Set solution configuration to Release or Debug
4. Build the solution (Build → Build Solution)
5. Run the generated executable

Usage

- Run the executable from Visual Studio or by double-clicking the .exe
- Rendered images are saved to the working directory or displayed in a window
- Adjustable settings: resolution, scene parameters, number of samples per pixel

Technical Overview

Recursive Reflections and Refractions:
- Rays bounce up to a configurable maximum depth
- Reflection rays use the surface normal for perfect mirror-like surfaces
- Refraction rays follow Snell's Law for transparent materials

Camera and Scene Setup:
- Pinhole camera model
- Coordinate system: right-handed, Y-up
- Scene configuration supports multiple objects and lights

Anti-Aliasing:
- Supersampling by shooting multiple rays per pixel and averaging colors
- Reduces jagged edges and improves visual quality

Visual Showcase

<img width="805" height="636" alt="Screenshot 2025-12-12 143108" src="https://github.com/user-attachments/assets/89c75776-f38a-4d37-969c-4837fae31e5a" />

Attribution

- Inspired by Ray Tracing in One Weekend
- Standard C++ STL
- Optional: SDL2, GLM, stb_image

Conclusion

This ray tracer serves as a learning tool and a foundation for more advanced graphics projects. Contributions and enhancements are welcome.
