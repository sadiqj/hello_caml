#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)
COMPONENT_EXTRA_INCLUDES := $(shell opam config var lib)/ocaml/
COMPONENT_ADD_LDFLAGS := -l$(COMPONENT_NAME) $(COMPONENT_PATH)/../lib/libcamlrun.a $(COMPONENT_BUILD_DIR)/hello_caml.o -z muldefs
COMPONENT_EXTRA_CLEAN := $(COMPONENT_BUILD_DIR)/hello_caml.c
COMPONENT_SRCDIRS := .

hello_caml.c: $(COMPONENT_PATH)/hello.ml
	rm -f hello_caml.c
	ocamlc -g -custom -output-obj -o hello_caml.c $(COMPONENT_PATH)/hello.ml

hello_caml.o: hello_caml.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(addprefix -I ,$(COMPONENT_INCLUDES)) $(addprefix -I ,$(COMPONENT_EXTRA_INCLUDES)) -c $< -o $@

build: hello_caml.o
