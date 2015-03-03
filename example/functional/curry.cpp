/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/assert.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/functional.hpp>
using namespace boost::hana;


int main() {
    //! [main]
    BOOST_HANA_CONSTEXPR_LAMBDA auto add = [](auto x, auto y, auto z) {
        return x + y + z;
    };

    BOOST_HANA_CONSTEXPR_CHECK(curry<3>(add)(1)(2)(3) == 1 + 2 + 3);
    BOOST_HANA_CONSTEXPR_CHECK(curry<3>(add)(1)(2, 3) == curry<3>(add)(1)(2)(3));
    BOOST_HANA_CONSTEXPR_CHECK(curry<3>(add)(1, 2, 3) == curry<3>(add)(1)(2)(3));
    //! [main]


    //! [curry0]
    BOOST_HANA_CONSTEXPR_LAMBDA auto two = []() {
        return 2;
    };

    BOOST_HANA_CONSTEXPR_CHECK(curry<0>(two)() == two());
    //! [curry0]
}
