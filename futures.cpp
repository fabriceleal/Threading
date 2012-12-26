#include <future>
#include <iostream>
#include <thread>

using namespace std;

int calc_meaning_of_life()
{
  cout << "* Starting calculation ..." << endl;
  this_thread::sleep_for(chrono::milliseconds(1000));
  cout << "* Calculation ended ..." << endl;
  return 12345;
}

int main(int argc, char** argv)
{
  future<int> the_answer = async(calc_meaning_of_life);
  cout << "Async was launched..." << endl;
  cout << "The meaning of life is " << the_answer.get() << endl;
  return 0;
}
