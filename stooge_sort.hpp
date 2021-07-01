#pragma once


#include <iterator>
#include <functional>

namespace sort {
	namespace _utils {
		template<typename RandomAccessIterator, typename Compare>
		void _stooge_sort_helper(RandomAccessIterator first, RandomAccessIterator last, const Compare comp) {
			if (comp(*last, *first)) {
				std::iter_swap(first, last);
			}

			typename std::iterator_traits<RandomAccessIterator>::difference_type size = last - first + 1;

			if (size > 2) {
				typename std::iterator_traits<RandomAccessIterator>::difference_type third = size / 3;

				_stooge_sort_helper(first, last - third, comp);
				_stooge_sort_helper(first + third, last, comp);
				_stooge_sort_helper(first, last - third, comp);
			}
		}
	}

	template<typename RandomAccessIterator, typename Compare>
	void stooge_sort(RandomAccessIterator first, RandomAccessIterator last, const Compare comp) {
		using namespace _utils;

		_stooge_sort_helper(first, last - 1, comp);
	}

	template<typename RandomAccessIterator>
	void stooge_sort(RandomAccessIterator first, RandomAccessIterator last) {
		stooge_sort(
			first,
			last,
			std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>()
		);
	}
}
