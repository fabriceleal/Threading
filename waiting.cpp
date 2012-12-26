#include <iostream>
#include <thread>

using namespace std;

class data_chunk {
public:
  bool isLast;
  long id;
};
 
std::mutex mutex1;

// Used to send data between threads
std::queue<data_chunk> data_queue;

std::condition_variable data_cond;

data_chunk prepare_data()
{  
  static int chunks = 1300;

  data_chunk* e = new data_chunk();
  e->isLast = (0 == chunks);
  e->id = chunks--;
  return *e;
}

bool has_data()
{
  return false;
}

void process(data_chunk data)
{
  cout << "Processing chunk " << data.id << endl;
}

bool is_last_chunk(data_chunk data)
{
  return data.isLast;
}

void prepare_data_thread()
{
  while(has_data())
    {
      data_chunk const data = prepare_data();
      std::lock_guard<std::mutex> lk(mutex1);
      data_queue.push(data);
      // Notify waiting thread
      data_cond.notify_one();
    }
}

void process_data_thread()
{
  while(true)
    {
      std::unique_lock<std::mutex> lk(mutex1);
      // Wait, pass lock and waiting condition
      data_cond.wait(lk, []{ return !data_queue.empty(); });
      data_chunk data = data_queue.front();
      data_queue.pop();
      lk.unlock();
      process(data);
      if(is_last_chunk(data))
	break;
    }
}

int main(int argc, char** argv)
{
  thread process(process_data_thread);
  thread prepare(prepare_data_thread);
  prepare.join();
  process.join();
  return 0;
}
