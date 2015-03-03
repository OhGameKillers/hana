/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/assert.hpp>
#include <boost/hana/core/datatype.hpp>
#include <boost/hana/core/default.hpp>

#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
using namespace boost::hana;


//! [default_]
// In the header defining the concept of a Printable
template <typename T>
struct print_impl : default_ {
    template <typename Stream, typename X>
    static void apply(Stream& out, X const& x)
    { out << x; }
};

auto print = [](auto& stream, auto const& x) {
    return print_impl<datatype_t<decltype(x)>>::apply(stream, x);
};

// In some other header
template <typename T>
struct print_impl<std::vector<T>> {
    template <typename Stream>
    static void apply(Stream& out, std::vector<T> const& xs) {
        out << '[';
        std::copy(begin(xs), end(xs), std::ostream_iterator<T>{out, ", "});
        out << ']';
    }
};

static_assert(is_default<print_impl<int>>{}, "");
static_assert(!is_default<print_impl<std::vector<int>>>{}, "");
//! [default_]

int main() {
    {
        std::stringstream s;
        print(s, std::vector<int>{1, 2, 3});
        BOOST_HANA_RUNTIME_CHECK(s.str() == "[1, 2, 3, ]");
    }

    {
        std::stringstream s;
        print(s, "abcd");
        BOOST_HANA_RUNTIME_CHECK(s.str() == "abcd");
    }
}
