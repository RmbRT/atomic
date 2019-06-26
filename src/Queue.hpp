#ifndef __atomic_queue_hpp_defined
#define __atomic_queue_hpp_defined

#include "detail/Queue.hpp"

namespace atomic
{
	template<class T>
	/** Lock-free queue.
		Items inside the queue are not automatically deleted.
	@tparam T:
		The queued item type. */
	class Queue : detail::Queue
	{
	public:
		/** Queue item wrapper type. */
		class Item : detail::Queue::Item
		{
			friend class Queue<T>;
			/** The queued item's stored value. */
			T m_value;
		public:
			template<class ...Args>
			/** Creates an item and its held value using the passed arguments.
			@param[in] args:
				The arguments to construct the held value with. */
			Item(
				Args &&... args);

			/** Accesses the item's value. */
			inline T * get();
			/** Accesses the item's value. */
			inline T const * get() const;

			/** Accesses the item's value. */
			inline T * operator->();
			/** Accesses the item's value. */
			inline T const * operator->() const;

			/** Accesses the item's value. */
			inline T &operator*();
			/** Accesses the item's value. */
			inline T const& operator*() const;

			/** Acquires the item's value.
				When removing multiple items at once, accessing an item's value before acquiring it is unsafe.
			@return
				The next queued item, if it is already set, or null. */
			inline Item * acquire();

			/** Waits until the item's successor is linked to it.
				If `next` is null, waits until a successor is set. This is only needed when iterating through a list of items (removed using `pop_all()`).
			@param[in] next:
				The next item (or null), as returned by `acquire()`.
			@return
				The item's successor, if any. */
			inline Item * wait(
				Item * next);

			/** Waits until the item's successor is linked to it.
				This version is to be used when removing multiple items at once. If `next` is null, waits until a successor is set, except if this item is the last item, as there cannot be a next item.
			@param[in] next:
				The next item (or null), as returned by `acquire()`.
			@param[in] last:
				The last removed item (if multiple items have been removed at once).
			@return
				The item's successor, if any. */
			inline Item * wait(
				Item * next,
				Item * last);

			/** Sets the item's successor.
				The item must not yet have a successor.
			@param[in] next:
				The next item. */
			inline void link(
				Item * next);
		};

		/** Pushes an item to the end of the queue.
		@param[in] item:
			The item to push to the end of the queue. */
		void push(
			Item * item);

		/** Pushes a list of linked items to the end of the queue.
		@param[in] first:
			The first item to push.
		@param[in] last:
			The last item to push. */
		void push_all(
			Item * first,
			Item * last);

		/** Pops an item from the beginning of the queue.
			May fail to pop an item during concurrency.
		@return
			The popped item, or null. */
		Item * pop();

		/** Pops all items from the queue.
		@param[out] first:
			The first removed item, or null.
		@param[out] last:
			The last removed item, or null.
		@return
			Whether any item has been removed. */
		bool pop_all(
			Item * &first,
			Item * &last);
	};
}

#include "Queue.inl"

#endif