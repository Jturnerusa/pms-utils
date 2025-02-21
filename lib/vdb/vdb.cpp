#include "pms-utils/depend/depend.hpp"
#include "pms-utils/depend/depend_parser.hpp"
#include "pms-utils/misc/readfile.hpp"
#include "pms-utils/misc/try_parse.hpp"
#include "pms-utils/vdb/vdb.hpp"

#include <algorithm>
#include <boost/parser/parser.hpp>
#include <charconv>
#include <cstdint>
#include <cstring>
#include <expected>
#include <filesystem>
#include <format>
#include <memory>
#include <stdexcept>
#include <variant>

namespace pms_utils::vdb {

namespace {

struct IoError {
    int err;
};

struct ParseError {
    std::string unconsumed;
};

struct NotANumber {
    std::string data;
};

using Error = std::variant<IoError, ParseError, NotANumber>;

template <typename T, typename I> std::expected<I, NotANumber> read_int(T data) {
    I number;

    auto [ptr, err] = std::from_chars(data.data(), data.data() + data.size(), number);

    if (!(err == std::errc{})) {
        return std::unexpected(NotANumber(std::string(data.begin(), data.end())));
    }

    return number;
}

std::expected<std::uint64_t, Error> read_int_entry(const std::filesystem::path &path) {
    auto readfile_result = pms_utils::misc::try_readfile(path);

    if (!readfile_result) {
        return std::unexpected(IoError{.err = readfile_result.error()});
    }

    auto read_int_result = read_int<std::vector<char>, std::uint64_t>(readfile_result.value());

    if (!read_int_result) {
        return std::unexpected(
            NotANumber{std::string(readfile_result.value().begin(), readfile_result.value().end())});
    }

    return read_int_result.value();
}

template <class... Ts> struct overloaded : Ts... {
    using Ts::operator()...;
};

template <typename T> T unwrap(std::expected<T, Error> result, std::string message) {

    std::visit(overloaded{[&message](IoError error) {
                   throw std::runtime_error(
                       std::format("{}: IO error: {}", message, std::strerror(error.err)));
               }},
               result.error());

    return *result;
}

std::expected<depend::DependExpr, Error> read_depend(const std::filesystem::path &path) {
    auto readfile_result = pms_utils::misc::try_readfile(path);

    if (!readfile_result) {
        return std::unexpected(IoError{.err = readfile_result.error()});
    }

    const auto &buffer = readfile_result.value();

    auto parse_result = pms_utils::misc::try_parse(std::string_view(buffer.begin(), buffer.end()),
                                                   pms_utils::parsers::depend::group, true);

    if (!parse_result) {
        return std::unexpected(ParseError{.unconsumed = std::string(parse_result.error())});
    }

    return parse_result.value();
}

} // namespace
// namespace

Entry::Entry(const std::filesystem::path &path) {
    _depend = unwrap(read_depend(path / "DEPEND"), "failed to load DEPEND");
    _bdepend = unwrap(read_depend(path / "DEPEND"), "failed to load BDEPEND");
    _rdepend = unwrap(read_depend(path / "DEPEND"), "failed to load RDEPEND");
    _build_id = unwrap(read_int_entry(path / "BUILD_ID"), "failed to load BUILD_ID");
    _build_time = unwrap(read_int_entry(path / "BUILD_TIME"), "failed to load BUILD_TIME");
};
} // namespace pms_utils::vdb

// namespace pms_utils::vdb
