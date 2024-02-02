LINK_FLAG = \
    -s STANDALONE_WASM \
    -s NO_FILESYSTEM \
    -s INITIAL_MEMORY=1MB \
    -s STACK_SIZE=128KB \
    -s ENVIRONMENT="web" \
    -s FILESYSTEM=0 \
    --no-entry

step1.wasm: step1.c
	emcc -s EXPORTED_FUNCTIONS="[_add,_abs]" $^ $(LINK_FLAG) -o $@

all: step1.wasm
