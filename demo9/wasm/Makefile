LINK_FLAG = \
    -g \
    -s NO_FILESYSTEM \
    -s INITIAL_MEMORY=1MB \
    -s STACK_SIZE=128KB \
    -s ENVIRONMENT="web" \
    -s FILESYSTEM=0 \
    -s EXPORT_ES6=1 \
    --no-entry

LIBS = \
    -lembind

demo9.js: demo9.cpp
	emcc $^ -s EXPORTED_RUNTIME_METHODS="[_malloc,_free]" $(LINK_FLAG) ${LIBS} -o $@

all: demo9.js

clean:
	rm -f demo9.js demo9.wasm
