#include <cstdlib>
#include <type_traits>

namespace args {

template <char C>
struct char_marker {
    constexpr char operator()() const { return C; }
};

template <typename Char, typename First, typename... Types>
class Args {
    Args<Char, First> head;
    Args<Types...> tail;

   public:
    template <typename Char2>
    typename std::enable_if_t<std::is_same<Char, Char2>::value, First> get()
        const {
        return head.template get<Char2>();
    }

    template <typename Char2>
    typename std::enable_if_t<!std::is_same<Char, Char2>::value,
                              decltype(tail.template get<Char2>())>
    get() const {
        return tail.template get<Char2>();
    }
};

template <typename Char, typename First>
struct Args<Char, First> {
    char name = Char{}();
    First value;

   public:
    template <typename Char2>
    typename std::enable_if_t<std::is_same<Char, Char2>::value, First> get()
        const {
        return value;
    }
};

}  // namespace args
