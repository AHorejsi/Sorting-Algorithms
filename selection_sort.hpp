#pragma once


#include <iterator>
#include <functional>
#include <stdexcept>
#include <algorithm>

namespace sort {
	enum class selection_sort_type { NORMAL, STABLE, DOUBLE };

	template<typename Iterator, typename Compare>
	void _normal_selection_sort(Iterator first, Iterator last, const Compare comp) {
		for (Iterator i = first; i != last; ++i) {
			Iterator min = std::min_element(i, last, comp);

			if (min != i) {
				std::iter_swap(min, i);
			}
		}
	}

	template<typename Iterator>
	void _stable_swap(Iterator i, Iterator j) {
		typename std::iterator_traits<Iterator>::value_type temp = std::move(*j);

		for (Iterator k = j; k != i; --k) {
			*k = std::move(*std::prev(k));
		}

		*i = std::move(temp);
	}

	template<typename Iterator, typename Compare>
	void _stable_selection_sort(Iterator first, Iterator last, const Compare comp) {
		for (Iterator i = first; i != last; ++i) {
			Iterator min = std::min_element(i, last, comp);

			if (min != i) {
				_stable_swap(i, min);
			}
		}
	}

	template<typename Iterator, typename Compare>
	void _double_selection_sort(Iterator first, Iterator last, const Compare comp) {
		typename std::iterator_traits<Iterator>::difference_type end = std::distance(first, last) / 2;

		Iterator low = first;
		Iterator high = last;

		for (typename std::iterator_traits<Iterator>::difference_type index = 0; index < end; ++index) {
			std::pair<Iterator, Iterator> minmax = std::minmax_element(low, high, comp);

			Iterator beforeHigh = std::prev(high);

			std::iter_swap(low, minmax.first);

			if (comp(*minmax.second, *minmax.first)) {
				std::iter_swap(minmax.first, beforeHigh);
			}
			else {
				std::iter_swap(minmax.second, beforeHigh);
			}

			++low;
			--high;
		}
	}

	template<typename Iterator, typename Compare>
	void selection_sort(Iterator first, Iterator last, const selection_sort_type type, const Compare comp) {
		switch (type) {
		case selection_sort_type::NORMAL:
			_normal_selection_sort(first, last, comp);
			break;
		case selection_sort_type::STABLE:
			_stable_selection_sort(first, last, comp);
			break;
		case selection_sort_type::DOUBLE:
			_double_selection_sort(first, last, comp);
			break;
		default:
			throw std::invalid_argument("Invalid selection sort type");
		}
	}

	template<typename Iterator>
	void selection_sort(Iterator first, Iterator last, const selection_sort_type type) {
		selection_sort(
			first,
			last,
			type,
			std::less<typename std::iterator_traits<Iterator>::value_type>()
		);
	}
}
