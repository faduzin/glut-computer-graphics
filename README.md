# OpenGL and GLUT Projects

This repository contains a collection of projects developed using the **OpenGL Utility Toolkit (GLUT)** library in C. Each project is organized by week, representing progressive learning and experimentation with computer graphics concepts.

## Repository Structure

```
.
├── week-02/           # Projects and code created during week 2
├── week-03/           # Projects and code created during week 3
├── week-04/           # Projects and code created during week 4
├── week-05/           # Projects and code created during week 5
├── week-06/           # Projects and code created during week 6
├── week-09/           # Projects and code created during week 9
├── week-10/           # Projects and code created during week 10
└── README.md          # Repository documentation (this file)
```

Each folder contains the following:
- **`.c` files**: Source code for the respective week's project.
- **Compiled files**: Ready-to-run executables created from the `.c` files.

## How to Compile and Run

To compile and run the `.c` files, you need to have the OpenGL and GLUT development libraries installed. Use the following steps:

1. **Install Required Libraries**:
   - For Linux:
     ```bash
     sudo apt-get install freeglut3-dev
     ```
   - For macOS (with Homebrew):
     ```bash
     brew install freeglut
     ```
   - For Windows: Download and set up the FreeGLUT library from its official site or a trusted source.

2. **Compile the Code**:
   Use the `gcc` compiler with the following parameters:
   ```bash
   gcc -o output_name source_file.c -lglut -lGL -lGLU
   ```
   Replace `output_name` with the desired name for the executable and `source_file.c` with the path to the `.c` file you want to compile.

3. **Run the Program**:
   ```bash
   ./output_name
   ```

## Examples

- To compile and run a file named `example.c` in `week-02`:
  ```bash
  cd week-02
  gcc -o ex1 ex1.c -lglut -lGL -lGLU
  ./ex1
  ```

## Notes

- Ensure the required libraries are properly set up before running the code.
- If any issues arise during compilation, double-check the library paths and ensure OpenGL/GLUT dependencies are correctly installed.

## License

This repository is licensed under the MIT License. Feel free to use, modify, and distribute the code as needed.

## Acknowledgments

Thanks to the creators of the GLUT library and OpenGL for providing powerful tools to learn and implement computer graphics.
