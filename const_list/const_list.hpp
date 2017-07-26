
#include <cassert>
template <typename T, T... Items>
class const_list
{

    template <T ... ItItems>
    class Iterator {
        constexpr Iterator<> make_iter() const {
            return Iterator<>();
        }

        template <T, T ... i, typename ... X>
        constexpr Iterator<i...> make_iter(X...) const {
            return Iterator<i...>();
        }

        constexpr T get_head() const {
            assert(false && "dereferencing end iterator");
        }

        template <typename ... Args>
        constexpr T get_head(T head, Args...) const {
            return head;
        }
    public:
        constexpr T operator*() const {
            return get_head(ItItems...);
        }

        constexpr T operator->() const {
            return get_head(ItItems...);
        }

        constexpr bool operator==(const Iterator& other) const {
            return true;
        }
        constexpr bool operator!=(const Iterator& other) const {
            return false;
        }

        template <typename U, U ... X>
        constexpr bool operator==(const Iterator<X...>&) const {
            return false;
        }
        template <typename U, U ... X>
        constexpr bool operator!=(const Iterator<X...>&) const {
            return true;
        }

        constexpr auto operator++(int) const -> decltype(make_iter<ItItems...>(ItItems...)) {
            return make_iter<ItItems...>();
        }

        constexpr auto operator++() const -> decltype(make_iter<ItItems...>(ItItems...)) {
            return make_iter<ItItems...>;
        }
    };

public:

    using iterator=Iterator<Items...>;

    constexpr iterator find(const T& t) const {
        if (t == get_head(Items...)) {
            return *this;
        }
        return const_list<T, Items...>().find(t);
    }

    constexpr iterator begin() const {
        return iterator();
    }

    constexpr Iterator<> end() const {
        return Iterator<>();
    }

    constexpr bool empty() const {
        return false;
    }

    constexpr int size() const {
        return sizeof...(Items);
    }
};
