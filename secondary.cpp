#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h> //SEMAFORY

using namespace std;

double expectation(double* var, size_t size)
{
    double sum = 0;
    size_t i;
 
    for(i = 0; i < size; ++i)
    sum += var[i];
 
    return sum / size;
}
 
double variance(double* var, size_t size)
{
    double sum = 0;
    double mean = expectation(var, size);
    
    size_t i;
 
    for(i = 0; i < size; ++i)
    sum += (var[i] - mean) * (var[i] - mean);
 
    return sum / size;
}
 
void show(double* var, size_t size)
{
    size_t i;
    
    printf("Given array:\n");
    for(i = 0; i < size; ++i)
    	printf("%.5f ", var[i]);
 	
    printf("\nExpectation: %.5f\n", expectation(var, size));
    printf("Variance: %.5f\n", variance(var, size));
}

int main(int argc, char *argv[])
{	
	double X[] = {1.2, 1.21, 1.19, 1.22, 1.24, 1.18, 1.16, 1.2, 0.17, 0.29};
    double Y[] = {0.15, 0.18, 0.2, 0.16, 0.14, 0.08, 0.15, 0.17, 0.29, 1.2};
    double Z[] = {1.3, 1.31, 1.29, 1.32, 1.34, 1.28, 1.26, 1.1, 0.33, 1.3};
	int size = 10;

	double *array = new double[size];
	int decide = stoi(argv[1]);

	switch(decide)
	{
		case 1:
			array = X;
			break;
		case 2:
			array = Y;
			break;
		case 3:
			array = Z;
			break;
		default:
			array = X;
			break;
	}

	cout << "Pid ID "<< getpid() << endl;

	show(array, size);
	
	//delete [] array;
	return 0;
}