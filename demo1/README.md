# Demo1说明：

Demo1只导出一个简单的WASM文件，实现了一个`add(a, b)`方法和一个`abs(a)`方法。

1. 在`wasm`目录中：
  - 参照`env.example`创建`.env`，并设置`EMSDK_HOME`为本地EMSDK的路径
  - 执行`./build.sh`编译并生成`demo1.wasm`
  - 打开`test.html`，并切换至Console，可以看到输出`3`

请注意：
- 在Chrome浏览器的`Console->Network`中，可以选中下载的wasm文件，然后在*Preview*标签中看到解码后的WASM的内容
- 可以看到，WASM中只包含指定导出的函数，其余函数未被导出，比如`unused()`函数
