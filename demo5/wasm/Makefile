EXPORT_FUNCS = \
    _string_duplicate, \
    _plus100, \
    _plus100f, \
    _rgb_to_gray, \
    _malloc, \
    _free

EXPORT_RUNTIME_FUNCS = \
    UTF8ToString, \
    stringToUTF8

LINK_FLAG = \
    -s NO_FILESYSTEM \
    -s INITIAL_MEMORY=1MB \
    -s STACK_SIZE=128KB \
    -s ENVIRONMENT="web" \
    -s FILESYSTEM=0 \
    -s SINGLE_FILE=1 \
    -s MODULARIZE=1 \
    -s EXPORT_ES6=1 \
    --no-entry

demo5.js: demo5.c
	emcc -s EXPORTED_FUNCTIONS="[$(EXPORT_FUNCS)]" -s EXPORTED_RUNTIME_METHODS="[$(EXPORT_RUNTIME_FUNCS)]" $^ $(LINK_FLAG) -o $@

all: demo5.js

clean:
	rm -f demo5.js
