# ParaSAT

### Requirements
- [CMake](https://cmake.org/download/) >= 3.14
- Compilers with c++17 supports (e.g., gcc-8)

### Build
``` bash
mkdir -p build
cd build
cmake ..
make
```

### Test
This repo does not contain the testing data. To run the tests, [download](http://satcompetition.org/) and place the data as followed. 

| From                        | To                        |
| --------------------------- | ------------------------- |
| SAT Comp. 2018 - main/final | test/data/sc18_main/final |
| SAT Comp. 2018 - random/cnf | test/data/sc18_random/cnf |

Note: the data in `sc18_main` need to be uncompressed. Run below for the pre-processing:
```bash
./script/process_benchmark.py --unzip test/data/sc18_main/final
```

Once the data is ready, tests can be triggered by
```bash
make run  # to run light-weight tests
make hard # to run larger testbenches
```
