clang++ \
-D__cpp_modules \
-std=c++2a -O2 -fmodules-ts --precompile -x c++-module \
-o kerbal_type_traits.pcm \
../include/kerbal/type_traits/type_traits.hpp
