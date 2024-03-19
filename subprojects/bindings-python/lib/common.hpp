#pragma once

#include <boost/core/demangle.hpp>
#include <boost/describe/enum_to_string.hpp>
#include <boost/describe/enumerators.hpp>
#include <boost/describe/members.hpp>
#include <boost/mp11.hpp>
#include <boost/mp11/list.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl/filesystem.h>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace py = pybind11;

namespace pms_utils::bindings::python {

template <typename Rule> [[nodiscard]] static inline auto expr_from_str(Rule rule, std::string_view str) {
    typename Rule::attribute_type ret;
    const auto *begin = str.begin();
    const auto *const end = str.end();
    if (!parse(begin, end, rule, ret)) {
        // TODO
        throw std::runtime_error("parser failed");
    }

    if (begin != end) {
        // TODO
        throw std::runtime_error(std::string("parser did not consume all input, remaining ") +
                                 std::string{begin, end});
    }

    return ret;
}

namespace _internal {

template <typename Test, template <typename...> class Ref> struct is_specialization : std::false_type {};

template <template <typename...> class Ref, typename... Args>
struct is_specialization<Ref<Args...>, Ref> : std::true_type {};

[[nodiscard]] constexpr std::string_view unqualified(std::string_view str) {
    return str.substr(str.find_last_of(':') + 1);
}

template <template <typename, typename> typename T, typename T1, typename T2> struct extract_crtp {
    using first = T1;
    using second = T2;

    explicit extract_crtp(T<T1, T2> /*unused*/){};
};

template <typename T>
concept is_crtp = requires {
    requires std::is_same_v<T, typename decltype(_internal::extract_crtp(typename T::Base()))::second>;
};

} // namespace _internal

template <typename T, typename M, typename R = bool>
    requires(std::is_enum_v<T> && boost::describe::has_describe_enumerators<T>::value)
static inline auto create_bindings(
    M module_, R rule = false,
    std::string name = std::string(_internal::unqualified(boost::core::demangle(typeid(T).name())))) {
    using namespace boost::mp11;

    auto ret = py::enum_<T>(module_, name.data());
    mp_for_each<boost::describe::describe_enumerators<T>>(
        [&ret](auto member) { ret.value(member.name, member.value); });
    ret.def("__str__", [](T val) { return boost::describe::enum_to_string(val, "BAD_ENUM"); });
    if constexpr (!std::is_same_v<R, bool>) {
        ret.def(py::init([rule](std::string_view str) { return expr_from_str(rule(), str); }));
    }
    return std::move(ret);
}

template <typename T, typename M, typename R = bool>
    requires(std::is_class_v<T> && boost::describe::has_describe_members<T>::value)
static inline auto create_bindings(
    M module_, R rule = false,
    std::string name = std::string(_internal::unqualified(boost::core::demangle(typeid(T).name())))) {
    using namespace boost::mp11;

    // this extracts the bases from T and transforms them such that py::class_<T, ...Bases>
    using bases = boost::describe::describe_bases<T, boost::describe::mod_any_access>;
    // if no inheritance, bases is empty and thus mp_first<bases> not a valid expression
    // otherwise, bases already contains T (why?)
    using t_plus_bases = mp_eval_or<mp_list<T>, mp_first, bases>;
    // for now, only declare inheritance for CRTP
    // need to figure out a way to prevent multiple declarations when e.g. two types inherit from std::string
    using pytype = std::conditional_t<_internal::is_crtp<T>, t_plus_bases, mp_list<T>>;
    static_assert(std::is_same_v<mp_first<pytype>, T>);
    using pyclass = mp_apply<py::class_, pytype>;

    // if we are doing CRTP, register the base type as an empty class
    if constexpr (_internal::is_crtp<T>) {
        using crtp_base = mp_second<pytype>;
        py::class_<crtp_base>(module_, (std::string("_crtp_") + name).data());
    }

    auto ret = pyclass(module_, name.data());
    mp_for_each<boost::describe::describe_members<T, boost::describe::mod_public>>(
        [&ret](auto member) { ret.def_readonly(member.name, member.pointer); });
    if constexpr (requires(const T &val) { std::string(val); }) {
        ret.def("__str__", [](const T &val) { return std::string(val); });
    }
    if constexpr (!std::is_same_v<R, bool>) {
        ret.def(py::init([rule](std::string_view str) { return expr_from_str(rule(), str); }));
    }

    // prevent exporting __iter__ for std::string types
    if constexpr (requires(const T &val) {
                      std::begin(val);
                      std::end(val);
                  } && !std::is_base_of_v<std::string, T>) {
        ret.def(
            "__iter__", [](const T &val) { return py::make_iterator(std::begin(val), std::end(val)); },
            py::keep_alive<0, 1>());
    }
    return std::move(ret);
}

} // namespace pms_utils::bindings::python
