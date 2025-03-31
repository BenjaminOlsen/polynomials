// poly.hpp
#pragma once

#include <array>
#include <utility>
#include <type_traits>

// C++17-compatible to_array helper
namespace poly {

    // Convert a parameter pack into a std::array<T, N>
    template <typename T>
    constexpr std::array<T, 0> to_array() {
        return {};
    }

    template <typename T, typename... U>
    constexpr std::array<T, sizeof...(U)> to_array(U... elems) {
        return std::array<T, sizeof...(U)>{{static_cast<T>(elems)...}};
    }

    // Check if all elements in a std::array are zero
    template <typename T, std::size_t N>
    constexpr bool all_zeros(const std::array<T, N>& arr) {
        for (std::size_t i = 0; i < N; ++i) {
            if (arr[i] != T(0)) return false;
        }
        return true;
    }

    // trim_trailing_zeros<T, Values...>:
    // Returns std::integer_sequence<T, ...> with trailing 0s removed
    template <typename T, T... Values>
    struct trim_trailing_zeros;

    // Base case: empty pack
    template <typename T>
    struct trim_trailing_zeros<T> {
        using type = std::integer_sequence<T>;
        static constexpr auto value = to_array<T>();
    };

    // Recursive case
    template <typename T, T Head, T... Tail>
    struct trim_trailing_zeros<T, Head, Tail...> {
    private:
        using tail_trimmed = typename trim_trailing_zeros<T, Tail...>::type;
        static constexpr auto tail_array = trim_trailing_zeros<T, Tail...>::value;
        static constexpr bool all_tail_zeros = all_zeros(tail_array);

    public:
        using type = std::conditional_t<
            all_tail_zeros && Head == T(0),
            tail_trimmed,
            std::integer_sequence<T, Head, Tail...>
        >;

        static constexpr auto value = to_array<T>(Head, Tail...);
    };

} // namespace poly

