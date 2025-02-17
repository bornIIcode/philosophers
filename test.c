#include <pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>



// starting a thread
void *thread_function(void *args)
{
  printf("hello form thread\n");
  return(NULL);
}

int main()
{
  pthread_t thread_id;

  pthread_create(&thread_id, NULL, thread_function, NULL);

  sleep(2);
  // pthread_detach(thread_id);
  pthread_join(thread_id, NULL);
  printf("exiting main function\n");
  return(0);
}

int main()
{

  struct timeval current_time;
  gettimeofday(&current_time, NULL);
  printf("second %ld microsecond %ld", current_time.tv_sec, current_time.tv_usec);
  return(0);


}

// size_t get_time(void)
// {
//   struct  timeval time;

//   if(gettimeofday(&time, NULL) == -1)
//     print_error(2, "Error : gettimeofday/n");
//   return((time.tv_sec * 1000) + (time.tv_usec / 1000));

// }

