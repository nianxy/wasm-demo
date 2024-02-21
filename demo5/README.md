# Demo5说明：


https://emscripten.org/docs/porting/connecting_cpp_and_javascript/Interacting-with-code.html#access-memory-from-javascript


从JS到WASM进行数据传递时，对于`number`类型的数据，包括`int`,`float`,`double`，可以直接传递，其它类型都需要传指针。

这个Demo演示了如何传递字符串（包括传入、传出）和图片。

## EMScript内存模型

> - INITIAL_MEMORY: https://emscripten.org/docs/tools_reference/settings_reference.html#initial-memory
> - ALLOW_MEMORY_GROWTH: https://emscripten.org/docs/tools_reference/settings_reference.html#allow-memory-growth
> - MAXIMUM_MEMORY: https://emscripten.org/docs/tools_reference/settings_reference.html#maximum-memory

WASM在加载时，会在JS中初始化一块内存做为WASM运行时使用。这块内存本质上就是JS中的`ArrayBuffer`，初始大小在编译时通过`INITIAL_MEMORY`指定。如果内存不足，将根据编译参数`ALLOW_MEMORY_GROWTH`来决定是否允许扩充内存。在扩充内存时，将会申请一块新的`ArrayBuffer`，并将现在的`ArrayBuffer`中的数据Copy至新的区域，然后释放当前Buffer。

如果通过EMScripten生成的JS来使用WASM，则该JS的Module对象中会包括一些内存管理的快捷对象，比如：

```javascript
// 下面这些对象指向的是同一块内存区域，也就是WASM申请的ArrayBuffer
// 这些对象只是提供了对这块内存区域的便捷访问方法
// 比如，当使用 Module.HEAPU8 时，就相当于将ArrayBuffer当作Uint8Array来处理
Module['HEAP8'] = HEAP8 = new Int8Array(buf);
Module['HEAP16'] = HEAP16 = new Int16Array(buf);
Module['HEAP32'] = HEAP32 = new Int32Array(buf);
Module['HEAPU8'] = HEAPU8 = new Uint8Array(buf);
Module['HEAPU16'] = HEAPU16 = new Uint16Array(buf);
Module['HEAPU32'] = HEAPU32 = new Uint32Array(buf);
Module['HEAPF32'] = HEAPF32 = new Float32Array(buf);
Module['HEAPF64'] = HEAPF64 = new Float64Array(buf);
```

## 申请一段WASM内存

由于WASM中运行的代码只能读取WASM申请到的这块内存区域，所以除了`number`类型的数据，其它所有需要处理的数据都需要先放到WASM内存区域中，这就需要依赖WASM的内存管理方法了。

WASM的内存管理完全由WASM代码自己进行，比如，当我们使用C代码来生成WASM文件时，一般就会用到`malloc`和`free`这两个方法来实现内存的申请和释放。

对于申请到的内存，就可以通过上面的`Module.HEAPU8`来访问了。内存用完后，一定要记得释放，否则将会发生肉眼可见的内存泄露。

下面是一个内存使用的例子：

```javascript
// ptr就是个数字，标记出了本次申请到的内存位置，不包括内存大小等信息
let ptr = Module._malloc(1024);
Module.HEAPU8.fill(0x10, ptr, 1024);
Module._free(ptr);
ptr = null;
```

需要注意的是，在JS中要使用的`_malloc`和`_free`方法，也需要在编译过程中手动导出，否则在JS中是看不到这两个方法的。


## 传递Buffer数据

传递Buffer数据，本质上其实就是在传递Buffer的指针地址，其实也是一个`number`。

一般的处理流程：
1. 申请一块WASM内存
2. 将要处理的数据Copy到这块内存区域
3. 将内存地址传递给WASM方法
4. WASM处理完成后，将这块内存中的数据再取出
5. 如果WASM返回了一块新的内存区域，要注意是否需要在JS中手动释放这块内存

可以看出，完整的流程中包含了两次数据拷贝，在数据量较大时是比较耗时的。不过我们可以优化这个流程，由于WASM内存本质上就是JS中的ArrayBuffer，所以，来源数据时可以在一开始就直接写入到WASM内存中，这样就无需在处理时再Copy一次，数据取回也是一样，直接读取WASM内存中的数据即可。


## 传递字符串

虽然字符串本质上也是一段内存，但是由于要考虑字符编码的问题，就导致在WASM和JS之间传递字符串是一件并不轻松的事情，好在一般情况下我们不需要这么做。

字符串的一般处理流程：
1. 申请一块WASM内存
2. 将JS字符串转换为UTF8编码（JS使用的是一种非常奇怪的字符编码，不转换为UTF8的话难以进行处理），并写入到这块内存中
3. 将这块内存传递给WASM
4. WASM对字符串进行处理，并返回处理结果
5. 如果JS需要获取处理后的字符串，则需要再将这个字符串从UTF8转换为JS的字符串
6. 别忘了释放无用的内存


## Code说明

Demo5的C代码实现了几个方法，分别用来处理`nubmer`、图像数据和字符串。

1. 在`wasm`目录中：
  - 参照`env.example`创建`.env`，并设置`EMSDK_HOME`为本地EMSDK的路径
  - 执行`./build.sh`编译并生成`demo5.js`
  - 打开`test.html`，并切换至Console，查看运行结果

Demo5还在WASM和JS中分别实现了同一个卷积函数，用来对比WASM和JS下的性能。

测试发现，在数据规模较小时（比如矩阵256x256，核大小为3），JS的运行速度比WASM慢数倍；但是随着数据规模增大（比如矩阵成长为2048x256），WASM的执行周期几乎是线性增长的，但JS的执行周期并没有按比例增长，而是运行速度越来越快，说明浏览器的JS引擎对于反复执行的JS代码是有优化的。

关注点：
1. Makefile中的导出函数列表中，需要有`_malloc`和`_free`
2. Makefile中导出了一组`EXPORTED_RUNTIME_METHODS`，用来处理上述提到的UTF8和JS字符串之间的转换
  - EXPORT_RUNTIME_FUNCS: https://emscripten.org/docs/tools_reference/settings_reference.html#exported-runtime-methods
