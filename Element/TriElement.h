#pragma once
#ifndef _TRI_ELEMENT_H
#define _TRI_ELEMENT_H

#include "Element.h"
#include <Eigen/Dense>

class TriElement : public Element {
public:
    TriElement(int triEid, const std::vector<std::shared_ptr<Node>>& nodes, std::shared_ptr<Material> mat, double thick = 1.0)
    : Element(triEid, ElementType::TRI3, nodes, mat), thickness(thick) {}

    ////////// override //////////// 
    Eigen::MatrixXd computeStiffnessMatrix() const override;
    Eigen::MatrixXd computeMassMatrix() const override;
    std::vector<double> computeStrain(const std::vector<double>& displacements) const override;
    std::vector<double> computeStress(const std::vector<double>& displacements) const override;
    double computeVolume() const override;

public:
    Eigen::Vector3d computeElasticMatrix() const; // [D]
    Eigen::Vector3d computeNormalVector() const;
    Eigen::Matrix3d computeLocalCoordSystem() const;
    Eigen::Matrix<double, 3, 6> computeStrainDisplacementMatrix() const; // [B]

private:
    double thickness;
};

#endif