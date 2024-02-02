# wasm-demo

基于EMScripten来构造Web环境下运行的wasm.

> EMScripten: https://emscripten.org/

## EMScripten输出模式

1. 输出`html`,`js`,`wasm`3个文件，直接打开`html`就能加载对应的`js`和`wasm`代码。一般用于测试吧，生产里没这么用过；
2. 输出`js`,`wasm`两个文件，使用时自己加载`js`，`js`会自动加载`wasm`；生产中较为常用，但是需要仔细配置构建参数，以便让`js`和调用代码更好的配合；
3. 只输出`wasm`文件，需要自己写`js`代码进行加载，这种情况一般会在`wasm`功能非常简单时使用，因为需要自己手写`js`来加载`wasm`，没有EMScript生成的很多Glue Code，好处是自己写的`js`代码会非常小，同时由于`wasm`中也不需要Glue Code，所以生成的`wasm`也会更小

实际工作中，使用上述2最多，3有时会用。

在Step1中，我们先看下第3种情况的开发方法。

## Demo步骤

1. 创建并运行一个最简单的wasm
2. EMScripten生成wasm的不同方式
3. 将wasm打包到js文件中
4. wasm内存管理
