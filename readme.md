## Kerbal ##

language [English](readme.md) | [汉](readme.zh.md)

[![Codacy grade](https://img.shields.io/codacy/grade/d8cf41ae4db84f36bbbab26ff3e3a0bd)](https://www.codacy.com/gh/WentsingNee/Kerbal/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=WentsingNee/Kerbal&amp;utm_campaign=Badge_Grade)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/WentsingNee/Kerbal)
![Lines of code](https://img.shields.io/tokei/lines/github/WentsingNee/Kerbal)
![GitHub test code size in bytes](https://img.shields.io/github/languages/code-size/WentsingNee/KerbalTest?label=code%20size%20of%20test)
![Lines of test code](https://img.shields.io/tokei/lines/github/WentsingNee/KerbalTest?label=total%20lines%20of%20test%20code)
![License](https://img.shields.io/github/license/WentsingNee/Kerbal)

![GitHub last commit](https://img.shields.io/github/last-commit/WentsingNee/Kerbal)
![GitHub commit activity](https://img.shields.io/github/commit-activity/y/WentsingNee/Kerbal)
![GitHub commit activity](https://img.shields.io/github/commit-activity/m/WentsingNee/Kerbal)
![GitHub commit activity](https://img.shields.io/github/commit-activity/w/WentsingNee/Kerbal)

C++ template library with:

1) more fundamental features,
2) modern standard library facilities backport to old,
3) **and MORE constexpr**!

### Sub Libraries overview ###

| Library                                        | Brief                                                                                                                     |
|------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------|
| [algorithm](include/kerbal/algorithm/)         | algorithm                                                                                                                 |
| [any](include/kerbal/any/)                     | `std::any`-like facility but backport to C++98, together with C++20 constexpr support                                     |
| [assign](include/kerbal/assign/)               | `std::initializer_list`-like facility for C++98                                                                           |
| [autonm](include/kerbal/autonm/)               | autonomous containers, having flexible memory (de)allocation like intrusive containers but have no intrusion to value type |
| [bitset](include/kerbal/bitset/)               | `static_bitset` (like `std::bitset` but have more function and constexpr support)                                         |
| [compare](include/kerbal/compare/)             | comparators and sequence compare                                                                                          |
| [compatibility](include/kerbal/compatibility/) | compatibility macros                                                                                                      |
| [config](include/kerbal/config/)               | architecture, compiler, OS platform, std library environment detection                                                    |
| [container](include/kerbal/container/)         | `array`, `vector`, `static_vector`, `list`, `forward_list`, `priority_queue`, ...                                         |
| [function](include/kerbal/function/)           | `function`, `function_traits`, `invoke`, `invoke_r`...                                                                    |
| [hash](include/kerbal/hash/)                   | hash support                                                                                                              |
| [iterator](include/kerbal/iterator/)           | iterator support                                                                                                          |
| [macro](include/kerbal/macro/)                 | macro utilities                                                                                                           |
| [memory](include/kerbal/memory/)               | memory management support like allocator, uninitialized algorithms                                                        |
| [numeric](include/kerbal/numeric/)             | numeric algorithms                                                                                                        |
| [ompalgo](include/kerbal/ompalgo/)             | openMP accelerated algorithms                                                                                             |
| [openmp](include/kerbal/openmp/)               | openMP facilities and environment detection                                                                               |
| [operators](include/kerbal/operators/)         | use CRTP to simplify operator overload                                                                                    |
| [optional](include/kerbal/optional/)           | `std::optional`-like facility but backport to C++98                                                                       |
| [random](include/kerbal/random/)               | random number engines and distributions                                                                                   |
| [test](include/kerbal/test/)                   | unit test                                                                                                                 |
| [tmp](include/kerbal/tmp/)                     | template meta programming facilities                                                                                      |
| [type_traits](include/kerbal/type_traits/)     | C++11 `<type_traits>`-like facilities but backport part to C++98                                                          |
| [utility](include/kerbal/utility/)             | `compressed_pair`, `tuple`, ...                                                                                           |

### Document ###

* Doxygen generated document: click [this](https://wentsingnee.github.io/KerbalDoxygenDoc/)

### Thanks ###

[ThinkSpirit Laboratory](http://thinkspirit.org/) of [Nanjing University of Information
Science and Technology](http://www.nuist.edu.cn/)