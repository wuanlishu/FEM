#include "Material.h"

void Material::matValidCheck() const {
    if(this->E<=0){
        throw std::invalid_argument("Young's Modulus must be positive number.");
    }
    if(this->Nu<-1.0 || this->Nu>=0.5){
        throw std::invalid_argument("Poisson's Ratio must between -1.0 to 0.5.");
    }
    if(std::abs(1 - this->E / (2.0 * (1.0 + this->Nu) * this->G)) >= 1.0e-2){
        throw std::invalid_argument("E, G and Nu relationship is wrong. Please check!");
    }
}
