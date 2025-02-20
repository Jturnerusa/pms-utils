#include <cerrno>
#include <expected>
#include <filesystem>
#include <fstream>
#include <vector>

namespace pms_utils::misc {
std::expected<std::vector<char>, int> try_readfile(const std::filesystem::path &path) {
    auto file_size = std::filesystem::file_size(path);

    if (file_size == 0) {
        return {};
    }

    std::ifstream fsteam(path, std::ios::binary);

    if (!fsteam.is_open()) {
        return std::unexpected(errno);
    }

    std::vector<char> buffer(file_size);

    fsteam.read(buffer.data(), file_size);

    return buffer;
}
} // namespace pms_utils::misc
