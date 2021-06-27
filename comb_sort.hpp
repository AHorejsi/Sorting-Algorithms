#pragma once


#include <iterator>
#include <functional>

namespace sort {
	namespace _utils {
		template<typename RandomAccessIterator>
		typename std::iterator_traits<RandomAccessIterator>::difference_type _next_gap(typename std::iterator_traits<RandomAccessIterator>::difference_type gap) {
			gap = gap * 10 / 13;

			if (gap < 1) {
				gap = 1;
			}

			return gap;
		}
	}

	template<typename RandomAccessIterator, typename Compare>
	void comb_sort(RandomAccessIterator first, RandomAccessIterator last, const Compare comp) {
		using namespace _utils;

		typename std::iterator_traits<RandomAccessIterator>::difference_type gap = last - first;
		bool swapped = true;

		while (gap > 1 || swapped) {
			gap = _next_gap<RandomAccessIterator>(gap);
			swapped = false;

			RandomAccessIterator end = last - gap;

			for (RandomAccessIterator i = first; i != end; ++i) {
				RandomAccessIterator j = i + gap;

				if (comp(*j, *i)) {
					std::iter_swap(i, j);
					swapped = true;
				}
			}
		}
	}

	template<typename RandomAccessIterator>
	void comb_sort(RandomAccessIterator first, RandomAccessIterator last) {
		comb_sort(
			first,
			last,
			std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>()
		);
	}
}
