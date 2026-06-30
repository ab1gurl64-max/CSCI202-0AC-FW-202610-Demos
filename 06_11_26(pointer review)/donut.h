#ifndef DONUT_H
#define DONUT_H
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>

// Module 1 a lab activity implement all of the getters and setters for the donut class.
// You can use the maps to help you

class Donut
{
public:
    enum icingType
    {
        CHOCOLATEICING,
        CARAMELICING,
        MAPLE,
        VANILLA,
        GLAZE,
        SPECIALICE,
        NOICE
    };

    enum drizzleType
    {
        CARAMELDRIZZLE,
        CHOCOLATEDRIZZLE,
        PEANUTBUTTER,
        RASPBERRY,
        SPECIALDRIZZLE,
        NODRIZZLE
    };
    enum toppingType
    {
        RAINBOWSPR,
        CHOCOLATESPR,
        PEANUTS,
        COCONUT,
        OREO,
        BACON,
        GRAHAM,
        FRUITYPEBBLES,
        REESESPIECES,
        MMS,
        CANDYBAR,
        CHOCOLATECHIPS,
        SEASALT,
        CINSUGAR,
        POWDSUGAR,
        NOTOP
    };
    Donut(std::string icing = "none", std::string topping = "none", std::string drizzle = "none");
    icingType getIcing() const;
    toppingType getTopping() const;
    drizzleType getDrizzle() const;
    void setIcing(std::string icing);
    void setTopping(std::string topping);
    void setDrizzle(std::string drizzle);
    std::string toString() const;
    friend std::ostream &operator<<(std::ostream &, const Donut &);
    const static std::map<icingType, std::string> iceToStr;
    const static std::map<std::string, icingType> strToice;
    const static std::map<drizzleType, std::string> drizzleToStr;
    const static std::map<std::string, drizzleType> strToDrizzle;
    const static std::map<toppingType, std::string> topToStr;
    const static std::map<std::string, toppingType> strToTop;

private:
    icingType icing;
    toppingType topping;
    drizzleType drizzle;
};

#endif