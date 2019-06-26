#ifndef __cr_util_atomic_hpp_defined
#define __cr_util_atomic_hpp_defined

#include <atomic>

namespace atomic
{
	template<class T>
	/** An extension for std::atomic that also includes the `load_strong()` operation.
		`load()` has been renamed `load_weak()` to make a more obvious distinction between the two supported types of load operation. Also contains some shorthand notations that omit the memory order parameter. */
	class Atomic: public std::atomic<T>
	{
		using std::atomic<T>::load;
		using std::atomic<T>::operator T;
	public:
		using std::atomic<T>::atomic;

		/** Reads the globally latest value.
		@param[in] order:
			The memory order to use.
		@return
			The globally latest value. It is guaranteed that at the time of reading, there exists no later value than the one obtained. */
		inline T load_strong(
			std::memory_order order) const noexcept;
		/** Reads the locally latest seen value.
		@param[in] order:
			The memory order to use.
		@return
			The latest value the current thread has seen. This value is not guaranteed to be the globally latest value. */
		inline T load_weak(
			std::memory_order order) const noexcept;

		/** Strong load with acquire semantics. */
		inline T acquire_strong() const noexcept;
		/** Weak load with acquire semantics. */
		inline T acquire_weak() const noexcept;
		/** Strong load with consume semantics. */
		inline T consume_strong() const noexcept;
		/** Weak load with consume semantics. */
		inline T consume_weak() const noexcept;
		/** Strong load with relaxed semantics. */
		inline T relaxed_strong() const noexcept;
		/** Weak load with relaxed semantics. */
		inline T relaxed_weak() const noexcept;
		/** Strong load with sequentially consistent semantics. */
		inline T seq_cst_strong() const noexcept;
		/** Weak load with sequentially consistent semantics. */
		inline T seq_cst_weak() const noexcept;

		/** Store with relaxed semantics. */
		inline void relaxed(
			T const& value);
		/** Store with release semantics. */
		inline void release(
			T const& value);
		/** Store with sequentially consistent semantics. */
		inline void seq_cst(
			T const& value);

		/** Exchange with relaxed semantics. */
		inline T exchange_relaxed(
			T const& value);
		/** Exchange with release semantics. */
		inline T exchange_release(
			T const& value);
		/** Exchange with acquire semantics. */
		inline T exchange_acquire(
			T const& value);
		/** Exchange with sequentially consistent semantics. */
		inline T exchange_seq_cst(
			T const& value);
		/** Exchange with consume semantics. */
		inline T exchange_consume(
			T const& value);
		/** Exchange with acquire-release semantics. */
		inline T exchange_acq_rel(
			T const& value);
	};
}

#include "Atomic.inl"

#endif