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
    BOOST_HANA_CONSTEXPR_LAMBDA auto minus = [](int x, int y, int z = 0) {
        return x - y - z;
    };

    BOOST_HANA_CONSTEXPR_CHECK(minus(3, 0) == 3 - 0);
    BOOST_HANA_CONSTEXPR_CHECK(flip(minus)(3, 0) == 0 - 3);

    BOOST_HANA_CONSTEXPR_CHECK(minus(3, 0, 1) == 3 - 0 - 1);
    BOOST_HANA_CONSTEXPR_CHECK(flip(minus)(3, 0, 1) == 0 - 3 - 1);
    //! [main]
}
