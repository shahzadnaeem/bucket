#include <stdlib.h>
#include <thread>
#include <cstdio>

#define NUM_ITERS 100000000
#define NUM_THREADS 12

int counter = 0;
int *p_counter = &counter;

void asm_inc()
{
  int *p_counter = &counter;
  for (int i = 0; i < NUM_ITERS; ++i)
  {
    // Without lock prefix below, incl is NOT atomic
    __asm__("lock incl (%0) \n\t"
            :
            : "r"(p_counter));
  }
}

int main()
{
  std::thread t[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; ++i)
  {
    t[i] = std::thread(asm_inc);
  }
  for (int i = 0; i < NUM_THREADS; ++i)
  {
    t[i].join();
  }
  printf("Counter value: %i, threads: %i - %s\n",
         counter,
         NUM_THREADS,
         (counter == (NUM_THREADS * NUM_ITERS)) ? "LUCKY?" : "TOO SMALL!");

  return 0;
}
