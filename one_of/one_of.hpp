#ifndef ONE_OF_H
#define ONE_OF_H

template< typename T, T ... vals >
class one_of
{
    constexpr bool equals(const T&) {
        return false;
    }

    template <typename ... Args>
    constexpr bool equals(const T& t, const T& u, const Args & ...args) {
        return (t == u) || equals(t, args...);
    }

public:
    constexpr bool operator()(const T& val) {
        return equals(val, vals...);
    }
};
#endif /* ONE_OF_H */
