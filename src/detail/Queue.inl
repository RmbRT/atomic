#include <cassert>

namespace atomic::detail
{
	Queue::Item * Queue::Item::acquire()
	{
		return m_next.acquire_strong();
	}

	Queue::Item * Queue::Item::wait(
		Queue::Item * next)
	{
		while(!next)
			next = m_next.relaxed_weak();
		return next;
	}

	Queue::Item * Queue::Item::wait(
		Queue::Item * next,
		Queue::Item * last)
	{
		if(this != last)
			return wait(next);
		else
			return nullptr;
	}

	void Queue::Item::link(
		Item * next)
	{
		assert(next != nullptr);
		assert(next != this);
		assert(m_next.relaxed_weak() == nullptr);

		m_next.release(next);
	}

	void Queue::Item::release()
	{
		m_next.release(nullptr);
	}
}