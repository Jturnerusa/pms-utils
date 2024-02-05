#pragma once

#include "depend.hpp"
#include "pms-utils/misc/x3_utils.hpp"

#include <boost/spirit/home/x3.hpp>

namespace [[gnu::visibility("default")]] pms_utils {
namespace parsers {

namespace x3 = boost::spirit::x3;

PARSER_RULE_T(use_cond, depend::UseConditional);
PARSER_RULE_T(conds, depend::GroupHeader);

PARSER_RULE_T(group, depend::DependExpr);
PARSER_RULE_T(node, depend::DependExpr::Node);
PARSER_RULE_T(nodes, depend::DependExpr);

} // namespace parsers
} // namespace pms_utils
