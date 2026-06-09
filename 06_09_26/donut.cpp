#include "donut.h"

const std::map<icingType, std::string> Donut::iceToStr = {{CHOCOLATEICING, "Chocolate"},
                                                          {CARAMELICING, "Caramel"},
                                                          {MAPLE, "Maple"},
                                                          {VANILLA, "Vanilla"},
                                                          {GLAZE, "Glaze"},
                                                          {SPECIALICE, "Special"},
                                                          {NOICE, "None"}};
const std::map<std::string, icingType> Donut::strToice = {{"chocolate", CHOCOLATEICING},
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
const std::map<drizzleType, std::string> Donut::drizzleToStr =
    {{drizzleType::CARAMELDRIZZLE, "Caramel"},
     {drizzleType::CHOCOLATEDRIZZLE, "Chocolate"},
     {drizzleType::PEANUTBUTTER, "Peanut Butter"},
     {drizzleType::RASPBERRY, "Raspberry"},
     {drizzleType::SPECIALDRIZZLE, "Special"},
     {drizzleType::NODRIZZLE, "None"}};

const std::map<std::string, drizzleType> Donut::strToDrizzle =
    {{"caramel", drizzleType::CARAMELDRIZZLE},
     {"chocolate", drizzleType::CHOCOLATEDRIZZLE},
     {"peanut butter", drizzleType::PEANUTBUTTER},
     {"raspberry", drizzleType::RASPBERRY},
     {"special", drizzleType::SPECIALDRIZZLE},
     {"none", drizzleType::NODRIZZLE}};