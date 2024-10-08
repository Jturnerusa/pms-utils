#include "profile.hpp"

#include "../common.hpp"
#include "pms-utils/atom/atom.hpp"
#include "pms-utils/profile/profile.hpp"
#include "pms-utils/repo/repo.hpp"

#include <filesystem>
#include <memory>
#include <pybind11/pybind11.h>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

namespace py = pybind11;

using namespace pms_utils::profile;

namespace pms_utils::bindings::python::profile {

void _register(py::module &_module) {
    py::module profile = _module.def_submodule("profile");

    profile.def("expand_package_expr",
                static_cast<std::vector<std::tuple<atom::PackageExpr, std::string>> (&)(
                    std::string_view, const std::vector<repo::Repository> &)>(expand_package_expr));

    auto py_Filters = create_bindings<Filters>(profile);
    auto py_Profile = create_bindings<Profile, std::shared_ptr<Profile>>(profile)
                          .def(py::init<std::filesystem::path>())
                          .def("effective_useflags", &Profile::effective_useflags);
    auto py_PortageProfile = create_bindings<PortageProfile, std::shared_ptr<PortageProfile>>(profile).def(
        py::init<std::filesystem::path>());
}

} // namespace pms_utils::bindings::python::profile
