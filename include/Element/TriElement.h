#pragma once
#ifndef _TRI_ELEMENT_H
#define _TRI_ELEMENT_H

#include "Element.h"

class TriElement : public Element {
public:
    TriElement(int triEid, const std::vector<std::shared_ptr<Node>>& nodes, std::shared_ptr<Material> mat)
    : Element(triEid, ElementType::TRI3, nodes, mat) {}

    std::vector<std::vector<double>> computeStiffnessMatrix() const override;

    std::vector<std::vector<double>> computeMassMatrix() const override;

    std::vector<double> computeStrain(const std::vector<double>& displacements) const override;

    std::vector<double> computeStress(const std::vector<double>& displacements) const override;

    double computeVolume() const override;
};

#endif