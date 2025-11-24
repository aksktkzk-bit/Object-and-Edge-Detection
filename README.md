# Detecting Simple Objects and Edges (Modular C Project)
This project is a modular C-based image processing pipeline for PPM (P6) images.
It performs grayscale conversion, adaptive thresholding, dark-pixel detection,
Gaussian blur, Canny edge detection with non-maximum suppression, and small-component
removal. The project is organized into reusable modules and builds cleanly using a Makefile.

# Included files
Testcases: Includes images that can be used for testing
src: includes codes
include: includes header files

# How To Use
Input-- Add the input image as a .ppm file in the project directory
Compile-- Use the makefile to compile (terminal command: make or mingw-make(for windows))
Run-- terminal command: ./ppmproc input_filename.ppm output_prefix

3 output files will be created:
    1. output_prefix_dark_pixels_red  (separation of object and background)
    2. output_prefix_red_only (separated binary image (red and white image))
    3. output_prefix_edges_cleaned (the detected object edge against black background)

# Overview 
The project does not simply use a guassian blur with canny detection but instead first identifies dark clusters of similar intensity pixels and makes a separated red and white image. A gaussian blur and edge detection is then run on the binary image. Few intermediate noise filtering steps are also executed.

# Recreation and improvements
To recreate a similar tool in C, the basic pipeline to be followed is:
input.ppm
   ↓
PPM Loader
   ↓
Grayscale
   ↓
Noise filter (optional)
   ↓
Clustering
   ↓
Gaussian Blur
   ↓
Canny Edge Detection
   ↓
Threshold
   ↓
Components / Masking
   ↓
Recolor / Highlight
   ↓
output.ppm

For improvements, libraries such as OpenCV can be used. (An older version of opencv is available for C)

# Authors
1. Mohmad Abdul Quadir
2. Siddharth Arya
3. Om Londhe