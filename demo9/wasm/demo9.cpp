#include <string>
#include <emscripten/bind.h>

class Counter {
public:
  const static std::string version;

  static int getValueFromCounter(const Counter& counter) {
    return counter.getValue();
  }

  Counter(int max) : max(max), value(0) {}
  
  int increase() {
    value = (value+1)%max;
    return value;
  }
  
  int getValue() const {
    return value;
  }

  int sum(int* numbers, int length) {
    int v = 0;
    for (int i=0; i<length; i++) {
      v += numbers[i];
    }
    return v;
  }

private:
  int max;
  int value;
};

const std::string Counter::version = "1.0.0";

using namespace emscripten;

EMSCRIPTEN_BINDINGS(my_module) {
  class_<Counter>("Counter")
    .constructor<int>()
    .function("increase", &Counter::increase)
    .function("getValue", &Counter::getValue)
    .function("sum", optional_override(
      [](Counter& self, int ptr, int size) {
        return self.sum((int*)ptr, size);
      }
    ))
    .class_function("getValueFromCounter", &Counter::getValueFromCounter)
    .class_property("version", &Counter::version);
}
