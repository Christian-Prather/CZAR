#CZAR

## Build instructions
To build CZAR you can do it in two ways, the first is by calling `./Build.sh` from the root of the directory 

This will poduce an executable in the build directory that can be called with three arguments in the build folder `./CZAR 8 source.def output.czr`

The other method is to manually build it with these steps ran from the root directory
* `mkdir build`
* `cd build`
* `cmake ..`
* `make` add -j thread number wanted ex `-j6`

This will produce and executable in the same mannor as the `Build.sh` and can be executed in the same way