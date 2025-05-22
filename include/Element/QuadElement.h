#ifndef _QUAD_ELEMENT_H
#define _QUAD_ELEMENT_H

#include "Element.h"

class QuadElement : public Element {
public:
    QuadElement(int quadEid, const std::vector<std::shared_ptr<Node>>& nodes, std::shared_ptr<Material> mat)
    : Element(quadEid, ElementType::QUAD4, nodes, mat) {}

    std::vector<std::vector<double>> computeStiffnessMatrix() const override;

    std::vector<std::vector<double>> computeMassMatrix() const override;

    std::vector<double> computeStrain(const std::vector<double>& displacements) const override;

    std::vector<double> computeStress(const std::vector<double>& displacements) const override;

    double computeVolume() const override;
};

#endif