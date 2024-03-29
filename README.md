# wasm-demo

这个项目主要就来演示如何基于EMScripten来构造Web环境下运行的wasm，并不对WebAssembly做过多解释。

> WebAssembly: https://developer.mozilla.org/en-US/docs/WebAssembly
> EMScripten: https://emscripten.org/
> - Download and install: https://emscripten.org/docs/getting_started/downloads.html

## EMScripten输出模式

1. 输出`html`,`js`,`wasm`3个文件，直接打开`html`就能加载对应的`js`和`wasm`代码。一般用于测试吧，生产里没这么用过；
2. 输出`js`,`wasm`两个文件，使用时自己加载`js`，`js`会自动加载`wasm`；生产中较为常用，但是需要仔细配置构建参数，以便让`js`和调用代码更好的配合；
3. 只输出`wasm`文件，需要自己写`js`代码进行加载，这种情况一般会在`wasm`功能非常简单时使用，因为需要自己手写`js`来加载`wasm`，没有EMScript生成的很多Glue Code，好处是自己写的`js`代码会非常小，同时由于`wasm`中也不需要Glue Code，所以生成的`wasm`也会更小

实际工作中，使用上述2最多，3有时会用。

## 运行方法

在项目目录下执行`npm install`来安装`servez`，然后通过`npm run dev`来启动一个HTTP Server。

## Demo

1. 创建并运行一个最简单的wasm
2. 使用EMScripten生成的js脚本来加载wasm
3. 将wasm打包到js文件中
4. 生成ESM格式的js文件
5. 数据类型和内存管理
6. Debug
7. 使用CMake
8. 使用其它库（未完成）
9. 导出类
10. 编译优化

