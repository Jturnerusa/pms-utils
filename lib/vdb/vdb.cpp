#include "pms-utils/misc/readfile.hpp"
#include "pms-utils/misc/try_parse.hpp"
#include "pms-utils/vdb/vdb.hpp"

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
    virtual void error(std::string) = 0;
};

struct ParseError : Error {
public:
    ParseError(std::string unconsumed) : unconsumed(std::move(unconsumed)) {};
    virtual ~ParseError() = default;

    void error(std::string message) override {
        throw std::runtime_error(std::format("parser error: {}", message));
    };

private:
    std::string unconsumed;
};

struct NotANumber : Error {
public:
    NotANumber(std::string data) : data(std::move(data)) {};
    virtual ~NotANumber() = default;

    void error(std::string message) override {
        throw std::runtime_error(std::format("not a number: {}", message));
    };

private:
    std::string data;
};

struct IoError : Error {
public:
    IoError(int err) : err(err) {};
    virtual ~IoError() = default;

    void error(std::string message) override { throw std::runtime_error(std::format("IO error")); };

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

std::expected<std::uint64_t, std::unique_ptr<Error>> read_build_id(const std::filesystem::path &path) {
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

    return result.value();
}

} // namespace
// namespace

Entry::Entry(const std::filesystem::path &path) {
    _build_id = unwrap(read_build_id(path / "BUILD_ID"), "failed to load BUILD_ID");
};
} // namespace pms_utils::vdb

// namespace pms_utils::vdb
