/*
@copyright Louis Dionne 2014
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/bool.hpp>
#include <boost/hana/detail/constexpr.hpp>
#include <boost/hana/detail/static_assert.hpp>
#include <boost/hana/integral.hpp>
#include <boost/hana/list/instance.hpp>
#include <boost/hana/type.hpp>
using namespace boost::hana;
using namespace literals;


int main() {
    //! [fusion]
    BOOST_HANA_CONSTEXPR_LAMBDA auto odd = [](auto x) {
        return x % 2_c != 0_c;
    };

    BOOST_HANA_STATIC_ASSERT(all(odd, list(1, 3)));
    BOOST_HANA_STATIC_ASSERT(!all(odd, list(1, 2)));
    //! [fusion]

    //! [mpl]
    BOOST_HANA_STATIC_ASSERT(decltype_(all(odd, list(1_c, 3_c))) == decltype_(true_));
    BOOST_HANA_STATIC_ASSERT(decltype_(all(odd, list(1_c, 2_c))) == decltype_(false_));
    //! [mpl]
}
