# Demo9说明：

> https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html

Demo9导出了一个`Counter`类。

关注点：
- 在链接时，需要链接`embind`库
- 不需要将导出类设置在`EXPORTED_FUNCTIONS`中
