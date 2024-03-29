# Demo2说明：

Demo2的C代码与Demo1相同，编译时会输出`demo2.wasm`和`demo2.js`，HTML通过引入`demo2.js`来调用WASM方法。

1. 在`wasm`目录中：
  - 参照`env.example`创建`.env`，并设置`EMSDK_HOME`为本地EMSDK的路径
  - 执行`./build.sh`编译并生成`demo2.wasm`和`demo2.js`
  - 打开`test.html`，并切换至Console，可以看到输出`3`

关注点：
- 将`emcc`的输出目标指定为`.js`，即可同时生成js和wasm文件
- 在`demo2.js`加载时，会判断当前环境是否存在名字为`Module`的对象，如果有，则将所有方法注入到这个对象中；如果没有，则创建一个
- 在`test.html`中，加载`demo2.js`之前，手动创建了一个`Module`对象，并设置了一个`onRuntimeInitialized()`方法，该方法将在WASM加载完成后自动调用，我们需要在这个方法被调用以后，才可以调用WASM中的其它方法
  - 可参考 https://emscripten.org/docs/getting_started/FAQ.html#how-can-i-tell-when-the-page-is-fully-loaded-and-it-is-safe-to-call-compiled-functions 获得详细信息
- 在手动创建的`Module`对象中还有一个`locateFile()`方法，用来返回要加载的WASM位置。如果没有这个方法，则JS会自动加载脚本所在位置下的`demo2.wasm`
  - 关于`Module`对象的详细说明： https://emscripten.org/docs/api_reference/module.html

