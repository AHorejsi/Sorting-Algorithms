#pragma once


#include <iterator>
#include <functional>

namespace sort {
	template<typename ForwardIterator, typename Compare>
	void bubble_sort(ForwardIterator first, ForwardIterator last, const Compare comp) {
		for (ForwardIterator i = first; i != last; ++i) {
			bool swapped = false;
			
			ForwardIterator j = first;
			ForwardIterator k = std::next(j);

			while (k != last) {
				if (comp(*k, *j)) {
					std::iter_swap(j, k);
					swapped = true;
				}

				++j;
				++k;
			}

			if (!swapped) {
				return;
			}
		}
	}

	template<typename ForwardIterator>
	void bubble_sort(ForwardIterator first, ForwardIterator last) {
		bubble_sort(
			first,
			last,
			std::less<typename std::iterator_traits<ForwardIterator>::value_type>()
		);
	}
}
