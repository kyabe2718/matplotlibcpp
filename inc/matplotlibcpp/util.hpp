#pragma once

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

namespace matplotlibcpp
{
namespace py = boost::python;
namespace np = boost::python::numpy;

template <class T, class = std::enable_if_t<std::is_arithmetic_v<typename T::value_type>>>
np::ndarray to_ndarray(const T& vec)
{
    auto shape = py::make_tuple(vec.size());
    auto dtype = np::dtype::get_builtin<typename T::value_type>();
    auto strides = py::make_tuple(sizeof(typename T::value_type));
    py::object owner;
    return np::from_data(static_cast<const void*>(vec.data()), dtype, shape, strides, owner).copy();
}

template <class... TKWArgs>
py::dict to_dict(const std::pair<const char*, TKWArgs>&... kwargs)
{
    py::dict ret;
    ((ret[kwargs.first] = kwargs.second), ...);
    return ret;
}
}  // namespace matplotlibcpp
