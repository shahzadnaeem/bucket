#include <stdlib.h>
#include <thread>

#define NUM_ITERS 10000
#define NUM_THREADS 2

int counter = 0;
int *p_counter = &counter;

void asm_inc() {
  int *p_counter = &counter;
  for (int i = 0; i < NUM_ITERS; ++i) {
    __asm__("incl (%0) \n\t" : : "r" (p_counter));
  }
}

int main () {
  std::thread t[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; ++i) {
    t[i] = std::thread(asm_inc);
  }
  for (int i = 0; i < NUM_THREADS; ++i) {
    t[i].join();
  }
  printf("Counter value: %i - %s\n",
         counter,
         ( counter == ( NUM_THREADS * NUM_ITERS ) ) ? "LUCKY?" : "TOO SMALL!" );

  return 0;
}
