#pragma once
#ifndef _NASPARSER_H
#define _NASPARSER_H

#include <iostream>
#include "MeshData.h"
#include <string>
// NASParser.h
class NASParser {
public:
    static MeshData parse(const std::string& filePath);

private:
    static void parseGrid(std::ifstream& file, MeshData& mesh);
    static void parseCQuad4(std::ifstream& file, MeshData& mesh);
    static void parseCHexa8(std::ifstream& file, MeshData& mesh);
    static void parseMat1(std::ifstream& file, MeshData& mesh);
    static void parseSpc1(std::ifstream& file, MeshData& mesh);
    static void parseLoad(std::ifstream& file, MeshData& mesh);

    static void processLine(const std::string& line, MeshData& mesh);
};

#endif