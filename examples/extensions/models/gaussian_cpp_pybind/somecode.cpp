
/*
 <%
 setup_pybind11(cfg)
 cfg['libraries'] = ['armadillo']
 %>
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <vector>
#include <armadillo>
#include <iostream>

using namespace arma;
using namespace std;
namespace py = pybind11;



// Simulation function of the gaussian model
std::vector<double> gaussian_cpp(double mu, double sigma, int k, int seed = 1) {
	arma_rng::set_seed(seed);
	vec output = randn<vec>(k);
	output = output*sigma + mu;
	//output.transform( [](double val) { return ( (val + mu) / sigma ); } );
	std::vector<double> std_output = conv_to<std::vector<double>>::from(output);
	return(std_output);
}


PYBIND11_PLUGIN(somecode) {
    pybind11::module m("somecode", "auto-compiled c++ extension");
    m.def("gaussian_cpp", &gaussian_cpp);
    return m.ptr();
}