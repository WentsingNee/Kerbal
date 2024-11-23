## Kerbal ##

language [English](readme.md) | [汉](readme.zh.md)

![Static Badge](https://img.shields.io/badge/%E7%9F%A5%E4%B9%8E-IceBear-blue?link=https%3A%2F%2Fwww.zhihu.com%2Fpeople%2Fpeter-43-43-80)
![Codacy grade](https://img.shields.io/codacy/grade/d8cf41ae4db84f36bbbab26ff3e3a0bd?label=%E4%BB%A3%E7%A0%81%E8%B4%A8%E9%87%8F%E8%AF%84%E7%BA%A7&link=https%3A%2F%2Fapp.codacy.com%2Fgh%2FWentsingNee%2FKerbal%2Fdashboard)
![License](https://img.shields.io/github/license/WentsingNee/Kerbal?label=%E5%8D%8F%E8%AE%AE)

![Vcpkg Version](https://img.shields.io/vcpkg/v/kerbal)
![NuGet Version](https://img.shields.io/nuget/v/Kerbal)

![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/WentsingNee/Kerbal?label=%E4%BB%A3%E7%A0%81%E5%A4%A7%E5%B0%8F)
![GitHub test code size in bytes](https://img.shields.io/github/languages/code-size/WentsingNee/KerbalTest?label=%E6%B5%8B%E8%AF%95%E4%BB%A3%E7%A0%81%E5%A4%A7%E5%B0%8F)

![GitHub last commit](https://img.shields.io/github/last-commit/WentsingNee/Kerbal?label=%E4%B8%8A%E6%AC%A1%E6%8F%90%E4%BA%A4)
![GitHub commit activity](https://img.shields.io/github/commit-activity/y/WentsingNee/Kerbal?label=%E5%B9%B4%E5%9D%87%E6%8F%90%E4%BA%A4%E6%AC%A1%E6%95%B0)
![GitHub commit activity](https://img.shields.io/github/commit-activity/m/WentsingNee/Kerbal?label=%E6%9C%88%E5%9D%87%E6%8F%90%E4%BA%A4%E6%AC%A1%E6%95%B0)
![GitHub commit activity](https://img.shields.io/github/commit-activity/w/WentsingNee/Kerbal?label=%E5%91%A8%E5%9D%87%E6%8F%90%E4%BA%A4%E6%AC%A1%E6%95%B0)

C++ 模板库, 具有:

1) 更多基础功能,
2) 新版本标准库移植至老版本,
3) **还有更多的 constexpr**!



### 安装说明 ###

#### I) 通过包管理安装

##### 1. Vcpkg #####

必须有 Vcpkg 环境, 详见: [Vcpkg](https://github.com/microsoft/vcpkg)

```shell
vcpkg install kerbal
```

##### 2. NuGet #####

详见: [本项目主页](https://www.nuget.org/packages/Kerbal)

```shell
nuget install kerbal
```

#### II) 通过源码安装 ####

1) 克隆仓库

```shell
git clone https://github.com/WentsingNee/Kerbal.git
cd Kerbal
```

2) 克隆 git 子模块仓库 (如果你需要的话)

```shell
git submodule init
git submodule update
```

3) 通过 CMake 配置

```shell
mkdir build
cmake -S . -B build/ \
    -DCMAKE_BUILD_TYPE=Release

    # 以下参数是可选的

    # 安装 Kerbal 的目录前缀
    -DCMAKE_INSTALL_PREFIX=`你想要的目录前缀`
    # 默认会被设置为你的系统目录

    # cpack 阶段要启用的包生成器
    -DCPACK_GENERATOR=`你想要的包生成器`
    # 默认设为: "DEB;STGZ;TGZ;ZIP"

    # 是否要安装 pretty printer 文件
    # git `pretty_printer` 子模块必须已存在
    -DKERBAL_INSTALL_PRETTY_PRINTER=True # 或者是 False
    # 默认值是根据 git `pretty_printer` 子模块是否已存在决定的
```

4) 安装

```shell
cd build
cmake --build . --target install
```

执行完毕后, Kerbal 就会被安装进 `CMAKE_INSTALL_PREFIX` 目录中

5) 生成安装包 (如果你需要的话)

```shell
cd build
cpack .
```



### 将 Kerbal 集成进你的 CMake 项目 ###

```cmake
find_package(Kerbal REQUIRED)
target_link_libraries(
        your-target PRIVATE
        Kerbal::kerbal
        [Kerbal::kerbal-omp] # 当你使用到 Kerbal::omp 模块时, 这行可能是需要的
)
```



### 子库 ###

| 库                                              | 简介                                                                             |
|------------------------------------------------|--------------------------------------------------------------------------------|
| Kerbal::kerbal                                 |                                                                                |
| [algorithm](include/kerbal/algorithm/)         | 算法                                                                             |
| [any](include/kerbal/any/)                     | 与 `std::any` 相像但是支持 C++98 和 C++20 constexpr                                    |
| [assign](include/kerbal/assign/)               | 在 C++98 中像 C++11 中的 `std::initializer_list`一样初始化容器                             |
| [autonm](include/kerbal/autonm/)               | 自治容器, 与侵入式容器一样支持灵活的分配/解分配，但是对类型没有侵入性                                           |
| [bitset](include/kerbal/bitset/)               | `static_bitset` (与 `std::bitset` 但是有更多功能和 constexpr 支持)                        |
| [compare](include/kerbal/compare/)             | 比较器和序列比较                                                                       |
| [compatibility](include/kerbal/compatibility/) | 为兼容性提供的宏                                                                       |
| [config](include/kerbal/config/)               | 架构, 编译器, 系统平台, 标准库环境检测                                                         |
| [container](include/kerbal/container/)         | `array`, `vector`, `static_vector`, `list`, `forward_list`, `priority_queue` 等 |
| [function](include/kerbal/function/)           | `function`, `function_traits`, `invoke`, `invoke_r` 等                          |
| [hash](include/kerbal/hash/)                   | 哈希支持                                                                           |
| [iterator](include/kerbal/iterator/)           | 迭代器支持                                                                          |
| [macro](include/kerbal/macro/)                 | 宏设施                                                                            |
| [memory](include/kerbal/memory/)               | 内存管理支持, 如 allocator, 未初始化算法                                                    |
| [numeric](include/kerbal/numeric/)             | 数值算法                                                                           |
| [operators](include/kerbal/operators/)         | 使用 CRTP 简化运算符重载                                                                |
| [optional](include/kerbal/optional/)           | 与 `std::optional` 相像但是支持 C++98                                                 |
| [random](include/kerbal/random/)               | 随机数生成器和分布                                                                      |
| [smath](include/kerbal/smath/)                 | 静态数学运算                                                                         |
| [test](include/kerbal/test/)                   | 单元测试                                                                           |
| [tmp](include/kerbal/tmp/)                     | 模板元编程设施                                                                        |
| [type_traits](include/kerbal/type_traits/)     | 与 C++11 `<type_traits>` 相像, 但是部分支持 C++98                                       |
| [utility](include/kerbal/utility/)             | `compressed_pair`, `tuple` 等                                                   |
| Kerbal::kerbal-coroutine                       |                                                                                |
| [coroutine](include/kerbal/coroutine/)         | 协程设施                                                                           |
| Kerbal::kerbal-omp                             |                                                                                |
| [ompalgo](include/kerbal/ompalgo/)             | openMP 加速的算法                                                                   |
| [openmp](include/kerbal/openmp/)               | openMP 设施和环境检测                                                                 |
| Kerbal::kerbal-parallel                        |                                                                                |
| [parallel](include/kerbal/parallel/)           | 并行设施                                                                           |



### 文档 ###

* Doxygen 自动生成文档: 点击 [此处](https://wentsingnee.github.io/KerbalDoxygenDoc/) 查看



### 鸣谢 ###

[ThinkSpirit Laboratory](http://thinkspirit.org/) of [Nanjing University of Information
Science and Technology](http://www.nuist.edu.cn/)