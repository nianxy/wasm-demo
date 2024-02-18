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
    .class_function("getValueFromCounter", &Counter::getValueFromCounter)
    .class_property("version", &Counter::version);
}
