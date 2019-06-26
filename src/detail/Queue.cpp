#include "Queue.hpp"
#include "../Queue.hpp"

namespace atomic::detail
{
	Queue::Queue():
		m_first(nullptr),
		m_last(nullptr)
	{
	}

	void Queue::push(
		Item * item)
	{
		assert(item != nullptr);

		item->release();

		Item * last = m_last.exchange_relaxed(item);

		if(last)
		{
			last->m_next.exchange_relaxed(item);
		} else
		{
			m_first.relaxed(item);
		}
	}

	void Queue::push_all(
		Item * first,
		Item * last)
	{
		assert(first != nullptr);
		assert(last != nullptr);

		last->release();

		Item * old_last = m_last.exchange_relaxed(last);

		if(old_last)
			old_last->m_next.exchange_relaxed(first);
		else
			m_first.relaxed(first);
	}

	Queue::Item * Queue::pop()
	{
		Item * first = m_first.exchange_relaxed(nullptr);

		if(!first)
			return nullptr;

		if(Item * second = first->acquire())
			m_first.relaxed(second);
		else
		{
			Item * expected = first;
			if(!m_last.compare_exchange_strong(
				expected,
				nullptr,
				std::memory_order_relaxed))
			{
				m_first.relaxed(first->wait(nullptr));
			}
		}

		return first;
	}

	bool Queue::pop_all(
		Queue::Item * &first,
		Queue::Item * &last)
	{
		if((first = m_first.exchange_relaxed(nullptr)))
			last = m_last.exchange_relaxed(nullptr);
		else
			last = nullptr;

		return first;
	}
}