
CXX=g++
CXX_FLAGS=-O2 -march=native -g
KERBAL_HEADER_ROOT=/home/peter/git/Kerbal/include
KERBAL_MODULE_HEADER=$(shell bash ./header_list.sh)

#include kerbal_module_header.mk

#gcm.cache$(KERBAL_HEADER_ROOT)/%.gcm: $(KERBAL_HEADER_ROOT)/%
#	$(CXX) -x c++-header $< -std=c++20 -fmodules-ts -c $(CXX_FLAGS)
#
#.PHONY:
#build_kerbal_gcm: $(addprefix gcm.cache$(KERBAL_HEADER_ROOT)/, $(addsuffix .gcm, $(KERBAL_MODULE_HEADER)))


gcm.cache/%.gcm: $(KERBAL_HEADER_ROOT)/%
	$(CXX) -x c++ $< -std=c++20 -fmodules-ts -fmodule-only -c $(CXX_FLAGS)

.PHONY:
build_kerbal_gcm: $(addprefix gcm.cache/, $(addsuffix .gcm, $(KERBAL_MODULE_HEADER)))


test: build_kerbal_gcm test.cpp
	$(CXX) test.cpp -o test -std=c++20 -fmodules-ts -DKERBAL_ENABLE_MODULES_EXPORT=0 -I $(KERBAL_HEADER_ROOT) $(CXX_FLAGS) -DMOH=1
	$(CXX) test.cpp -S -o /dev/stdout -std=c++20 -fmodules-ts -DKERBAL_ENABLE_MODULES_EXPORT=0 -I $(KERBAL_HEADER_ROOT) $(CXX_FLAGS) -DMOH=1 | c++filt > test.asm

test2: test.cpp
	$(CXX) test.cpp -o test2 -std=c++11 -fmodules-ts -DKERBAL_ENABLE_MODULES_EXPORT=0 $(CXX_FLAGS) -DMOH=0

.PHONY:
all: build_kerbal_gcm test


.PHONY:
clean:
	-rm -r ./gcm.cache
	-rm *.o
	-rm test
	-rm test2



.PHONY:
list_kerbal_module:
	echo
	echo
	echo
	echo
	echo $(KERBAL_MODULE_HEADER)
