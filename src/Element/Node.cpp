#include "Node.h"
#include <iostream>

bool Node::setCoord(std::vector<double> newCoord)
{
    if (newCoord.size() != 3)
    {
        std::cout << "new coordinate error." << std::endl;
        return false;
    }

    this->x = newCoord[0];
    this->y = newCoord[1];
    this->z = newCoord[2];
    return true;
}

bool Node::setDisplacement(std::vector<double> newDisp)
{
    if (newDisp.size() != 3)
    {
        std::cout << "new displacement error." << std::endl;
        return false;
    }

    this->displacement.assign(newDisp.begin(), newDisp.end());
    return true;
}

bool Node::setForce(std::vector<double> newForce)
{
    if (newForce.size() != 3)
    {
        std::cout << "new force error." << std::endl;
        return false;
    }

    this->force.assign(newForce.begin(), newForce.end());
    return true;
}