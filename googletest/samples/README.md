### How to Build Sample Unit Test

Check 1
option(BUILD_GMOCK "Builds the googlemock subproject" OFF)

Check 2
option(gtest_build_samples "Build gtest's sample programs." ON)


```
git clone https://github.com/google/googletest.git
cd googletest
mkdir build
cd build
cmake ..
make
```