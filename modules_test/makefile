
PCM_DIR = ./pcm

PRECOMPILE_MODULES += \
$(PCM_DIR)/kerbal.compatibility.move.pcm \
$(PCM_DIR)/kerbal.function.function_traits.pcm \
$(PCM_DIR)/kerbal.iterator.iterator.pcm \
$(PCM_DIR)/kerbal.iterator.iterator_traits.pcm \
$(PCM_DIR)/kerbal.operators.addable.pcm \
$(PCM_DIR)/kerbal.operators.dereferenceable.pcm \
$(PCM_DIR)/kerbal.operators.equality_comparable.pcm \
$(PCM_DIR)/kerbal.operators.generic_assign.pcm \
$(PCM_DIR)/kerbal.operators.incr_decr.pcm \
$(PCM_DIR)/kerbal.operators.less_than_comparable.pcm \
$(PCM_DIR)/kerbal.operators.subtractable.pcm \
$(PCM_DIR)/kerbal.type_traits.pcm \
$(PCM_DIR)/kerbal.utility.addressof.pcm \
$(PCM_DIR)/kerbal.utility.as_const.pcm \
$(PCM_DIR)/kerbal.utility.declval.pcm \
$(PCM_DIR)/kerbal.utility.forward.pcm \
$(PCM_DIR)/kerbal.utility.in_place.pcm \
$(PCM_DIR)/kerbal.utility.integer_sequence.pcm \
$(PCM_DIR)/kerbal.utility.member_compress_helper.pcm \
$(PCM_DIR)/kerbal.utility.noncopyable.pcm \
$(PCM_DIR)/kerbal.utility.reference_wrapper.pcm \
$(PCM_DIR)/kerbal.utility.throw_this_exception.pcm \


#./pcm/%.pcm : modules/%.cc
#	mkdir -p ./pcm
#	clang++ -std=c++2a -fmodules-ts --precompile -x c++-module -o "$@" "$<"


define build_pre_compiled_module
	@-mkdir -p pcm
	clang++ \
	$(1) \
	-o $(2) \
	-std=c++2a -O2 -c -fmodules -Xclang -emit-module-interface \
	-DKERBAL_ENABLE_MODULES \
	$(3) \
	-stdlib=libc++
endef

$(PCM_DIR)/kerbal.compatibility.move.pcm : $(PCM_DIR)/kerbal.type_traits.pcm
	$(call build_pre_compiled_module, \
		../include/kerbal/compatibility/move.hpp, \
		$(PCM_DIR)/kerbal.compatibility.move.pcm, \
		-fmodule-file=$(PCM_DIR)/kerbal.type_traits.pcm \
	)

$(PCM_DIR)/kerbal.function.function_traits.pcm : $(PCM_DIR)/kerbal.type_traits.pcm
	$(call build_pre_compiled_module, \
		../include/kerbal/function/function_traits.hpp, \
		$(PCM_DIR)/kerbal.function.function_traits.pcm, \
		-fmodule-file=$(PCM_DIR)/kerbal.type_traits.pcm \
	)

$(PCM_DIR)/kerbal.iterator.iterator_traits.pcm : $(PCM_DIR)/kerbal.type_traits.pcm
	$(call build_pre_compiled_module, \
		../include/kerbal/iterator/iterator_traits.hpp, \
		$(PCM_DIR)/kerbal.iterator.iterator_traits.pcm, \
		-fmodule-file=$(PCM_DIR)/kerbal.type_traits.pcm \
	)

$(PCM_DIR)/kerbal.iterator.iterator.pcm : \
		$(PCM_DIR)/kerbal.type_traits.pcm \
		$(PCM_DIR)/kerbal.iterator.iterator_traits.pcm
	$(call build_pre_compiled_module, \
		../include/kerbal/iterator/iterator.hpp, \
		$(PCM_DIR)/kerbal.iterator.iterator.pcm, \
		-fmodule-file=$(PCM_DIR)/kerbal.iterator.iterator_traits.pcm \
	)

$(PCM_DIR)/kerbal.operators.addable.pcm :
	$(call build_pre_compiled_module, \
		../include/kerbal/operators/addable.hpp, \
		$(PCM_DIR)/kerbal.operators.addable.pcm \
	)

