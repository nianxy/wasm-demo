LINK_FLAG = \
    -s NO_FILESYSTEM \
    -s INITIAL_MEMORY=1MB \
    -s STACK_SIZE=128KB \
    -s ENVIRONMENT="web" \
    -s FILESYSTEM=0 \
    -s EXPORT_ES6=1 \
    --no-entry

demo4.js: demo4.c
	emcc -s EXPORTED_FUNCTIONS="[_add,_abs]" $^ $(LINK_FLAG) -o $@

all: demo4.js

clean:
	rm -f demo4.js demo4.wasm
