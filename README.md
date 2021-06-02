# Route Planning Project

This repository contains tmy solution for the Route Planning project of the Udacity C++ Nanodegree.

<img src="map.png" width="600" height="450" />

## Cloning

When cloning this project, use the `--recurse-submodules` flag. 

## Dependencies
* cmake 3.11.3 or higher
  * All operating systems: [Click here for installation instructions](https://cmake.org/install/).
* make 4.1 or higher (Linux, Mac), 3.81 or higher (Windows) 
  * Linux: make is installed by default on most Linux distributions
  * Mac: [Install Xcode command line tools to get make](https://developer.apple.com/xcode/features/).
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm).
* gcc/g++ 7.4.0 or higher
  * Linux: gcc / g++ is installed by default on most Linux distributions.
  * Mac: Same instructions as for make - [Install Xcode command line tools](https://developer.apple.com/xcode/features/).
  * Windows: [MinGW](http://www.mingw.org/).
* IO2D
  * Linux and Windows: Installation instructions can be found [here](https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md).
  * Mac: I recommend following the steps listed out in the [next section](#install-and-build-io2d-on-mac).

## Install and build IO2D on Mac

The following instructions are adapted from [https://github.com/mylescallan/OpenStreetMaps_C-](https://github.com/mylescallan/OpenStreetMaps_C-).

1. `cd` to the `thirdparty` folder and clone the IO2D files:

```
git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
```

2. Follow the O2D instructions: https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md

3. Install `libpng` using Homebrew: `brew install libpng`

4. Install `cmake` using Homebrew: `brew install cmake`

5. In the ``thirdparty` folder `cd` to `P0267_RefImpl`

```
mkdir Debug && cd Debug
```

Next, when I try to run cmake as described step 5. of [https://github.com/mylescallan/OpenStreetMaps_C-](https://github.com/mylescallan/OpenStreetMaps_C-), I get the error `CMake Error: Unknown argument --config`. What worked for me was to remove the `--config` statement and run only

```
cmake -G "Xcode" -DIO2D_DEFAULT=COREGRAPHICS_MAC ../.
```

```
open io2d.xcodeproj
```

6. In XCode

```
Build "ALL_BUILD"
Build "install"
```

Follow the instructions for compiling and running below.


## Compiling and Running

### Compiling
To compile the project, first, create a `build` directory and change to that directory:
```
mkdir build && cd build
```
From within the `build` directory, then run `cmake` and `make` as follows:
```
cmake ..
make
```
### Running
The executable will be placed in the `build` directory. From within `build`, you can run the project as follows:
```
./OSM_A_star_search
```
Or to specify a map file:
```
./OSM_A_star_search -f ../<your_osm_file.osm>
```

## Testing

The testing executable is also placed in the `build` directory. From within `build`, you can run the unit tests as follows:
```
./test
```

