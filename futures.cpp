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

int calc_meaning_of_life_async()
{
  cout << "* Starting async calculation ..." << endl;
  this_thread::sleep_for(chrono::milliseconds(1000));
  cout << "* Calculation async ended ..." << endl;
  return 12345;
}

int calc_meaning_of_life_deferred()
{
  cout << "* Starting deferred calculation ..." << endl;
  this_thread::sleep_for(chrono::milliseconds(1000));
  cout << "* Calculation deferred ended ..." << endl;
  return 12345;
}

int calc_meaning_of_life_dont_care()
{
  cout << "* Starting calculation dont care ..." << endl;
  this_thread::sleep_for(chrono::milliseconds(1000));
  cout << "* Calculation dont care ended ..." << endl;
  return 12345;
}


int main(int argc, char** argv)
{
  future<int> the_answer = async(calc_meaning_of_life);
  future<int> the_answer_async = async(std::launch::async, calc_meaning_of_life_async);

  // My compiler doesnt support std::launch::deferred. Cant test

  // async - run on own thread
  // deferred - wait until get is called
  // async | deferred - chosen by implementation

  //future<int> the_answer_deferred = async(std::launch::deferred, calc_meaning_of_life_deferred);
  //future<int> the_answer_dont_care = async(std::launch::async | std::launch::deferred, calc_meaning_of_life_dont_care);

  cout << "Asyncs were launched..." << endl;
  cout << "The meaning of life is " << the_answer.get() << endl; 
  cout << "I want an async answer: " << the_answer_async.get() << endl;
  //cout << "I want a deferred answer: " << the_answer_deferred.get() << endl;
  //cout << "I want a dont care answer: " << the_answer_dont_care.get() << endl;

  return 0;
}
