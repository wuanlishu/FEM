#include "TriElement.h"

Eigen::MatrixXd TriElement::computeStiffnessMatrix() const  {
    // 1. compute stiffness matrix in loacl coord system
    Eigen::Matrix<double, 3, 6> B = computeStrainDisplacementMatrix();
    Eigen::Matrix3d D = computeElasticMatrix();
    double area = computeVolume();
    
    Eigen::Matrix<double, 6, 6> K_local = B.transpose() * D * B *thickness*area;
    
    // 2. compute coord transformmatrix
    Eigen::Matrix3d T = computeLocalCoordSystem();

    // 3. extend transform matrix to 9 * 9
    Eigen::Matrix<double, 9, 9> T_total = Eigen::Matrix<double, 9, 9>::Zero();
    for (int i = 0; i < 3; ++i){
        T_total.block<3,3>(3*i, 3*i) = T.transpose();
    }

    // 4. extend local stiffness to 9 * 9
    Eigen::Matrix<double, 9, 9> K_local_expanded = Eigen::Matrix<double, 9, 9>::Zero();
    K_local_expanded.block<6,6>(0,0) = K_local;

    // 5. transform to global coord system 
    return T_total * K_local_expanded * T_total.transpose();
}

Eigen::MatrixXd TriElement::computeMassMatrix() const {
    return Eigen::Matrix<double, 9,9>::Zero();
}

std::vector<double> TriElement::computeStrain(const std::vector<double>& displacements) const {
    return std::vector<double>(3, 0.0);
}

std::vector<double> TriElement::computeStress(const std::vector<double>& displacements) const {
    return std::vector<double>(3, 0.0);
}

// compute triangle area override
double TriElement::computeVolume() const {
    if (nodes.size() != 3) {
        throw std::runtime_error("TRI3 element must have exactly 3 nodes.");
    }

    Eigen::Vector3d normal = computeNormalVector();
    return 0.5 * normal.norm();
}

// compute strain-displacement matrix [B] : loacl coord system, 2D plate stress
Eigen::Matrix<double, 3, 6> TriElement::computeStrainDisplacementMatrix() const {
    const auto& n0 = nodes[0];
    const auto& n1 = nodes[1];
    const auto& n2 = nodes[2];

    double x0 = n0->getX(), y0 = n0->getY();
    double x1 = n1->getX(), y1 = n1->getY();
    double x2 = n2->getX(), y2 = n2->getY();

    double b1 = y1 - y2;
    double b2 = y2 - y0;
    double b3 = y0 - y1;

    double c1 = x2 - x1;
    double c2 = x0 - x2;
    double c3 = x1 - x0;

    double area = computeVolume();
    double factor = 1.0 / (2.0 * area);

    Eigen::Matrix<double, 3, 6> B;
    B << b1*factor, 0,         b2*factor, 0,         b3*factor, 0,
         0,         c1*factor, 0,         c2*factor, 0,         c3*factor,
         c1*factor, b1*factor, c2*factor, b2*factor, c3*factor, b3*factor;
    return B;
}

// compute elastic matrix [D] : plate stress
Eigen::Vector3d TriElement::computeElasticMatrix() const{
    double E = materials->getYoungsModulus();
    double nu = materials->getPoissonRatio();

    Eigen::Matrix3d D;
    double factor = E / (1 - nu*nu);
    D << factor,    factor*nu, 0,
         factor*nu, factor,    0,
         0,         0,         factor*(1-nu)/2;
    
    return D;
}

// compute triangle normal vector
Eigen::Vector3d TriElement::computeNormalVector() const {
    const auto& n0 = nodes[0];
    const auto& n1 = nodes[1];
    const auto& n2 = nodes[2];

    Eigen::Vector3d v1(n1->getX() - n0->getX(),
                       n1->getY() - n0->getY(),
                       n1->getZ() - n0->getZ());

    Eigen::Vector3d v2(n2->getX() - n0->getX(),
                       n2->getY() - n0->getY(),
                       n2->getZ() - n0->getZ());

    return v1.cross(v2).normalized();
}

Eigen::Matrix3d TriElement::computeLocalCoordSystem() const {
    Eigen::Vector3d normal = computeNormalVector();
    Eigen::Vector3d v1(nodes[1]->getX() - nodes[0]->getX(),
                       nodes[1]->getY() - nodes[0]->getY(),
                       nodes[1]->getZ() - nodes[0]->getZ());
    Eigen::Vector3d local_x = v1.normalized();
    Eigen::Vector3d local_y = normal.cross(local_x).normalized();

    Eigen::Matrix3d T;
    T.col(0) = local_x;
    T.col(1) = local_y;
    T.col(2) = normal;
    return T;
}