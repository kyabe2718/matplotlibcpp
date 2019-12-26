#include <matplotlibcpp.hpp>

#include <boost/core/demangle.hpp>
#include <iostream>
#include <string>


int main()
{
    using namespace Flier;
    std::vector<double> x{1, 2, 3};
    std::vector<double> y{1, 2, 3};
    plt.scatter(x, y, std::make_pair("alpha", 0.5));
    plt.show();
}
