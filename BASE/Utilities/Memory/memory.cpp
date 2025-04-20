#include "pch.h"
#include "memory.h"

memory::allocator memory::mem_allocator_;

memory::allocator::~allocator()
{
	this->clear();
}

void memory::allocator::clear()
{
	std::lock_guard _(this->mutex_);

	for (auto& data : this->pool_)
	{
		memory::free(data);
	}

	this->pool_.clear();
}

void memory::allocator::free(void* data)
{
	std::lock_guard _(this->mutex_);

	const auto j = std::find(this->pool_.begin(), this->pool_.end(), data);
	if (j != this->pool_.end())
	{
		memory::free(data);
		this->pool_.erase(j);
	}
}

void memory::allocator::free(const void* data)
{
	this->free(const_cast<void*>(data));
}

void* memory::allocator::allocate(const size_t length)
{
	std::lock_guard _(this->mutex_);

	const auto data = memory::allocate(length);
	this->pool_.push_back(data);
	return data;
}

bool memory::allocator::empty() const
{
	return this->pool_.empty();
}

void* memory::allocate(const size_t length)
{
	return calloc(length, 1);
}

void memory::free(void* data)
{
	if (data)
	{
		::FMemory::Free(data);
	}
}

void memory::free(const void* data)
{
	free(const_cast<void*>(data));
}

bool memory::is_set(const void* mem, const char chr, const size_t length)
{
	const auto mem_arr = static_cast<const char*>(mem);

	for (size_t i = 0; i < length; ++i)
	{
		if (mem_arr[i] != chr)
		{
			return false;
		}
	}

	return true;
}

memory::allocator* memory::get_allocator()
{
	return &memory::mem_allocator_;
}

void memcpy_(void* _Dst, void const* _Src, size_t _Size)
{
	auto csrc = (char*)_Src;
	auto cdest = (char*)_Dst;

	for (int i = 0; i < _Size; i++)
	{
		cdest[i] = csrc[i];
	}
}

void SwapVtable(void* obj, uint32_t index, void* hook)
{
	auto table_ptr = *reinterpret_cast<void**>(obj);
	auto original_table = *reinterpret_cast<void***>(obj);
	int i = 0;

	for (; original_table[i]; i++)
		__noop();

	auto stored_table = new uintptr_t[i];
	memcpy_(stored_table, table_ptr, i * sizeof(uintptr_t));

	stored_table[index] = (uintptr_t)hook;
	*(uintptr_t**)(obj) = stored_table;
}