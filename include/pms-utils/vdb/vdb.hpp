#include "pms-utils/depend/depend.hpp"

#include <cstdint>
#include <expected>
#include <filesystem>
#include <optional>
#include <variant>

namespace pms_utils::vdb {

class Entry {
private:
    depend::DependExpr _bdepend;
    std::optional<std::string> _binpkgmd5;
    std::uint64_t _build_id;
    std::uint64_t _build_time;
    depend::DependExpr _depend;
    depend::DependExpr _rdepend;

public:
    Entry(const std::filesystem::path &);

    const depend::DependExpr &bdepend() { return _bdepend; }
    const std::optional<std::string> &binpkgmd5() { return _binpkgmd5; };
    const std::uint64_t build_id() { return _build_id; };
    const std::uint64_t build_time() { return _build_time; };
    const depend::DependExpr &depend() { return _depend; };
    const depend::DependExpr &rdepend() { return _rdepend; };
};

} // namespace pms_utils::vdb
