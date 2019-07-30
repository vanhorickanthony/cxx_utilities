//============================================================================
// @name        : utils.h
// @author      : Anthony Van Horick
// @date        : 2019-07-30
// @description :
//============================================================================

#ifndef UTILS_HH
#define UTILS_HH

#include <iostream>
#include <type_traits>
#include <cstdint>
#include <stdio.h>



/* To define whether a type T is a container, it has to own several properties:
 * a const_iterator/iterator, a begin and an end.
 */

/*!
 * @function	: has_const_iterator
 * @brief		: Check whether the given type has an iterator.
 *				  The member 'value' holds a boolean indicating whether
 *				  it has an iterator or not.
 */
template < typename T >
struct has_const_iterator
{
private:

    template< typename C > static std::true_type test(typename C::const_iterator*) noexcept;
    template< typename C > static std::false_type test(...) noexcept;

public:

    static const bool value = std::is_same< std::true_type, decltype(test<T>(nullptr)) >::value;

};

template < typename T >
struct has_begin
{
private:

	template< class C > static std::true_type test(decltype(std::declval<C>().begin()) * ) noexcept;
	template< class C > static std::false_type test(...) noexcept;

public:

	static const bool value = std::is_same<std::true_type, decltype(test<T>(nullptr))>::value;

};

template < typename T >
struct has_end
{
private:

	template< class C > static std::true_type test(decltype(std::declval<C>().end()) * ) noexcept;
	template< class C > static std::false_type test(...) noexcept;

public:

	static const bool value = std::is_same<std::true_type, decltype(test<T>(nullptr))>::value;

};

template < typename T >
struct is_container
{
public:

	static const bool begin = has_begin<T>::value;
	static const bool end = has_begin<T>::value;
	static const bool const_iterator = has_const_iterator<T>::value;

	static const bool value = (begin && end && const_iterator);

};

template < typename T, typename std::enable_if<!std::is_pointer<T>::value, void>::type* = nullptr >
bool _dcompare(const T& lhs, const T& rhs) noexcept { return lhs == rhs; }

template < typename T, typename std::enable_if<std::is_pointer<T>::value, void>::type* = nullptr >
bool _dcompare(const T& lhs, const T& rhs) noexcept { return _dcompare(*lhs, *rhs); }

template < typename T, typename std::enable_if<!is_container<T>::value, void>::type* = nullptr >
bool _compare(const T& lhs, const T& rhs) noexcept { return _dcompare(lhs, rhs);}

template < typename T, typename std::enable_if<is_container<T>::value, void>::type* = nullptr >
bool _compare(const T& lhs, const T& rhs) noexcept {
	if (lhs.size() != rhs.size()) return false;
	typename T::const_iterator lhs_it = lhs.begin();
	typename T::const_iterator rhs_it = rhs.begin();
	while(lhs_it != lhs.end(), rhs_it != rhs.end()) {
		if (!_compare(*lhs_it, *rhs_it)) return false;
		lhs_it = std::next(lhs_it, 1);
		rhs_it = std::next(rhs_it, 1);
	}
	return true;
};

#endif /* UTILS_HH */
