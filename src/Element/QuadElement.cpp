#include "QuadElement.h"

std::vector<std::vector<double>> QuadElement::computeStiffnessMatrix() const  {
    // compute stifness matrix
    return std::vector<std::vector<double>>(3, std::vector<double>(3, 0.0));
}

std::vector<std::vector<double>> QuadElement::computeMassMatrix() const {
    return std::vector<std::vector<double>>(3, std::vector<double>(3, 1.0));
}

std::vector<double> QuadElement::computeStrain(const std::vector<double>& displacements) const {
    return std::vector<double>(4, 0.0);
}

std::vector<double> QuadElement::computeStress(const std::vector<double>& displacements) const {
    return std::vector<double>(4, 0.0);
}

double QuadElement::computeVolume() const {
    // compute quad area
    if (nodes.size() != 4) {
        throw std::runtime_error("QUAD4 element must have exactly 4 nodes.");
    }

    const auto& n0 = nodes[0];
    const auto& n1 = nodes[1];
    const auto& n2 = nodes[2];

    double x1 = n1->getX() - n0->getX();
    double y1 = n1->getY() - n0->getY();
    double x2 = n2->getX() - n0->getX();
    double y2 = n2->getY() - n0->getY();

    return 0.5 * std::abs(x1 * y2 - x2 * y1);
}