![alt text](https://github.com/263519/Rover/blob/main/laziczki.png)
![alt text](https://github.com/263519/Rover/blob/main/wybor.png)


## Requirements

To build and run this application, the following system dependencies are required:

* **CMake** (version 3.14 or higher) - Required for project configuration and build generation.
* **Gnuplot** - Required for 3D visual rendering of the Mars Rover and surface scene.
* **Doxygen & Graphviz (dot)** - Optional, only required to generate HTML code documentation.

You can install all necessary packages on Ubuntu/Debian by running:
```bash
sudo apt update && sudo apt install -y cmake gnuplot doxygen graphviz
```

## Building & Running

Follow these steps to configure, build, and run the program:

1. **Create and enter the build directory:**
   ```bash
   mkdir build && cd build
   ```

2. **Configure the project using CMake:**
   *(Options: `-DCMAKE_BUILD_TYPE=[Debug | Coverage | Release]`, `Debug` is default)*
   ```bash
   cmake ..
   ```

3. **Compile the program:**
   ```bash
   make
   ```

4. **Run the main application:**
   ```bash
   ./main
   ```

5. **Run the unit tests:**
   ```bash
   ./tests/unit_tests
   ```

6. **Generate HTML documentation (Optional):**
   ```bash
   make doc
   ```

Things to remember during upgrading project to new task:

* changes to CMakeLists.txt in the main folder with new files added, i.e.:

```cpp
// --------------------------------------------------------------------------------
//                         Locate files (change as needed).
// --------------------------------------------------------------------------------
set(SOURCES          // All .cpp files in src/
    src/Matrix2x2.cpp
    src/Rectangle .cpp
    src/Vector2D.cpp // etc.
)
set(TESTFILES        // All .cpp files in tests/
    Vector2D.cpp
    Matrix2x2.cpp
    Rectangle.cpp // etc.
)
set(LIBRARY_NAME zadX)  // Default name for the library built from src/*.cpp (change if you wish)
```

* changes to tests/CMakeLists.txt (in tests subfolder) with new files added, i.e.:

```cpp
# List all files containing tests. (Change as needed)
set(TESTFILES        // All .cpp files in tests/
    main.cpp
    test_Wektor2D.cpp
    test_Macierz2x2.cpp
    test_Prostokat.cpp // etc.
)
```

The `main.cpp` in the folder `tests` is needed. Only there we define `#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN`.

The main loop of the program is in the `app` folder.
