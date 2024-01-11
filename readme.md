## Kerbal ##

language [English](readme.md) | [汉](readme.zh.md)

![Static Badge](https://img.shields.io/badge/zhihu-IceBear-blue?link=https%3A%2F%2Fwww.zhihu.com%2Fpeople%2Fpeter-43-43-80)
![Codacy grade](https://img.shields.io/codacy/grade/d8cf41ae4db84f36bbbab26ff3e3a0bd?link=https%3A%2F%2Fapp.codacy.com%2Fgh%2FWentsingNee%2FKerbal%2Fdashboard)
![Vcpkg Version](https://img.shields.io/vcpkg/v/kerbal)
![License](https://img.shields.io/github/license/WentsingNee/Kerbal)

![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/WentsingNee/Kerbal)
![GitHub test code size in bytes](https://img.shields.io/github/languages/code-size/WentsingNee/KerbalTest?label=code%20size%20of%20test)

![GitHub last commit](https://img.shields.io/github/last-commit/WentsingNee/Kerbal)
![GitHub commit activity](https://img.shields.io/github/commit-activity/y/WentsingNee/Kerbal)
![GitHub commit activity](https://img.shields.io/github/commit-activity/m/WentsingNee/Kerbal)
![GitHub commit activity](https://img.shields.io/github/commit-activity/w/WentsingNee/Kerbal)

C++ template library with:

1) more fundamental features,
2) modern standard library facilities backport to old,
3) **and MORE constexpr**!



### Install ###

#### I) Install via Vcpkg ####

Vcpkg environment is required, see [Vcpkg](https://github.com/microsoft/vcpkg)

```shell
vcpkg install kerbal
```

#### II) Install via Source ####

1) clone repository

```shell
git clone https://github.com/WentsingNee/Kerbal.git
cd Kerbal
```

2) clone git submodules (if you need)

```shell
git submodule init
git submodule update
```

3) configure by CMake

```shell
mkdir build
cmake -S . -B build/ \
    -DCMAKE_BUILD_TYPE=Release

    # the following arguments are optional

    # the path prefix to install Kerbal
    -DCMAKE_INSTALL_PREFIX=`the-path-prefix-you-want-to-install`
    # default is set to your system path

    # the package generator(s) enabled during the cpack stage
    -DCPACK_GENERATOR=`package-generators-you-want`
    # default is set to "DEB;STGZ;TGZ;ZIP"

    # whether install pretty printer files
    # git submodule of `pretty_printer` is required to be existed
    -DKERBAL_INSTALL_PRETTY_PRINTER=True # or False
    # default value is decided by the existence of `pretty_printer` submodule
```

4) install

```shell
cd build
cmake --build . --target install
```

then Kerbal will be installed to `CMAKE_INSTALL_PREFIX`

5) generate package (if you need)

```shell
cd build
cpack .
```



### Integrate Kerbal In Your CMake Project ###

```cmake
find_package(Kerbal REQUIRED)
target_link_libraries(
        your-target PRIVATE
        Kerbal::kerbal
        [Kerbal::kerbal-omp] # maybe required when you have used Kerbal::omp module
)
```



### Sub Libraries Overview ###

| Library                                        | Brief                                                                                                                      |
|------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------|
| [algorithm](include/kerbal/algorithm/)         | algorithm                                                                                                                  |
| [any](include/kerbal/any/)                     | `std::any`-like facility but backport to C++98, together with C++20 constexpr support                                      |
| [assign](include/kerbal/assign/)               | `std::initializer_list`-like facility for C++98                                                                            |
| [autonm](include/kerbal/autonm/)               | autonomous containers, having flexible memory (de)allocation like intrusive containers but have no intrusion to value type |
| [bitset](include/kerbal/bitset/)               | `static_bitset` (like `std::bitset` but have more function and constexpr support)                                          |
| [compare](include/kerbal/compare/)             | comparators and sequence compare                                                                                           |
| [compatibility](include/kerbal/compatibility/) | compatibility macros                                                                                                       |
| [config](include/kerbal/config/)               | architecture, compiler, OS platform, std library environment detection                                                     |
| [container](include/kerbal/container/)         | `array`, `vector`, `static_vector`, `list`, `forward_list`, `priority_queue` ...                                           |
| [function](include/kerbal/function/)           | `function`, `function_traits`, `invoke`, `invoke_r` ...                                                                    |
| [hash](include/kerbal/hash/)                   | hash support                                                                                                               |
| [iterator](include/kerbal/iterator/)           | iterator support                                                                                                           |
| [macro](include/kerbal/macro/)                 | macro utilities                                                                                                            |
| [memory](include/kerbal/memory/)               | memory management support like allocator, uninitialized algorithms                                                         |
| [numeric](include/kerbal/numeric/)             | numeric algorithms                                                                                                         |
| [ompalgo](include/kerbal/ompalgo/)             | openMP accelerated algorithms                                                                                              |
| [openmp](include/kerbal/openmp/)               | openMP facilities and environment detection                                                                                |
| [operators](include/kerbal/operators/)         | use CRTP to simplify operator overload                                                                                     |
| [optional](include/kerbal/optional/)           | `std::optional`-like facility but backport to C++98                                                                        |
| [random](include/kerbal/random/)               | random number engines and distributions                                                                                    |
| [test](include/kerbal/test/)                   | unit test                                                                                                                  |
| [tmp](include/kerbal/tmp/)                     | template meta programming facilities                                                                                       |
| [type_traits](include/kerbal/type_traits/)     | C++11 `<type_traits>`-like facilities but backport part to C++98                                                           |
| [utility](include/kerbal/utility/)             | `compressed_pair`, `tuple` ...                                                                                             |



### Document ###

* Doxygen generated document: click [this](https://wentsingnee.github.io/KerbalDoxygenDoc/)



### Thanks ###

[ThinkSpirit Laboratory](http://thinkspirit.org/) of [Nanjing University of Information
Science and Technology](http://www.nuist.edu.cn/)