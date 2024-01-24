#include "atom/atom.hpp"
#include "atom/atom_parser.hpp"

#include <string>

using namespace pms_utils::atom;
namespace parsers = pms_utils::parsers;

int main() {
    bool ret = true;

    // TODO: migrate to x3_util::try_parse
    const std::string str = "[foo(-)?,bar(+),!baz(+)?]";
    Usedeps usedeps;
    auto begin = str.begin();
    const auto end = str.end();
    ret = parse(begin, end, parsers::use_deps(), usedeps);

    if (!ret) {
        return 1;
    }

    if (begin != end) {
        std::cerr << "parser did not consume all input, remaining: " << std::string_view{begin, end} << '\n';
        return 1;
    }
}