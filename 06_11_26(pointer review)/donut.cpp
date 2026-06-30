#include "donut.h"

const std::map<Donut::icingType, std::string> Donut::iceToStr = {{CHOCOLATEICING, "Chocolate"},
                                                                 {CARAMELICING, "Caramel"},
                                                                 {MAPLE, "Maple"},
                                                                 {VANILLA, "Vanilla"},
                                                                 {GLAZE, "Glaze"},
                                                                 {SPECIALICE, "Special"},
                                                                 {NOICE, "None"}};
const std::map<std::string, Donut::icingType> Donut::strToice = {{"chocolate", CHOCOLATEICING},
                                                                 {"caramel", CARAMELICING},
                                                                 {"maple", MAPLE},
                                                                 {"vanilla", VANILLA},
                                                                 {"glaze", GLAZE},
                                                                 {"special", SPECIALICE},
                                                                 {"none", NOICE}};
const std::map<Donut::toppingType, std::string> Donut::topToStr =
    {{RAINBOWSPR, "Rainbow Sprinkles"},
     {CHOCOLATESPR, "Chocolate Sprinkles"},
     {PEANUTS, "Peanuts"},
     {COCONUT, "Coconut"},
     {OREO, "Oreo"},
     {BACON, "Bacon"},
     {GRAHAM, "Graham"},
     {FRUITYPEBBLES, "Fruity Pebbles"},
     {REESESPIECES, "Reeses Pieces"},
     {MMS, "M&Ms"},
     {CANDYBAR, "Candy Bar"},
     {CHOCOLATECHIPS, "Chocolate Chips"},
     {SEASALT, "Sea Salt"},
     {CINSUGAR, "Cinnamon Sugar"},
     {POWDSUGAR, "Powdered Sugar"},
     {NOTOP, "None"}};

const std::map<std::string, Donut::toppingType> Donut::strToTop =
    {
        {"rainbow sprinkles", RAINBOWSPR},
        {"chocolate sprinkles", CHOCOLATESPR},
        {"peanuts", PEANUTS},
        {"coconut", COCONUT},
        {"oreo", OREO},
        {"bacon", BACON},
        {"graham", GRAHAM},
        {"fruity pebbles", FRUITYPEBBLES},
        {"reeses pieces", REESESPIECES},
        {"m&ms", MMS},
        {"candy bar", CANDYBAR},
        {"chocolate chips", CHOCOLATECHIPS},
        {"sea salt", SEASALT},
        {"cinnamon sugar", CINSUGAR},
        {"powdered sugar", POWDSUGAR},
        {"none", NOTOP}};
const std::map<Donut::drizzleType, std::string> Donut::drizzleToStr =
    {{drizzleType::CARAMELDRIZZLE, "Caramel"},
     {drizzleType::CHOCOLATEDRIZZLE, "Chocolate"},
     {drizzleType::PEANUTBUTTER, "Peanut Butter"},
     {drizzleType::RASPBERRY, "Raspberry"},
     {drizzleType::SPECIALDRIZZLE, "Special"},
     {drizzleType::NODRIZZLE, "None"}};

const std::map<std::string, Donut::drizzleType> Donut::strToDrizzle =
    {{"caramel", drizzleType::CARAMELDRIZZLE},
     {"chocolate", drizzleType::CHOCOLATEDRIZZLE},
     {"peanut butter", drizzleType::PEANUTBUTTER},
     {"raspberry", drizzleType::RASPBERRY},
     {"special", drizzleType::SPECIALDRIZZLE},
     {"none", drizzleType::NODRIZZLE}};

std::string toLower(std::string str)
{

    for (int i = 0; i < str.length(); i++)
    {
        str[i] = std::tolower(str[i]);
    }
    return str;
}

Donut::Donut(std::string icing, std::string topping, std::string drizzle)
{
    setIcing(icing);
    setTopping(topping);
    setDrizzle(drizzle);
}

void Donut::setIcing(std::string icing)
{
    this->icing = NOICE;
}

void Donut::setTopping(std::string topping)
{
    // std::string toppingcpy = topping;
    // std::transform(topping.begin(), topping.end(), toppingcpy.begin(), ::tolower);
    if (!strToTop.count(toLower(topping)))
    {
        throw std::invalid_argument(topping + " is not a valid topping");
    }
    this->topping = strToTop.at(toLower(topping));
}

void Donut::setDrizzle(std::string drizzle)
{
    this->drizzle = drizzleType::NODRIZZLE;
}

std::string Donut::toString() const
{
    std::string out;
    out = "Icing: " + iceToStr.at(icing) + " Topping: " + topToStr.at(topping) + " Drizzle: " + drizzleToStr.at(drizzle);
    return out;
}

std::ostream &operator<<(std::ostream &out, const Donut &d)
{
    out << d.toString();
    return out;
}