$(PCM_DIR)/kerbal.operators.dereferenceable.pcm : $(PCM_DIR)/kerbal.utility.declval.pcm
	$(call build_pre_compiled_module, \
		../include/kerbal/operators/dereferenceable.hpp, \
		$(PCM_DIR)/kerbal.operators.dereferenceable.pcm, \
		-fmodule-file=$(PCM_DIR)/kerbal.utility.declval.pcm \
	)

$(PCM_DIR)/kerbal.operators.equality_comparable.pcm :
	$(call build_pre_compiled_module, \
		../include/kerbal/operators/equality_comparable.hpp, \
		$(PCM_DIR)/kerbal.operators.equality_comparable.pcm \
	)

$(PCM_DIR)/kerbal.operators.generic_assign.pcm : \
		$(PCM_DIR)/kerbal.type_traits.pcm \
		$(PCM_DIR)/kerbal.utility.forward.pcm
	$(call build_pre_compiled_module, \
		../include/kerbal/operators/generic_assign.hpp, \
		$(PCM_DIR)/kerbal.operators.generic_assign.pcm, \
		-fmodule-file=$(PCM_DIR)/kerbal.type_traits.pcm \
		-fmodule-file=$(PCM_DIR)/kerbal.utility.forward.pcm \
	)

$(PCM_DIR)/kerbal.operators.incr_decr.pcm :
	$(call build_pre_compiled_module, \
		../include/kerbal/operators/incr_decr.hpp, \
		$(PCM_DIR)/kerbal.operators.incr_decr.pcm \
	)

$(PCM_DIR)/kerbal.operators.less_than_comparable.pcm :
	$(call build_pre_compiled_module, \
		../include/kerbal/operators/incr_decr.hpp, \
		$(PCM_DIR)/kerbal.operators.incr_decr.pcm \
	)

$(PCM_DIR)/kerbal.operators.subtractable.pcm :
	$(call build_pre_compiled_module, \
		../include/kerbal/operators/incr_decr.hpp, \
		$(PCM_DIR)/kerbal.operators.incr_decr.pcm \
	)

$(PCM_DIR)/kerbal.random.mersenne_twister_engine.pcm : $(PCM_DIR)/kerbal.type_traits.pcm
	$(call build_pre_compiled_module, \
		../include/kerbal/random/mersenne_twister_engine.hpp, \
		$(PCM_DIR)/kerbal.random.mersenne_twister_engine.pcm, \
		-fmodule-file=$(PCM_DIR)/kerbal.type_traits.pcm \
	)

$(PCM_DIR)/kerbal.type_traits.pcm :
	$(call build_pre_compiled_module, \
		../include/kerbal/type_traits/type_traits.hpp, \
		$(PCM_DIR)/kerbal.type_traits.pcm \
	)

$(PCM_DIR)/kerbal.utility.addressof.pcm :
	$(call build_pre_compiled_module, \
		../include/kerbal/utility/addressof.hpp, \
		$(PCM_DIR)/kerbal.utility.addressof.pcm \
	)

$(PCM_DIR)/kerbal.utility.as_const.pcm : $(PCM_DIR)/kerbal.type_traits.pcm
	$(call build_pre_compiled_module, \
		../include/kerbal/utility/as_const.hpp, \
		$(PCM_DIR)/kerbal.utility.as_const.pcm, \
		-fmodule-file=$(PCM_DIR)/kerbal.type_traits.pcm \
	)

$(PCM_DIR)/kerbal.utility.declval.pcm : $(PCM_DIR)/kerbal.type_traits.pcm
	$(call build_pre_compiled_module, \
		../include/kerbal/utility/declval.hpp, \
		$(PCM_DIR)/kerbal.utility.declval.pcm, \
		-fmodule-file=$(PCM_DIR)/kerbal.type_traits.pcm \
	)

$(PCM_DIR)/kerbal.utility.forward.pcm : $(PCM_DIR)/kerbal.type_traits.pcm
	$(call build_pre_compiled_module, \
		../include/kerbal/utility/forward.hpp, \
		$(PCM_DIR)/kerbal.utility.forward.pcm, \
		-fmodule-file=$(PCM_DIR)/kerbal.type_traits.pcm \
	)

