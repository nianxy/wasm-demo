LINK_FLAG = \
    -s NO_FILESYSTEM \
    -s INITIAL_MEMORY=1MB \
    -s STACK_SIZE=128KB \
    -s ENVIRONMENT="web" \
    -s FILESYSTEM=0 \
    -s SINGLE_FILE=1 \
    --no-entry

demo3.js: demo3.c
	emcc -s EXPORTED_FUNCTIONS="[_add,_abs]" $^ $(LINK_FLAG) -o $@

all: demo3.js

clean:
	rm -f demo3.js
