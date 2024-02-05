EXPORT_FUNCS = \
    _factorial, \
    _invalid_access, \
    _memory_leak

EXPORT_RUNTIME_FUNCS = 

DEBUG_BUILD_OPTIONS = -g -s ASSERTIONS=2 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=2 -fsanitize=undefined

BUILD_OPTIONS = $(DEBUG_BUILD_OPTIONS)

LINK_FLAG = \
    -s NO_FILESYSTEM \
    -s INITIAL_MEMORY=1MB \
    -s STACK_SIZE=128KB \
    -s ENVIRONMENT="web" \
    -s FILESYSTEM=0 \
    -s EXPORT_ES6=1 \
    --no-entry \
    $(BUILD_OPTIONS)

demo6.js: demo6.c
	emcc -s EXPORTED_FUNCTIONS="[$(EXPORT_FUNCS)]" -s EXPORTED_RUNTIME_METHODS="[$(EXPORT_RUNTIME_FUNCS)]" $^ $(LINK_FLAG) -o $@

all: demo6.js

clean:
	rm -f demo6.js demo6.wasm
