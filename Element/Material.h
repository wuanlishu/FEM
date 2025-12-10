#pragma once
#ifndef _MATERIAL_H
#define _MATERIAL_H
#include <string>
#include <stdexcept>

class Material
{
public:
    Material()
    :mId(1), mName("steel"), E(2.1E5), G(8.077E4), Rho(7.85E-9), Nu(0.3)
    {
        matValidCheck();
    }
    
    Material(int id, std::string name, double ym, double sm, double ps, double d)
    : mId(id), mName(name), E(ym), G(sm), Rho(d), Nu(ps)
    {
        matValidCheck();
    }

    static Material fromYoungAndPoisson(int id, double ym, double ps, std::string name = "MAT1", double d = 0.0){
        double shearMudulus = ym/(2.0*(1.0 + ps));
        return Material(id, name, ym, shearMudulus, ps, d);
    }

    static Material fromShearAndPoisson(int id, double sm, double ps, std::string name = "MAT1", double d = 0.0){
        double yangsModulus = 2.0 * sm * (1.0 + ps);
        return Material(id, name, yangsModulus, sm, ps, d);
    }

    static Material fromYoungAndShear(int id, double ym, double sm, std::string name = "MAT1", double d = 0.0){
        double poissonRatio = ym / (2.0 * sm) - 1.0;
        return Material(id, name, ym, sm, poissonRatio, d);
    }
private:
    void matValidCheck() const;
public:
    int getId() const { return mId; }
    void setId(int id) { mId = id; };

    std::string getName() const { return mName; }
    void setName(const std::string& name) { mName = name; }

    double getYoungsModulus() const { return E; }
    // void setYoungsModulus(double ym);

    double getShearModulus() const { return G; }
    // void setShearModulus(double sm);

    double getPoissonRatio() const { return Nu; }
    // void setPoissonRatio(double ps);

    double getDensity() const { return Rho; }
    void setDensity(double r) { Rho = r; }

    int mId;
    std::string mName;
    double E; // Young's Modulus, Pa
    double G; // Shear Modulus, Pa
    double Rho; // Mass density, g/mm3
    double Nu; // Poisson's ratio
};

#endif