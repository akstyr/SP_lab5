#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <pthread.h> //потоки
#include <unistd.h>
#include <sys/wait.h>
#include <mutex>

using namespace std;

mutex g_lock;

struct count
{
    string num;
};

void *subprogramm_starter(void *s)
{
    int local = 0, status;
    count *arr = (count*) s;
    string str = arr->num;

    g_lock.lock();

    pid_t pr; /*идентификатор процесса*/
    pr = fork(); /*создание нового процесса*/
    if(pr == 0) /*успешное создание?*/
    {
		/*путь, указатели на аргументы, 0*/
        execl("secondary", " ", str.c_str(), NULL);
    }
    g_lock.unlock();
	/*приостанавливаем работу до завершения процесса*/
    wait(&status);
}
 
int main(void)
{ 
    int rc;
    void* status;
    int num_threads = 3; /*кол-во потов (массивов из 2ой проги)*/

    pthread_t thread[num_threads]; /*идентификатор потока*/
    pthread_attr_t attr; /*отрибуты потока*/

    pthread_attr_init(&attr); /*получаем дефолтные значения атрибутов*/
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); /*задаем статус отсоединения потока*/


    for(int i = 1; i <= num_threads; ++i)
    {
        count arg;
        arg.num = to_string(i);

        std::cout << "\nThread " << i << " created" << std::endl;
		/*создаем новый поток*/
        rc = pthread_create(&thread[i-1], &attr, subprogramm_starter, (void*) &arg);    
        if (rc) 
        {
         std::cout << "Error:unable to create thread, " << rc << std::endl;
         exit(-1);
        }
		pthread_join(thread[i-1], &status); /*ожидает завершения потока*/
    }

    pthread_attr_destroy(&attr); /*удаляем объект из памяти*/

    exit(0);
}