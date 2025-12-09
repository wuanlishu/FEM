#pragma once
#ifndef _MESHDATA_H
#define _MESHDATA_H

#include <vector>
#include <memory>
#include <string>
#include "Element/Node.h"
#include "Element/Element.h"
#include "Element/Material.h"
#include "IO/NASParser.h"

class MeshData
{
public:
    MeshData() = default;
    MeshData(const std::string& filePath)
    {
        *this = NASParser::parse(filePath);
    }
    void addNode(Node node)
    {
        nodes.push_back(std::make_shared<Node>(node));
    }

    void addElement(Element element)
    {
        elements.push_back(std::make_shared<Element>(element));
    }

    void addMaterial(Material mat)
    {
        material.push_back(std::make_shared<Material>(mat));
    }

    std::vector<std::shared_ptr<Node>> getNodes() const
    {
        return nodes;
    }

    std::vector<std::shared_ptr<Element>> getElements() const
    {
        return elements;
    }

    std::vector<std::shared_ptr<Material>> getMaterials() const
    {
        return material;
    }

private:
    std::vector<std::shared_ptr<Node>> nodes;
    std::vector<std::shared_ptr<Element>> elements;
    std::vector<std::shared_ptr<Material>> material;
};
#endif