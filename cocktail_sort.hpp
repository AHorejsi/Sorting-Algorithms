#pragma once


#include <iterator>
#include <functional>

namespace sort {
	template<typename BidirectionalIterator, typename Compare>
	bool _bubble_up(BidirectionalIterator first, BidirectionalIterator last, const Compare comp) {
		bool swapped = false;

		for (BidirectionalIterator i = first; i != last; ++i) {
			BidirectionalIterator j = std::next(i);

			if (comp(*j, *i)) {
				std::iter_swap(i, j);
				swapped = true;
			}
		}

		return swapped;
	}

	template<typename BidirectionalIterator, typename Compare>
	bool _bubble_down(BidirectionalIterator first, BidirectionalIterator last, const Compare comp) {
		bool swapped = false;

		for (BidirectionalIterator i = std::prev(last); i != first; --i) {
			BidirectionalIterator j = std::next(i);

			if (comp(*j, *i)) {
				std::iter_swap(i, j);
				swapped = true;
			}
		}

		BidirectionalIterator nextFirst = std::next(first);
		if (comp(*nextFirst, *first)) {
			std::iter_swap(first, nextFirst);
		}

		return swapped;
	}

	template<typename BidirectionalIterator, typename Compare>
	void cocktail_sort(BidirectionalIterator first, BidirectionalIterator last, const Compare comp) {
		bool swapped;
		--last;

		do {
			swapped = _bubble_up(first, last, comp);

			if (!swapped) {
				return;
			}

			--last;

			swapped = _bubble_down(first, last, comp);

			++first;
		} while (swapped);
	}

	template<typename BidirectionalIterator>
	void cocktail_sort(BidirectionalIterator first, BidirectionalIterator last) {
		cocktail_sort(
			first,
			last,
			std::less<typename std::iterator_traits<BidirectionalIterator>::value_type>()
		);
	}
}
