#pragma once
#ifndef _NODE_H
#define _NODE_H
#include <vector>

class Node
{
public:
    Node() = default;
    Node(int nId, double x1, double y1, double z1)
    : id(nId), x(x1), y(y1), z(z1), fixed(false)
    {
        this->displacement.reserve(3);
        this->force.reserve(3);
    }
    Node(int nId, double x1, double y1, double z1, std::vector<double> disp1, std::vector<double> force1, bool fix = false)
    : id(nId), x(x1), y(y1), z(z1), displacement(disp1), force(force1), fixed(fix)
    {}
    ~Node(){}

    int getId() const { return this->id; }
    void setId(int nId) { this->id = nId; }

    int getX() const { return this->x; }
    void setX(double newX) { this->x = newX; }

    int getY() const { return this->y; }
    void setY(double newY) { this->y = newY; }

    int getZ() const { return this->z; }
    void setZ(double newZ) { this->z = newZ; }

    std::vector<double> getCoord() const { std::vector<double> coord = {this->x, this->y, this->z}; return coord;};
    bool setCoord(std::vector<double> newCoord);

    std::vector<double> getDisplacement() const { return this->displacement; }
    bool setDisplacement(std::vector<double> newDisp);

    std::vector<double> getForce() const { return this->force; }
    bool setForce(std::vector<double> newForce);

    bool isFixed() {return this->fixed;}
    void setFixed(bool isfixed) { this->fixed = isfixed; }

private:
    int id;
    double x;
    double y;
    double z;
    std::vector<double> displacement;
    std::vector<double> force;
    bool fixed;
};

#endif