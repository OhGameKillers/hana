// Copyright Louis Dionne 2013-2016
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <boost/hana/ext/boost/tuple.hpp>
#include <boost/hana/tuple.hpp>
#include <laws/comparable.hpp>
#include <laws/orderable.hpp>
#include <boost/tuple/tuple.hpp>
#include <iostream>
namespace hana = boost::hana;


template <int i>
using eq = hana::test::ct_eq<i>;

template <int i>
using ord = hana::test::ct_ord<i>;

struct invalid { };
template <typename S, typename Eqs, typename Ords>
void tests(Eqs eqs, Ords ords) {
    using hana::test::implies;
    using hana::test::iff;

    // transitivity
    hana::test::foreach3(eqs, [](auto a, auto b, auto c) {
        std::cout << "Comparable 1 pass" << std::endl;
        auto ab = hana::equal(a, b);
        auto bc = hana::equal(b, c);
        auto ac = hana::equal(a, c);
        BOOST_HANA_CHECK(hana::and_(ab, bc) ^implies^ ac);
    });

    // transitivity
    hana::test::foreach3(ords, [](auto a, auto b, auto c) {
        std::cout << "Orderable 1 pass" << std::endl;
        auto ab = hana::less_equal(a, b);
        auto bc = hana::less_equal(b, c);
        auto ac = hana::less_equal(a, c);
        BOOST_HANA_CHECK(hana::and_(ab, bc) ^implies^ ac);
    });
}



int main() {
    auto eq_tuples = hana::make_tuple(
          ::boost::make_tuple()
        , ::boost::make_tuple(eq<0>{})
        , ::boost::make_tuple(eq<0>{}, eq<1>{})
        , ::boost::make_tuple(eq<0>{}, eq<1>{}, eq<2>{})
    );

    auto ord_tuples = hana::make_tuple(
          ::boost::make_tuple()
        , ::boost::make_tuple(ord<0>{})
        , ::boost::make_tuple(ord<0>{}, ord<1>{})
        , ::boost::make_tuple(ord<0>{}, ord<1>{}, ord<2>{})
    );

    tests<hana::ext::boost::tuple_tag>(eq_tuples, ord_tuples);
}
