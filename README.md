# Route Planning Project

This repository contains tmy solution for the Route Planning project of the Udacity C++ Nanodegree.

<img src="map.png" width="600" height="450" />

## Cloning

When cloning this project, use the `--recurse-submodules` flag. 

## Dependencies
* cmake $\geq$ 3.11.3
  * All operating systems: [Click here for installation instructions](https://cmake.org/install/).
* make $\geq$ 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distributions
  * Mac: [Install Xcode command line tools to get make](https://developer.apple.com/xcode/features/).
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm).
* gcc/g++ $\geq$ 7.4.0
  * Linux: gcc / g++ is installed by default on most Linux distributions.
  * Mac: Same instructions as for make - [Install Xcode command line tools](https://developer.apple.com/xcode/features/).
  * Windows: [MinGW](http://www.mingw.org/).
* IO2D
  * Linux and Windows: Installation instructions can be found [here](https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md).
  * Mac: I recommend following the steps listed out in the [next section](#io2d-on-mac).

[Install and build IO2D on Mac](#io2d-on-mac)

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

