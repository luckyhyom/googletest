#include <iostream>

class Adder {
  public:
    virtual ~Adder() = default;
    virtual int add(int x, int y) = 0;
};

class LocalAdder : public Adder {
  public:
    int add(int x, int y) override {
      return x + y;
    };
};

class OnlineAdder : public Adder {
  public:
    int add(int x, int y) override {
      std::cout << "Connecting Adder Server.." << std::endl;
      std::cout << "Calculating.." << std::endl;
      std::cout << "Completed." << std::endl;
      return x + y;
    };
};