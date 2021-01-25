#include <Ticker.h>

void func() {
  Serial.println("func.");
  }

Ticker ticker1(func, 1000, 0, MILLIS);

// Simple class with (non static) method
class A {
  public:
  A(bool flag) : flag(flag) {}
  
  void func() {
    Serial.printf("A::func: %s.\n", flag ? "true" : "false");
    }
  bool flag;
  };

A a1(true);

// use lambda to capture a1 and execute a1.func()

Ticker ticker2([](){a1.func();}, 1000, 0, MILLIS);

A a2(false);

Ticker ticker3([](){a2.func();}, 1000, 0, MILLIS);

// Class that registers its own method as a callback when it's instantiated.
class B {
  public:
  B(bool flag) : flag(flag), ticker{[this](){this->func();}, 1000, 0, MILLIS} {
    ticker.start();
    }
  
  void func() {
    Serial.printf("B::func: %s.\n", flag ? "true" : "false");
    }
  bool flag;
  Ticker ticker;
  };

B b(true);

// Class that acts like a function (functor)
class C {
  public:
  C(int num) : num(num){}

  // you can call an instance directly with parenthesis and this is executed
  void operator()() const {
    Serial.printf("C(): %d.\n", num);
    }
  int num;
  };

C c(4);

Ticker ticker4(c, 1000, 0, MILLIS);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  
  ticker1.start();
  ticker2.start();
  ticker3.start();
  ticker4.start();
  }

void loop() {
  ticker1.update();
  ticker2.update();
  ticker3.update();
  b.ticker.update();
  ticker4.update();
  }
