#pragma once
#ifndef _FEANALYSIS_H
#define _FEANALYSIS_H
// FEAnalysis.h
#include <vector>
#include "Element/Element.h"
#include <Eigen/Sparse>

class FEAnalysis {
public:
    FEAnalysis(const Element& mesh);

    void setup();
    void solve();

    const Eigen::VectorXd& getDisplacements() const { return displacements; }
    const std::vector<Eigen::VectorXd>& getStresses() const { return stresses; }
    const std::vector<Eigen::VectorXd>& getStrains() const { return strains; }

private:
    void assembleGlobalStiffnessMatrix();
    void applyBoundaryConditions();
    void solveLinearSystem();
    void computeStressesAndStrains();

    const Element& mesh;
    Eigen::SparseMatrix<double> globalStiffness;
    Eigen::VectorXd displacements;
    Eigen::VectorXd forces;
    std::vector<Eigen::VectorXd> stresses;
    std::vector<Eigen::VectorXd> strains;
};

#endif