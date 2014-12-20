#include "SpecularMaterial.hpp"
#include "Constants.hpp"

AngleSample SpecularBRDF::sample(double theta_in, Sampler& sampler) {
    return { theta_in, Constants::PI, reflected };
}
