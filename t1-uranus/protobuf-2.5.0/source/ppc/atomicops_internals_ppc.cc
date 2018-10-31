/*****************************************************************************
模块名      : protobuf
文件名      : atomicops_internals_ppc.cc
相关文件    : 无
文件实现功能: ppc平台原子操作实现
作者        : 
版本        : V1.0  Copyright(C) 2015 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2015/3/11  1.0         田丽平      Create
******************************************************************************/

#include <google/protobuf/stubs/atomicops.h>
#include <pthread.h>

#ifdef GOOGLE_PROTOBUF_ATOMICOPS_INTERNALS_PPC_H_

namespace google {
namespace protobuf {
namespace internal {

static pthread_mutex_t g_plock = PTHREAD_MUTEX_INITIALIZER;

Atomic32 NoBarrier_CompareAndSwap(volatile Atomic32* ptr,
	Atomic32 old_value,
	Atomic32 new_value)
{
	pthread_mutex_lock(&g_plock);
	Atomic32 nRet = *ptr;
	if (*ptr == old_value)
	{
		*ptr = new_value;
	}
	pthread_mutex_unlock(&g_plock);
	return nRet;
}

Atomic32 NoBarrier_AtomicExchange(volatile Atomic32* ptr,
	Atomic32 new_value)
{
	pthread_mutex_lock(&g_plock);
	Atomic32 old_value;
	old_value = *ptr;
	*ptr = new_value;
	pthread_mutex_unlock(&g_plock);

	return old_value;
}

Atomic32 NoBarrier_AtomicIncrement(volatile Atomic32* ptr,
	Atomic32 increment)
{
		return Barrier_AtomicIncrement(ptr, increment);
}

Atomic32 Barrier_AtomicIncrement(volatile Atomic32* ptr, Atomic32 increment)
{
	pthread_mutex_lock(&g_plock);
	Atomic32 old_value = *ptr;
	Atomic32 new_value = old_value + increment;
	*ptr = new_value;
	pthread_mutex_unlock(&g_plock);

	return old_value;
}

Atomic32 Acquire_CompareAndSwap(volatile Atomic32* ptr, Atomic32 old_value, Atomic32 new_value)
{
	return NoBarrier_CompareAndSwap(ptr, old_value, new_value);
}

Atomic32 Release_CompareAndSwap(volatile Atomic32* ptr, Atomic32 old_value, Atomic32 new_value)
{
	return NoBarrier_CompareAndSwap(ptr, old_value, new_value);
}

void NoBarrier_Store(volatile Atomic32* ptr, Atomic32 value)
{
	*ptr = value;
}

void MemoryBarrier()
{
}

void Acquire_Store(volatile Atomic32* ptr, Atomic32 value)
{
	*ptr = value;
	MemoryBarrier();
}

void Release_Store(volatile Atomic32* ptr, Atomic32 value)
{
	MemoryBarrier();
	*ptr = value;
}

Atomic32 NoBarrier_Load(volatile const Atomic32* ptr)
{
	return *ptr;
}

Atomic32 Acquire_Load(volatile const Atomic32* ptr)
{
	Atomic32 value = *ptr;
	MemoryBarrier();
	return value;
}

Atomic32 Release_Load(volatile const Atomic32* ptr)
{
	MemoryBarrier();
	return *ptr;
}

}  // namespace internal
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_ATOMICOPS_INTERNALS_PPC_H_
