#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>


struct Ingrediant
{
public:
    // default: value between 0, 1

    double alk; // prozent alkohol
    double sweet;
    double bitter;
    double sour;
    double viscosity;
    double amount; 
    bool co2; // 0 oder 1
    double cost_permax; // in CHF
    // colour
    double randomness;

    Ingrediant();
    ~Ingrediant();
};
Ingrediant::Ingrediant(/* args */)
{
}
Ingrediant::~Ingrediant()
{
}

using List = std::vector<Ingrediant>;



Ingrediant read_input(){}

//returns a Vector of possible ingrediants to add to the drink. Sorted from most to least fitting
List sort_ingreds(List& ingrediants, List& drink, Ingrediant& input)
{
    Ingrediant Drink;
    for(Ingrediant i: drink){
        Drink.alk += i.alk/drink.size();
        Drink.sweet += i.sweet/drink.size();
        Drink.bitter += i.bitter/drink.size();
        Drink.sour += i.sour/drink.size();
        Drink.viscosity += i.viscosity/drink.size();
        Drink.co2 += i.co2/drink.size();
        Drink.cost_permax += i.bitter/drink.size();
    }
    
}

// post: vector of probabilities (e^{-ax_i})
std::vector<double> make_dist(int n_ingreds, int randomness){
    // see notizblatt
}

List select_ingreds(List& ingrediants, Ingrediant& input){
    while(input.max_amount_cL > 0){
        // call sort_ingreds
        // call make_dist
        // radnom generator -> choose ingrediant
        // subtract volume




    }
}

std::string give_name(List drink){
    return "bob";
}

void print_drink(List drink){}





int main()
{
    // desired drink: colour, volume, alkohol
    Ingrediant input = read_input();

    // random generator

    // create name

    return 0;
}