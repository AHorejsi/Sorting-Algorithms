#pragma once


#include <iterator>
#include <functional>

namespace sort {
	template<typename BidirectionalIterator, typename Compare>
	void gnome_sort(BidirectionalIterator first, BidirectionalIterator last, const Compare comp) {
		BidirectionalIterator i = first;

		while (i != last) {
			if (first == i) {
				++i;
			}

			BidirectionalIterator j = std::prev(i);

			if (!comp(*i, *j)) {
				++i;
			}
			else {
				std::iter_swap(i, j);
				--i;
			}
		}
	}

	template<typename BidirectionalIterator>
	void gnome_sort(BidirectionalIterator first, BidirectionalIterator last) {
		gnome_sort(
			first,
			last,
			std::less<typename std::iterator_traits<BidirectionalIterator>::value_type>()
		);
	}
}
