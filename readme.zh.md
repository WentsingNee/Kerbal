## Kerbal ##

language [English](readme.md) | [汉](readme.zh.md)

[![Codacy grade](https://img.shields.io/codacy/grade/d8cf41ae4db84f36bbbab26ff3e3a0bd?label=Codacy&nbsp;代码质量评级)](https://www.codacy.com/gh/WentsingNee/Kerbal/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=WentsingNee/Kerbal&amp;utm_campaign=Badge_Grade)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/WentsingNee/Kerbal?label=代码大小)
![Lines of code](https://img.shields.io/tokei/lines/github/WentsingNee/Kerbal?label=代码总行数)
![GitHub test_code size in bytes](https://img.shields.io/github/languages/code-size/WentsingNee/KerbalTest?label=测试代码大小)
![Lines of test_code](https://img.shields.io/tokei/lines/github/WentsingNee/KerbalTest?label=测试代码总行数)
![License](https://img.shields.io/github/license/WentsingNee/Kerbal?label=协议)

![GitHub last commit](https://img.shields.io/github/last-commit/WentsingNee/Kerbal?label=上次提交)
![GitHub commit activity](https://img.shields.io/github/commit-activity/y/WentsingNee/Kerbal?label=年均提交次数)
![GitHub commit activity](https://img.shields.io/github/commit-activity/m/WentsingNee/Kerbal?label=月均提交次数)
![GitHub commit activity](https://img.shields.io/github/commit-activity/w/WentsingNee/Kerbal?label=周均提交次数)

C++ 模板库, 具有:

1) 更多基础功能,
2) 新版本标准库移植至老版本,
3) **还有更多的 constexpr**!



### 子库 ###

| 库                                              | 简介                                                                             |
|------------------------------------------------|--------------------------------------------------------------------------------|
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
| [ompalgo](include/kerbal/ompalgo/)             | openMP 加速的算法                                                                   |
| [openmp](include/kerbal/openmp/)               | openMP 设施和环境检测                                                                 |
| [operators](include/kerbal/operators/)         | 使用 CRTP 简化运算符重载                                                                |
| [optional](include/kerbal/optional/)           | 与 `std::optional` 相像但是支持 C++98                                                 |
| [random](include/kerbal/random/)               | 随机数生成器和分布                                                                      |
| [test](include/kerbal/test/)                   | 单元测试                                                                           |
| [tmp](include/kerbal/tmp/)                     | 模板元编程设施                                                                        |
| [type_traits](include/kerbal/type_traits/)     | 与 C++11 `<type_traits>` 相像, 但是部分支持 C++98                                       |
| [utility](include/kerbal/utility/)             | `compressed_pair`, `tuple` 等                                                   |



### 文档 ###

* Doxygen 自动生成文档: 点击 [此处](https://wentsingnee.github.io/KerbalDoxygenDoc/) 查看



### 鸣谢 ###

[ThinkSpirit Laboratory](http://thinkspirit.org/) of [Nanjing University of Information
Science and Technology](http://www.nuist.edu.cn/)