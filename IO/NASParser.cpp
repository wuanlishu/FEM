#include "IO/NASParser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Mesh/MeshData.h"
MeshData NASParser::parse(const std::string& filePath) {
    std::ifstream file(filePath);
    if(!file.is_open()) {
        throw std::runtime_error("Can not open the file: " + filePath);
    }

    MeshData mesh;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) { continue; }

        std::string recordType = line.substr(0, 8);
        if (recordType == "GRID*   ") {
            parseGrid(file, mesh);
        } else if (recordType == "CQUAD4  ") {
            parseCQuad4(file, mesh);
        } else if (recordType == "CHEXA8  ") {
            parseCHexa8(file, mesh);
        } else if (recordType == "MAT1    ") {
            parseMat1(file, mesh);
        } else if (recordType == "SPC1    ") {
            parseSpc1(file, mesh);
        } else if (recordType == "FORCE   ") {
            parseLoad(file, mesh);
        } else {
            continue;
        }
    }

    return mesh;
}

void NASParser::parseGrid(std::ifstream& file, MeshData& mesh) {
    std::string line;

    std::getline(file, line);
    int node_id = std::stoi(line.substr(8, 16));
    double x_coord  = std::stod(line.substr(24,16));

    std::getline(file, line);
    double y_coord  = std::stod(line.substr(8, 16));
    double z_coord  = std::stod(line.substr(24,16));

    Node node(node_id, x_coord, y_coord, z_coord);
    mesh.addNode(node);
}

void NASParser::parseCQuad4(std::ifstream& file, MeshData& mesh) {
    std::string line;

    std::getline(file, line);
    int element_id = std::stoi(line.substr(8, 16));
    int node_id_1 = std::stoi(line.substr(24, 16));

}

void NASParser::parseCHexa8(std::ifstream& file, MeshData& mesh) {
    std::string line;

}

