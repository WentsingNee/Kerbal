clang++ -std=c++20 -O2 --precompile -stdlib=libc++ -x c++-module kerbal.cpp -c -I/home/peter/git/Kerbal/include -DKERBAL_ENABLE_MODULES_EXPORT=1

#clang++ -std=c++20 -O2 -c kerbal.pcm  -DKERBAL_ENABLE_MODULES_EXPORT=1

clang++ use.cpp kerbal.pcm -o use -std=c++20 -O2 -I/home/peter/git/Kerbal/include -DKERBAL_ENABLE_MODULES_EXPORT=1 -fmodules -fprebuilt-module-path=. -stdlib=libc++ -lc++ -lc++abi
