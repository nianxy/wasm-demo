# Demo3说明：

Demo3的C代码与Demo1相同，编译会将WASM文件以Base64的形式嵌入到`demo3.js`中，这可以避免程序在运行时还要单独下载WASM文件。不过将WASM文件转为Base64编码，体积会增加`1/3`，所以使用时需要根据实际情况来权衡利弊。

1. 在`wasm`目录中：
  - 参照`env.example`创建`.env`，并设置`EMSDK_HOME`为本地EMSDK的路径
  - 执行`./build.sh`编译并生成`demo3.js`
  - 打开`test.html`，并切换至Console，可以看到输出`3`

关注点：
- 将`emcc`的输出目标指定为`.js`，同时设置编译参数`-s SINGLE_FILE=1`，即可将WASM编译为Base64并嵌入到js文件中
  - 参考： https://emscripten.org/docs/compiling/Building-Projects.html#emscripten-linker-output-files