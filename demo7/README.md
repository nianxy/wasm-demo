# Demo4说明：

之前由EMScript生成的JS，会通过一个挂载到浏览器`window`对象下的`Module`对象来访问WASM库，但是，当页面中要加载多个WASM时，这个`Module`对象就会发生冲突了。

Demo4的C代码与Demo1相同，编译会生成ESM格式的JS文件，之前出现的全局`Module`对象作用范围就只会限定在引用该ESM的代码中，这样就不会跟其它的`Module`产生冲突了。

1. 在`wasm`目录中：
  - 参照`env.example`创建`.env`，并设置`EMSDK_HOME`为本地EMSDK的路径
  - 执行`./build.sh`编译并生成`demo4.js`
  - 打开`test.html`，并切换至Console，可以看到输出`3`

关注点：
- 在Makefile中，增加设置两个参数：
  - `-s MODULARIZE=1` 产生模块化输出
  - `-s EXPORT_ES6=1` 使用ES6输出格式
- 原本用于Module对象初始化的配置，可通过Default导出的方法参数传入，对应于本例中`test.html`中的`moduleSettings`
