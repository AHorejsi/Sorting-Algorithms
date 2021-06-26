#pragma once

#include <algorithm>
#include <iterator>
#include <memory>

namespace sort {
	template<typename BidirectionalIterator>
	void counting_sort(BidirectionalIterator first, BidirectionalIterator last) {
		std::pair<BidirectionalIterator, BidirectionalIterator> minmax = std::minmax_element(first, last);
		typename std::iterator_traits<BidirectionalIterator>::value_type size = std::distance(first, last);
		typename std::iterator_traits<BidirectionalIterator>::value_type range = *minmax.second - *minmax.first + 1;

		std::vector<typename std::iterator_traits<BidirectionalIterator>::value_type> counts(range);
		std::vector<typename std::iterator_traits<BidirectionalIterator>::value_type> result(size);

		for (BidirectionalIterator i = first; i != last; ++i) {
			++(counts[*i - *minmax.first]);
		}

		for (typename std::iterator_traits<BidirectionalIterator>::value_type i = 1; i < range; ++i) {
			counts[i] += counts[i - 1];
		}

		for (BidirectionalIterator i = std::prev(last); i != first; --i) {
			typename std::iterator_traits<BidirectionalIterator>::value_type indexOfCounts = *i - *minmax.first;

			result[counts[indexOfCounts] - 1] = *i;
			--(counts[indexOfCounts]);
		}

		typename std::iterator_traits<BidirectionalIterator>::value_type indexOfCounts = *first - *minmax.first;

		result[counts[indexOfCounts] - 1] = *first;
		--(counts[indexOfCounts]);

		std::copy(result.cbegin(), result.cend(), first);
	}
}
