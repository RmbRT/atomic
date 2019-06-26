namespace atomic
{
	template<class T>
	T Atomic<T>::load_strong(
		std::memory_order order) const noexcept
	{
		T expected = T();
		static_cast<std::atomic<T> *>(
			const_cast<Atomic<T> *>(
				this))->compare_exchange_strong(
					expected,
					expected,
					order,
					order);
		return expected;
	}

	template<class T>
	T Atomic<T>::load_weak(
		std::memory_order order) const noexcept
	{
		return std::atomic<T>::load(order);
	}

	template<class T>
	T Atomic<T>::acquire_strong() const noexcept
	{
		return load_strong(std::memory_order_acquire);
	}

	template<class T>
	T Atomic<T>::acquire_weak() const noexcept
	{
		return load_weak(std::memory_order_acquire);
	}

	template<class T>
	T Atomic<T>::consume_strong() const noexcept
	{
		return load_strong(std::memory_order_consume);
	}

	template<class T>
	T Atomic<T>::consume_weak() const noexcept
	{
		return load_weak(std::memory_order_consume);
	}

	template<class T>
	T Atomic<T>::relaxed_strong() const noexcept
	{
		return load_strong(std::memory_order_relaxed);
	}

	template<class T>
	T Atomic<T>::relaxed_weak() const noexcept
	{
		return load_weak(std::memory_order_relaxed);
	}

	template<class T>
	T Atomic<T>::seq_cst_strong() const noexcept
	{
		return load_strong(std::memory_order_seq_cst);
	}

	template<class T>
	T Atomic<T>::seq_cst_weak() const noexcept
	{
		return load_weak(std::memory_order_seq_cst);
	}

	template<class T>
	void Atomic<T>::relaxed(
		T const& value)
	{
		std::atomic<T>::store(value, std::memory_order_relaxed);
	}

	template<class T>
	void Atomic<T>::release(
		T const& value)
	{
		std::atomic<T>::store(value, std::memory_order_release);
	}

	template<class T>
	void Atomic<T>::seq_cst(
		T const& value)
	{
		std::atomic<T>::store(value, std::memory_order_seq_cst);
	}

	template<class T>
	T Atomic<T>::exchange_relaxed(
		T const& value)
	{
		return std::atomic<T>::exchange(
			value,
			std::memory_order_relaxed);
	}

	template<class T>
	T Atomic<T>::exchange_release(
		T const& value)
	{
		return std::atomic<T>::exchange(
			value,
			std::memory_order_release);
	}

	template<class T>
	T Atomic<T>::exchange_acquire(
		T const& value)
	{
		return std::atomic<T>::exchange(
			value,
			std::memory_order_acquire);
	}

	template<class T>
	T Atomic<T>::exchange_seq_cst(
		T const& value)
	{
		return std::atomic<T>::exchange(
			value,
			std::memory_order_seq_cst);
	}

	template<class T>
	T Atomic<T>::exchange_consume(
		T const& value)
	{
		return std::atomic<T>::exchange(
			value,
			std::memory_order_consume);
	}

	template<class T>
	T Atomic<T>::exchange_acq_rel(
		T const& value)
	{
		return std::atomic<T>::exchange(
			value,
			std::memory_order_acq_rel);
	}
}