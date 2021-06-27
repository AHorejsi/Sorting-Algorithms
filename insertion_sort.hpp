#pragma once


#include <iterator>
#include <functional>
#include <stdexcept>

namespace sort {
	namespace _utils {
		template<typename Iterator, typename Compare>
		Iterator _linear_search(Iterator first, Iterator last, const Compare comp) {
			Iterator i = first;

			while (i != last) {
				if (comp(*last, *i)) {
					break;
				}

				++i;
			}

			return i;
		}

		template<typename Iterator, typename Compare>
		Iterator _binary_search_util(Iterator first, Iterator last, const Compare comp, typename std::iterator_traits<Iterator>::reference key) {
			if (first == last || first == last + 1) {
				return first;
			}

			Iterator low = first;
			Iterator high = last - 1;

			while (low <= high) {
				Iterator mid = low + (high - low) / 2;

				if (comp(*mid, key)) {
					low = mid + 1;
				}
				else if (comp(key, *mid)) {
					if (mid == first) {
						break;
					}
					else {
						high = mid - 1;
					}
				}
				else {
					return mid;
				}
			}

			return low;
		}

		template<typename Iterator, typename Compare>
		Iterator _binary_search(Iterator first, Iterator last, const Compare comp) {
			return _binary_search_util(first, last, comp, *last);
		}

		template<typename Iterator, typename Compare>
		Iterator _jump_search(Iterator first, Iterator last, const Compare comp) {
			typename std::iterator_traits<Iterator>::difference_type size = last - first;
			typename std::iterator_traits<Iterator>::difference_type step = (typename std::iterator_traits<Iterator>::difference_type)std::sqrt(size);
			typename std::iterator_traits<Iterator>::difference_type prev = 0;

			while (comp(first[std::min(step, size)], *last)) {
				prev = step;
				step += step;

				if (prev >= size) {
					return first + prev;
				}
			}

			typename std::iterator_traits<Iterator>::difference_type end = std::min(step, size);

			while (comp(first[prev], *last)) {
				++prev;

				if (prev == end) {
					break;
				}
			}

			return first + prev;
		}

		template<typename Iterator, typename Compare>
		auto _get_searcher(const searcher searchType)->Iterator(*)(Iterator, Iterator, const Compare) {
			switch (searchType) {
			case searcher::LINEAR:
				return _linear_search;
			case searcher::BINARY:
				return _binary_search;
			case searcher::JUMP:
				return _jump_search;
			default:
				throw std::invalid_argument("Invalid search type");
			}
		}
	}

	enum class searcher { LINEAR, BINARY, JUMP };

	template<typename Iterator, typename Compare>
	void insertion_sort(Iterator first, Iterator last, const searcher searchType, const Compare comp) {
		using namespace _utils;

		Iterator(*searchFunc)(Iterator, Iterator, const Compare) = _get_searcher<Iterator, Compare>(searchType);

		for (Iterator i = std::next(first); i != last; ++i) {
			Iterator sortedPosition = searchFunc(first, i, comp);

			for (Iterator j = i; j != sortedPosition; --j) {
				std::iter_swap(j, std::prev(j));
			}
		}
	}

	template<typename Iterator>
	void insertion_sort(Iterator first, Iterator last, const searcher searchType) {
		insertion_sort(
			first,
			last,
			searchType,
			std::less<typename std::iterator_traits<Iterator>::value_type>()
		);
	}
}
