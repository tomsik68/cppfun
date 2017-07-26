#include <cstdint>

/**
 * list of compile-time constants
 * (not as in std::list)
 */
template <typename T, T... Items>
class const_list
{
    template <>
    constexpr const_list<T> incr() const {
        return const_list<T>();
    }

    template <T... its>
    constexpr auto incr(T, T...) const -> decltype(const_list<T,its...>()) {
        return const_list<its...>();
    }

public:
    constexpr const_list<T, Items...> begin() const {
        return *this;
    }

    constexpr const_list<T> end() const {
        return const_list<T>();
    }

    /* constexpr auto find(const T& t) const; */

    /* TODO */
    /* constexpr auto operator++(); */

    constexpr auto operator++(int) const -> decltype(incr(Items...)) {
        return incr(Items...);
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
};
