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

namespace pms_utils::vdb {

namespace {

struct Error {
public:
    Error() = default;
    virtual ~Error();
    virtual void error(std::string) = 0;
};

struct ParseError : Error {
public:
    ParseError(std::string unconsumed) : unconsumed(std::move(unconsumed)) {};

    void error(std::string message) override {
        throw std::runtime_error(std::format("parser error: {}", message));
    };

private:
    std::string unconsumed;
};

struct NotANumber : Error {
public:
    NotANumber(std::string data) : data(std::move(data)) {};

    void error(std::string message) override {
        throw std::runtime_error(std::format("not a number: {}", message));
    };

private:
    std::string data;
};

struct IoError : Error {
public:
    IoError(int err) : err(err) {};

    void error(std::string message) override {
        throw std::runtime_error(std::format("{}: IO error: {}", message, std::strerror(err)));
    };

private:
    int err;
};

template <typename T, typename I> std::expected<I, NotANumber> read_int(T data) {
    I number;

    auto [ptr, err] = std::from_chars(data.data(), data.data() + data.size(), number);

    if (!(err == std::errc{})) {
        return std::unexpected(NotANumber(std::string(data.begin(), data.end())));
    }

    return number;
}

std::expected<std::uint64_t, std::unique_ptr<Error>> read_int_entry(const std::filesystem::path &path) {
    auto readfile_result = pms_utils::misc::try_readfile(path);

    if (!readfile_result) {
        return std::unexpected(std::make_unique<IoError>(IoError(readfile_result.error())));
    }

    auto read_int_result = read_int<std::vector<char>, std::uint64_t>(readfile_result.value());

    if (!read_int_result) {
        return std::unexpected(std::make_unique<NotANumber>(NotANumber(read_int_result.error())));
    }

    return read_int_result.value();
}

template <typename T> T unwrap(std::expected<T, std::unique_ptr<Error>> result, std::string message) {
    if (!result) {
        result.error()->error(std::move(message));
    }

    return *result;
}

std::expected<depend::DependExpr, std::unique_ptr<Error>> read_depend(const std::filesystem::path &path) {
    auto readfile_result = pms_utils::misc::try_readfile(path);

    if (!readfile_result) {
        return std::unexpected(std::make_unique<IoError>(IoError(readfile_result.error())));
    }

    const auto &buffer = readfile_result.value();

    auto parse_result = pms_utils::misc::try_parse(std::string_view(buffer.begin(), buffer.end()),
                                                   pms_utils::parsers::depend::group, true);

    if (!parse_result) {
        return std::unexpected(std::make_unique<ParseError>(ParseError(std::string(parse_result.error()))));
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
};
} // namespace pms_utils::vdb

// namespace pms_utils::vdb
