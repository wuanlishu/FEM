#include "TriElement.h"

std::vector<std::vector<double>> TriElement::computeStiffnessMatrix() const  {
    // compute stifness matrix
    return std::vector<std::vector<double>>(3, std::vector<double>(3, 0.0));
}

std::vector<std::vector<double>> TriElement::computeMassMatrix() const {
    return std::vector<std::vector<double>>(3, std::vector<double>(3, 1.0));
}

std::vector<double> TriElement::computeStrain(const std::vector<double>& displacements) const {
    return std::vector<double>(3, 0.0);
}

std::vector<double> TriElement::computeStress(const std::vector<double>& displacements) const {
    return std::vector<double>(3, 0.0);
}

double TriElement::computeVolume() const {
    // compute triangle area
    if (nodes.size() != 3) {
        throw std::runtime_error("TRI3 element must have exactly 3 nodes.");
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