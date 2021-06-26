#pragma once


#include <iterator>
#include <functional>
#include <stdexcept>

namespace sort {
	enum class selection_sort_type { NORMAL, STABLE, DOUBLE };

	template<typename Iterator, typename Compare>
	Iterator _find_min(Iterator first, Iterator last, const Compare comp) {
		Iterator min = first;

		for (Iterator i = std::next(first); i != last; ++i) {
			if (comp(*i, *min)) {
				min = i;
			}
		}

		return min;
	}

	template<typename Iterator, typename Compare>
	Iterator _find_max(Iterator first, Iterator last, const Compare comp) {
		Iterator max = first;

		for (Iterator i = std::next(first); i != last; ++i) {
			if (comp(*max, *i)) {
				max = i;
			}
		}

		return max;
	}

	template<typename Iterator, typename Compare>
	void _normal_selection_sort(Iterator first, Iterator last, const Compare comp) {
		for (Iterator i = first; i != last; ++i) {
			Iterator min = _find_min(i, last, comp);

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
			Iterator min = _find_min(i, last, comp);

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
			Iterator min = _find_min(low, high, comp);
			Iterator max = _find_max(low, high, comp);

			Iterator beforeHigh = std::prev(high);

			std::iter_swap(low, min);

			if (comp(*max, *min)) {
				std::iter_swap(min, beforeHigh);
			}
			else {
				std::iter_swap(max, beforeHigh);
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
