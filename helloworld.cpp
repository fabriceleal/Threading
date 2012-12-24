#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

void hello()
{
  std::thread::id id = std::this_thread::get_id();
  std::cout << "ID=" << id << " printed from a thread!" << std::endl;
}

class thread_raii
{
  std::thread& t;
public:

  explicit thread_raii(std::thread& t_) : t(t_)
  { }

  ~thread_raii()
  {
    if(t.joinable())
      {
	t.join();
      }
  }

  thread_raii(thread_raii const&)=delete;
  thread_raii& operator=(thread_raii const&)=delete;
};

void f(int aInt, std::string const& aString)
{
  std::thread::id id = std::this_thread::get_id();
  std::cout << "ID=" << id << " a int " << aInt << " and a string "; 
  std::cout << aString << std::endl;
}

void do_stuff(int i)
{
  std::thread::id id = std::this_thread::get_id();
  std::cout << "ID=" << id << " do_stuff(" << i << ")" << std::endl;
}


int main()
{
  // Info
  std::cout << "Hardware threads: " << std::thread::hardware_concurrency();
  std::cout << std::endl;

  // Example 1
  std::thread t(hello);
  t.join();

  // Example 2
  std::thread t2(hello);
  thread_raii t2_raii(t2);
 
  // Example 3
  char buffer[1024];
  sprintf(buffer, "%s %i", "hello world", 123);
  std::thread t3(f, 3, std::string(buffer));
  t3.join();
  
  // Example 4
  std::vector<std::thread> threads;
  for(int i = 0; i<5; ++i)
    threads.push_back(std::thread(do_stuff, i));
  std::for_each(
		threads.begin(), 
		threads.end(), 
		std::mem_fn(&std::thread::join));
  
  // Example 5
  
}
