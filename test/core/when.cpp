/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/core/when.hpp>
using namespace boost::hana;


template <typename T, typename = when<true>>
struct base_template;

template <typename T>
struct base_template<T, when_valid<typename T::first_type>> { };

template <typename T>
struct base_template<T, when_valid<typename T::second_type>> { };

struct First { struct first_type; };
struct Second { struct second_type; };

template struct base_template<First>;
template struct base_template<Second>;

int main() { }
