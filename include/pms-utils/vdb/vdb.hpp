#include "pms-utils/atom/atom.hpp"
#include "pms-utils/depend/depend.hpp"

#include <cstdint>
#include <expected>
#include <filesystem>
#include <optional>

namespace pms_utils::vdb {

struct Entry {
    Entry(const std::filesystem::path &);

    depend::DependExpr bdepend;
    std::optional<std::string> binpkgmd5;
    std::uint64_t build_id;
    std::uint64_t build_time;
    depend::DependExpr depend;
    depend::DependExpr rdepend;
    std::vector<pms_utils::atom::Useflag> use;
};

} // namespace pms_utils::vdb
