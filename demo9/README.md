# Demo9说明：

> https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html

Demo9导出了一个`Counter`类。

关注点：
- 在链接时，需要链接`embind`库
- 不需要将导出类设置在`EXPORTED_FUNCTIONS`中
- 通过`embind`导出的函数，无法直接使用指针来传递参数，可以通过`optional_override`来代码函数调用，这样可以不改变原函数的实现
  - 参考： https://stackoverflow.com/a/27364643
