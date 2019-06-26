namespace atomic
{
	template<class T>
	template<class ...Args>
	Queue<T>::Item::Item(
		Args &&... args):
		m_value(std::forward<Args>(args)...)
	{
	}

	template<class T>
	T * Queue<T>::Item::get()
	{
		return &m_value;
	}

	template<class T>
	T const * Queue<T>::Item::get() const
	{
		return &m_value;
	}

	template<class T>
	T * Queue<T>::Item::operator->()
	{
		return &m_value;
	}

	template<class T>
	T const * Queue<T>::Item::operator->() const
	{
		return &m_value;
	}

	template<class T>
	T &Queue<T>::Item::operator*()
	{
		return m_value;
	}

	template<class T>
	T const& Queue<T>::Item::operator*() const
	{
		return m_value;
	}

	template<class T>
	typename Queue<T>::Item * Queue<T>::Item::acquire()
	{
		return detail::Queue::Item::acquire();
	}

	template<class T>
	typename Queue<T>::Item * Queue<T>::Item::wait(
		typename Queue<T>::Item * next)
	{
		return detail::Queue::Item::wait(next);
	}

	template<class T>
	typename Queue<T>::Item * Queue<T>::Item::wait(
		typename Queue<T>::Item * next,
		typename Queue<T>::Item * last)
	{
		return detail::Queue::Item::wait(next, last);
	}

	template<class T>
	void Queue<T>::Item::link(
		Item * next)
	{
		detail::Queue::Item::link(next);
	}

	template<class T>
	void Queue<T>::push(
		Item * item)
	{
		detail::Queue::push(item);
	}

	template<class T>
	void Queue<T>::push_all(
		Item * first,
		Item * last)
	{
		detail::Queue::push_all(first, last);
	}

	template<class T>
	typename Queue<T>::Item * Queue<T>::pop()
	{
		return static_cast<Item *>(detail::Queue::pop());
	}

	template<class T>
	bool Queue<T>::pop_all(
		typename Queue<T>::Item * &first,
		typename Queue<T>::Item * &last)
	{
		detail::Queue::Item * _first, * _last;
		bool result = detail::Queue::pop_all(_first, _last);
		first = static_cast<Item *>(_first);
		last = static_cast<Item *>(_last);
		return result;
	}
}