#include <iostream>
#include <thread>

void hello()
{
  std::cout << "printed from a thread!\n";
}

int main()
{
  std::thread t(hello);
  //std::thread t([]{
  //    hello();
  //  });

  //t.detach();
  t.join();
}
