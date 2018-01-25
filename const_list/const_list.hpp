#include <cstdint>

// forward declaration just for the detail functions
template <typename T, T... Items>
class const_list;

namespace detail {

    template <typename T, T _>
    constexpr const_list<T> const_list_next(const const_list<T, _>&) {
        return const_list<T>();
    }

    template <typename T, T x, T... Items>
    constexpr const_list<T, Items...> const_list_next(const const_list<T, x, Items...>&) {
        return const_list<T, Items...>();
    }

    template <typename T, T x, T... Items>
    constexpr T get_first(const const_list<T, x, Items...>&) {
        return x;
    }

    template <typename T, typename U, T... Items>
    constexpr void for_each(const const_list<T, Items...>& l, const U& u) {
        u(get_first(l));
        auto m = const_list_next(l);
        m.for_each(u);
    }

    template< typename T, T x, typename R, typename U, T... Items >
    constexpr R accumulate(const const_list<T, x, Items...>& l, const U& u, const R& identity) {
        return u(x, const_list_next(l).accumulate(u, identity));
    }


}

/**
 * list of compile-time constants
 * (not as in std::list)
 */
template <typename T, T... Items>
class const_list
{
public:
    constexpr const_list begin() const {
        return *this;
    }

    constexpr const_list<T> end() const {
        return const_list<T>();
    }

    constexpr bool operator==(const const_list&) const {
        return true;
    }

    constexpr bool operator!=(const const_list&) const {
        return false;
    }

    template <typename U, U... x>
    constexpr bool operator==(const const_list<U, x...>&) const {
        return false;
    }

    template <typename U, U... x>
    constexpr bool operator!=(const const_list<U, x...>&) const {
        return true;
    }

    constexpr std::size_t size() const {
        return sizeof...(Items);
    }

    constexpr bool empty() const {
        return size() == 0;
    }

    constexpr auto operator++() -> decltype(detail::const_list_next(*this)) const {
        return detail::const_list_next(*this);
    }

    constexpr T operator*() const {
        return detail::get_first(*this);
    }

    template<typename U>
    constexpr void for_each(const U& u) const {
        detail::for_each(*this, u);
    }

    template< typename R, typename U>
    constexpr R accumulate(const U& u, const R& identity) {
        return detail::accumulate(*this, u, identity);
    }
};

// specialization for empty list
template <typename T>
class const_list<T>
{
public:
    constexpr const_list begin() const {
        return *this;
    }

    constexpr const_list end() const {
        return *this;
    }

    constexpr std::size_t size() const {
        return 0;
    }

    constexpr bool empty() const {
        return true;
    }

    constexpr bool operator==(const const_list&) const {
        return true;
    }

    constexpr bool operator!=(const const_list&) const {
        return false;
    }

    template<typename U, U... x>
    constexpr bool operator==(const const_list<U, x...>&) const {
        return false;
    }

    template<typename U, U... x>
    constexpr bool operator!=(const const_list<U, x...>&) const {
        return true;
    }

    constexpr auto operator++() -> decltype(this) const {
        return this;
    }

    constexpr T operator*() const {
        static_assert("dereferencing past-the-end iterator");
    } // you are probably iterating an empty list.

    template< typename U>
    constexpr void for_each(const U&) const {}

    template< typename R, typename U >
    constexpr R accumulate(const U&, const R& identity) const { return identity; }

};
