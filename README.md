# stonefall
The repository for the stonefall.io game.

## Building
To build, first [install cmake](https://cmake.org/install/) (either `sudo apt-get install cmake` or `brew install cmake`). Then, [download the poco source](https://pocoproject.org/download/index.html) and move the folder you've just downloaded, `poco-1.9.0` to `~/dev/dev_apps/`. Then, move into the poco folder and build poco by running
```
mkdir cmake_build
cd cmake_build
cmake ..
make
```
Next, clone the stonefall repository with `git clone https://github.com/stonefallio/stonefall.git`. Then, open up the newly created `stonefall` folder in your IDE of choice. If it asks for a `CMakeLists.txt` file, simply choose the one at the top of the `stonefall` directory. Then, your IDE should be able to build and run Stonefall. To build and run from the command line, simply navigate into the folder and run `/Applications/CLion.app/Contents/bin/cmake/bin/cmake --build ~/stonefall/cmake-build-debug --target stonefall -- -j 4`

If you have the right version of cmake installed, you can also run `cmake --build ~/stonefall/cmake-build-debug --target stonefall -- -j 4`

Finally, `cd` into `cmake-build-debug` and run `./stonefall`. Stonefall is now running on `http://localhost:4567`.

You're all done running Stonefall! Now, let the stones fall!