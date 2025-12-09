#include "fem/FEAnalysis.h"
#include <iostream>

FEAnalysis::FEAnalysis(const MeshData& mesh) : mesh(mesh) {}

void FEAnalysis::setup() {
    int numDOFs = mesh.getNodes().size() * 6;
    globalStiffness.resize(numDOFs, numDOFs);
    displacements.resize(numDOFs);
    forces.resize(numDOFs);
    forces.setZero();

    // 组装全局刚度矩阵
    assembleGlobalStiffnessMatrix();
    // 边界条件
    applyBoundaryConditions();
}

void FEAnalysis::assembleGlobalStiffnessMatrix() {
    std::vector<Eigen::Triplet<double>> tripletList;

    for (const auto& element : mesh.getElements()) {
        const auto& material = mesh.getMaterials(element.materialId);
        
        if (element.type == "CQUAD4") {
            Eigen::Matrix<double, 8, 8> ke = Eigen::Matrix<double, 8, 8>::Identity();

            for (int i = 0; i < 4; ++i) {
                for ( int j = 0; j < 4; ++j) {
                    int nodeI = element.nodeIds[i];
                    int nodeJ = element.nodeIds[j];

                    // 每节点有两个自由度
                    for (int di = 0; di < 2; ++di) {
                        for (int dj = 0; dj < 2; ++dj) {
                            tripletList.emplace_back(
                                nodeI * 2 + di,
                                nodeJ * 2 + dj,
                                ke(i*2+di, j*2+dj)
                            );
                        }
                    }
                }
            }
        }
    }

    globalStiffness.setFromTriplets(tripletList.begin(), tripletList.end());
}

void FEAnalysis::solve() {
    solveLinearSystem();
    computeStressesAndStrains();
}

void FEAnalysis::solveLinearSystem() {
    Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
    solver.compute(globalStiffness);

    if(solver.info() != Eigen::Success) {
        throw std::runtime_error("Matrix sparse failed.");
    }

    displacements = solver.solve(forces);
}

void FEAnalysis::computeStressesAndStrains() {
    for (const auto& element : mesh.getElements()) {
        const auto& material = mesh.getMaterials(element.materialId);

        Eigen::VectorXd elementDisplacements;
        if ( element.type == "CQUAD4") {
            elementDisplacements.resize(8);
            for (int i = 0; i < 4; ++i) {
                int nodeId = element.nodeIds[i];
                elementDisplacements(2*i) = displacements(2*nodeId);
                elementDisplacements(2*i+1) = displacements(2*nodeId+1);
            }
        }

        // 计算应变 (简化示例)
        Eigen::VectorXd strain = Eigen::VectorXd::Zero(3); // εx, εy, γxy
        Eigen::VectorXd stress = Eigen::VectorXd::Zero(3); // σx, σy, τxy

        // 实际实现中需要使用B矩阵和D矩阵
        // strain = B * elementDisplacements
        // stress = D * strain

        strains.push_back(strain);
        stresses.push_back(stress);
    }
}