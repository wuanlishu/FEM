#pragma once
#ifndef _ELEMENTDATA_H
#define _ELEMENTDATA_H

#include <map>
#include <vector>
#include <string>

struct Node {
    int id;
    double x, y, z;
    bool isConstrained[6];
};

struct Element {
    int id;
    std::string type;
    std::vector<int> nodeIds;
    int materialId;
    int propertyId;
};

struct Material {
    int id;
    double youngsModulus;
    double poissonsRatio;
    double density;
};

class MeshData {
public:
    void addNode(const Node& node) { nodes.push_back(node); }
    void addElement(const Element& element) { elements.push_back(element); }
    void addMaterial(const Material& material) { materials[material.id] = material;}
    
    const std::vector<Node>& getNodes() const { return nodes; }
    const std::vector<Element>& getElements() const { return elements; }
    const Material& getMaterials(int id) const { return materials.at(id); }
    
private:
    std::vector<Node> nodes;
    std::vector<Element> elements;
    std::map<int, Material> materials;
};

#endif