$(PCM_DIR)/kerbal.utility.in_place.pcm :
	$(call build_pre_compiled_module, \
		../include/kerbal/utility/in_place.hpp, \
		$(PCM_DIR)/kerbal.utility.in_place.pcm \
	)

$(PCM_DIR)/kerbal.utility.integer_sequence.pcm :
	$(call build_pre_compiled_module, \
		../include/kerbal/utility/integer_sequence.hpp, \
		$(PCM_DIR)/kerbal.utility.integer_sequence.pcm \
	)

$(PCM_DIR)/kerbal.utility.member_compress_helper.pcm : \
		$(PCM_DIR)/kerbal.compatibility.move.pcm \
		$(PCM_DIR)/kerbal.operators.generic_assign.pcm \
		$(PCM_DIR)/kerbal.type_traits.pcm \
		$(PCM_DIR)/kerbal.utility.declval.pcm \
		$(PCM_DIR)/kerbal.utility.in_place.pcm \
		$(PCM_DIR)/kerbal.utility.noncopyable.pcm
	$(call build_pre_compiled_module, \
		../include/kerbal/utility/member_compress_helper.hpp, \
		$(PCM_DIR)/kerbal.utility.member_compress_helper.pcm, \
		-fmodule-file=$(PCM_DIR)/kerbal.compatibility.move.pcm \
		-fmodule-file=$(PCM_DIR)/kerbal.operators.generic_assign.pcm \
		-fmodule-file=$(PCM_DIR)/kerbal.type_traits.pcm \
		-fmodule-file=$(PCM_DIR)/kerbal.utility.declval.pcm \
		-fmodule-file=$(PCM_DIR)/kerbal.utility.in_place.pcm \
		-fmodule-file=$(PCM_DIR)/kerbal.utility.noncopyable.pcm \
	)


$(PCM_DIR)/kerbal.utility.noncopyable.pcm :
	$(call build_pre_compiled_module, \
		../include/kerbal/utility/noncopyable.hpp, \
		$(PCM_DIR)/kerbal.utility.noncopyable.pcm \
	)

$(PCM_DIR)/kerbal.utility.reference_wrapper.pcm :
	$(call build_pre_compiled_module, \
		../include/kerbal/utility/reference_wrapper.hpp, \
		$(PCM_DIR)/kerbal.utility.reference_wrapper.pcm \
	)

$(PCM_DIR)/kerbal.utility.throw_this_exception.pcm : $(PCM_DIR)/kerbal.utility.forward.pcm
	$(call build_pre_compiled_module, \
		../include/kerbal/utility/reference_wrapper.hpp, \
		$(PCM_DIR)/kerbal.utility.reference_wrapper.pcm, \
		-fmodule-file=$(PCM_DIR)/kerbal.utility.forward.pcm \
	)

OBJS += \
./obj/modules_example.o


./obj/%.o : ./src/%.cpp $(PRECOMPILE_MODULES)
	clang++ \
	-std=c++2a -O2 \
	-fmodules \
	-fmodule-file=$(PCM_DIR)/kerbal.type_traits.pcm \
	-fmodule-file=$(PCM_DIR)/kerbal.iterator.iterator_traits.pcm \
	-fmodule-file=$(PCM_DIR)/kerbal.iterator.iterator.pcm \
	-fmodule-file=$(PCM_DIR)/kerbal.operators.addable.pcm \
	-fmodule-file=$(PCM_DIR)/kerbal.operators.equality_comparable.pcm \
	-fmodule-file=$(PCM_DIR)/kerbal.utility.addressof.pcm \
	-fmodule-file=$(PCM_DIR)/kerbal.utility.in_place.pcm \
	-fmodule-file=$(PCM_DIR)/kerbal.utility.member_compress_helper.pcm \
	-stdlib=libc++ \
	-o "$@" -c "$<"


.PHONY: all
all: $(OBJS)
	clang++ -o main $(OBJS) -std=libc++ -lc++ -lc++abi

.PHONY: clean
clean:
	$(RM) $(PRECOMPILE_MODULES) $(OBJS) main
