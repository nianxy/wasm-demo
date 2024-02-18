OPT_FLAG = -O3

LINK_FLAG = \
    -s NO_FILESYSTEM \
    -s INITIAL_MEMORY=1MB \
    -s STACK_SIZE=128KB \
    -s ENVIRONMENT="web" \
    -s FILESYSTEM=0 \
    -s EXPORT_ES6=1 \
    --no-entry

demo10.js: demo10.c
	emcc -s EXPORTED_FUNCTIONS="[_add]" $^ $(LINK_FLAG) $(OPT_FLAG) -o $@

all: demo10.js

clean:
	rm -f demo10.js demo10.wasm
