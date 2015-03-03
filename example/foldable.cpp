/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/assert.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/ext/std/integral_constant.hpp>
#include <boost/hana/functional.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/maybe.hpp>
#include <boost/hana/range.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>

#include <sstream>
#include <string>
#include <type_traits>
using namespace boost::hana;


int main() {

{

//! [foldl1]
auto to_string = [](auto x) {
    return static_cast<std::ostringstream const&>(std::ostringstream{} << x).str();
};

auto show = [=](auto x, auto y) {
    return "(" + to_string(x) + " + " + to_string(y) + ")";
};

BOOST_HANA_RUNTIME_CHECK(foldl1(make<Tuple>(1, "2", '3'), show) == "((1 + 2) + 3)");
//! [foldl1]

}{

//! [foldl]
auto to_string = [](auto x) {
    return static_cast<std::ostringstream const&>(std::ostringstream{} << x).str();
};

auto show = [=](auto x, auto y) {
    return "(" + to_string(x) + " + " + to_string(y) + ")";
};

BOOST_HANA_RUNTIME_CHECK(foldl(make<Tuple>(2, "3", '4'), "1", show) == "(((1 + 2) + 3) + 4)");
//! [foldl]

}{

//! [foldr]
auto to_string = [](auto x) {
    return static_cast<std::ostringstream const&>(std::ostringstream{} << x).str();
};

auto show = [=](auto x, auto y) {
    return "(" + to_string(x) + " + " + to_string(y) + ")";
};

BOOST_HANA_RUNTIME_CHECK(foldr(make<Tuple>(1, "2", '3'), "4", show) == "(1 + (2 + (3 + 4)))");
//! [foldr]

}{

//! [foldr1]
auto to_string = [](auto x) {
    return static_cast<std::ostringstream const&>(std::ostringstream{} << x).str();
};

auto show = [=](auto x, auto y) {
    return "(" + to_string(x) + " + " + to_string(y) + ")";
};

BOOST_HANA_RUNTIME_CHECK(foldr1(make<Tuple>(1, "2", '3'), show) == "(1 + (2 + 3))");
//! [foldr1]

}{

//! [for_each]
std::stringstream ss;
for_each(make<Tuple>(0, '1', "234", 5.5), [&](auto x) {
    ss << x << ' ';
});

BOOST_HANA_RUNTIME_CHECK(ss.str() == "0 1 234 5.5 ");
//! [for_each]

}{

//! [length]
BOOST_HANA_CONSTANT_CHECK(length(make<Tuple>()) == size_t<0>);
BOOST_HANA_CONSTANT_CHECK(length(make<Tuple>(1, '2', 3.0)) == size_t<3>);

BOOST_HANA_CONSTANT_CHECK(length(nothing) == size_t<0>);
BOOST_HANA_CONSTANT_CHECK(length(just('x')) == size_t<1>);
//! [length]

}{

//! [maximum]
BOOST_HANA_CONSTANT_CHECK(
    maximum(tuple_c<int, -1, 0, 2, -4, 6, 9>) == int_<9>
);
//! [maximum]
//!
}{

//! [minimum]
BOOST_HANA_CONSTANT_CHECK(
    minimum(tuple_c<int, -1, 0, 2, -4, 6, 9>) == int_<-4>
);
//! [minimum]

}{

//! [product]
BOOST_HANA_CONSTANT_CHECK(
    product(range(int_<1>, int_<6>)) == int_<1 * 2 * 3 * 4 * 5>
);

BOOST_HANA_CONSTEXPR_CHECK(
    product(make<Tuple>(1, int_<3>, long_<-5>, 9)) == 1 * 3 * -5 * 9
);
//! [product]

}{

//! [sum]
BOOST_HANA_CONSTANT_CHECK(
    sum(range(int_<1>, int_<6>)) == int_<1 + 2 + 3 + 4 + 5>
);

BOOST_HANA_CONSTEXPR_CHECK(
    sum(make<Tuple>(1, int_<3>, long_<-5>, 9)) == 1 + 3 - 5 + 9
);
//! [sum]

}{

//! [unpack]
auto cheap_tie = [](auto& ...vars) {
    return partial(flip(unpack), [&vars...](auto ...values) {
        // Using an initializer list sequences the assignments.
        int dummy[] = {((vars = values), 0)...};
        (void)dummy;
    });
};
int a = 0;
char b = '\0';
double c = 0;

cheap_tie(a, b, c)(make<Tuple>(1, '2', 3.3));
BOOST_HANA_RUNTIME_CHECK(a == 1 && b == '2' && c == 3.3);
//! [unpack]

}{

//! [fuse]
BOOST_HANA_CONSTEXPR_LAMBDA auto add = [](auto x, auto y) {
    return x + y;
};

// Would be `boost::fusion::make_fused(add)` in Boost.Fusion.
BOOST_HANA_CONSTEXPR_LAMBDA auto add_seq = fuse(add);

BOOST_HANA_CONSTEXPR_CHECK(add_seq(make<Tuple>(1, 2)) == add(1, 2));
//! [fuse]

}{

//! [count]
using namespace literals;
BOOST_HANA_CONSTEXPR_LAMBDA auto odd = [](auto x) {
    return x % 2_c != 0_c;
};

constexpr auto types = tuple_t<int, char, long, short, char, double>;
constexpr auto ints = tuple_c<int, 1, 2, 3>;

BOOST_HANA_CONSTANT_CHECK(count(ints, odd) == size_t<2>);

BOOST_HANA_CONSTANT_CHECK(count(types, trait<std::is_floating_point>) == size_t<1>);
BOOST_HANA_CONSTANT_CHECK(count(types, _ == type<char>) == size_t<2>);
BOOST_HANA_CONSTANT_CHECK(count(types, _ == type<void>) == size_t<0>);
//! [count]

}{

//! [maximum_by]
BOOST_HANA_CONSTEXPR_LAMBDA auto size = [](auto xs, auto ys) {
    return length(xs) < length(ys);
};

BOOST_HANA_CONSTEXPR_CHECK(
    maximum_by(size, make<Tuple>(make<Tuple>(), make<Tuple>(1, '2'), make<Tuple>(3.3, nullptr, 4)))
    ==
    make<Tuple>(3.3, nullptr, 4)
);
//! [maximum_by]

}{

//! [minimum_by]
BOOST_HANA_CONSTEXPR_LAMBDA auto size = [](auto xs, auto ys) {
    return length(xs) < length(ys);
};

BOOST_HANA_CONSTANT_CHECK(
    minimum_by(size, make<Tuple>(make<Tuple>(), make<Tuple>(1, '2'), make<Tuple>(3.3, nullptr, 4)))
    ==
    make<Tuple>()
);
//! [minimum_by]

}

}
