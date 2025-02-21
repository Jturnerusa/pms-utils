#include "pms-utils/vdb/vdb.hpp"

#include <filesystem>

int main() {
    auto vdb = std::filesystem::path("/var/db/pkg");

    for (const auto &category : std::filesystem::directory_iterator(vdb)) {
        for (const auto &pkg : std::filesystem::directory_iterator(category)) {
            auto entry = pms_utils::vdb::Entry(vdb / category / pkg);
        }
    }

    return 0;
}
