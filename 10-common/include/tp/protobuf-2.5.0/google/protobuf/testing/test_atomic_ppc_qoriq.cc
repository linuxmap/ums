#include <stdio.h>
#include <unistd.h>
#include "atomicops.h"
#include <pthread.h>

using namespace google::protobuf::internal;

Atomic32 nTest = 1;
Atomic32 nOldValue = 1;
Atomic32 nNewValue = 2;
Atomic32 *ptr = &nTest;
Atomic32 nRet = 0;
static int nCount = 0;

void * thread1(void *)
{
	while(1)
	{
		if(1000 == nRet)
		{
			break;
		}
		printf("This is a thread1!\n");
		printf("The Input is %d, %d, %d, return is %d\n", *ptr, nOldValue, nNewValue, nRet);
		nOldValue++;
		usleep(10000);
	}
	return NULL;
}

void * thread2(void *)
{
	while(1)
	{
		if(50 == nCount)
		{
			break;
		}
		printf("This is a thread2!\n");
		nOldValue = *ptr;
//		nOldValue = NoBarrier_AtomicExchange(ptr, nNewValue);
		printf("NoBarrier_AtomicExchange:ptr is %d, oldvalue is %d, newvalue is %d\n",*ptr, nOldValue, nNewValue);
		nRet = NoBarrier_CompareAndSwap(ptr, nOldValue, nNewValue);

		printf("NoBarrier_CompareAndSwap:The Input is %d, %d, %d, return is %d\n", *ptr, nOldValue, nNewValue, nRet);
		usleep(200000);
		//nNewValue++;
		NoBarrier_AtomicIncrement(&nNewValue, 1);
		printf("NoBarrier_AtomicIncrement, newvalue is %d\n", nNewValue);
//		Acquire_Load(<const_cast>ptr);
//		Release_Load(ptr);
//		Acquire_Store(ptr, 10);
//		Release_Store(ptr, 11);
		nCount++;
	}
	return NULL;
}

int main()
{
	int i = 0, nThreadRet = 0;
	pthread_t pThreadID1, pThreadID2;
	nThreadRet = pthread_create(&pThreadID1, NULL, &thread1, NULL);
	if(0 != nThreadRet)
	{
		printf("Create thread error!\n");
		exit(1);
	}
	nThreadRet = pthread_create(&pThreadID2, NULL, &thread2, NULL);
	if(0 != nThreadRet)
	{
		printf("Create thread error!\n");
		exit(1);
	}

	pthread_join(pThreadID1, NULL);
	pthread_join(pThreadID2, NULL);
	return 0;
}
