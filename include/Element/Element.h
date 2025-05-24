#pragma once
#ifndef _ELEMENT_H
#define _ELEMENT_H

#include <map>
#include <vector>
#include <string>
#include <memory>
#include "Node.h"
#include "Material.h"
#include <Eigen/Dense>

class Element {
public:
    enum class ElementType {
        TRI3,
        QUAD4,
        TET4,
        HEX8
    };
    Element(int id, ElementType typ, const std::vector<std::shared_ptr<Node>>& nds,
    std::shared_ptr<Material> mat)
    : eId(id), type(typ), nodes(nds), materials(mat) {
        elmValidateCheck();
    }

    virtual ~Element() = default;

    int getId() const {return eId;}
    ElementType getType() const {return type;}
    size_t getNodesNum() const {return nodes.size();}
    const std::vector<std::shared_ptr<Node>> getNodes() const {return nodes;}
    std::shared_ptr<Material> getMaterial() const {return materials;}
    void setMaterial(std::shared_ptr<Material> material) {materials = material;}

    virtual Eigen::MatrixXd computeStiffnessMatrix() const = 0;
    virtual Eigen::MatrixXd computeMassMatrix() const = 0;
    virtual std::vector<double> computeStrain(const std::vector<double>& displacements) const = 0;
    virtual std::vector<double> computeStress(const std::vector<double>& displacements) const = 0;
    
    virtual double computeVolume() const = 0;

    virtual void elmValidateCheck() const {
        if(nodes.empty()) {
            throw std::runtime_error("Element has no nodes.");
        }

        size_t required_nodes = 0;
        switch (type) {
            case ElementType::TRI3:
                required_nodes = 3;
                break;
            case ElementType::QUAD4:
                required_nodes = 4;
                break;
            case ElementType::TET4:
                required_nodes = 4;
                break;
            case ElementType::HEX8:
                required_nodes = 8;
                break;
        }

        if(nodes.size() != required_nodes){
            throw std::runtime_error("nodes number don't match required nodes.");
        }

        if(!materials) {
            throw std::runtime_error("Element has no material assigned");
        }
    }
protected:
    int eId;
    ElementType type;
    std::vector<std::shared_ptr<Node>> nodes;
    std::shared_ptr<Material> materials;
};

#endif