#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <ctime>
#include <cassert>


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
    // only for input:
    int n;

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



// todo
Ingrediant read_input(){
    Ingrediant tmp;
    return tmp;
}

List read_ingreds_txt(){}

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
std::vector<double> make_dist(int n_ingreds, bool randomness){
    std::vector<double> dist;
    double alpha = randomness*0.5*n_ingreds;
    for(int i = 0; i < n_ingreds; i++){
        dist.push_back(exp(-alpha*i/(n_ingreds-1)));
    }
    return dist;
}

List select_ingreds(List& ingrediants, Ingrediant& input){
    List drink;
    while(input.amount > 0){
        // call sort_ingreds
        List possible_ingreds = sort_ingreds(ingrediants, drink, input);
        // call make_dist
        std::vector<double> distribution = make_dist(possible_ingreds.size(), input.randomness);
        // compute distribution integral
        double integral = 0;
        for(auto i : distribution){integral += i; }
        // radnom generator -> choose ingrediant
        double rand_position = (double)rand()*integral/RAND_MAX;
        double sum_till_now;
        for(int i = 0; i < distribution.size(); i++){
            sum_till_now += distribution.at(i);
            if(rand_position < sum_till_now){
                drink.push_back(possible_ingreds.at(i));
                input.amount -= possible_ingreds.at(i).amount;
                break;
            }
        }
    }

    return drink;
}

std::string give_name(List drink){
    return "bob";
}

void print_drink(List drink){}





int main()
{
    // desired drink: colour, volume, alkohol
    Ingrediant input = read_input();
    List ingrediants; // read all ingrediants from extra file
    srand(time(0)); // start randomizer

    // random generator

    // create name


 


    return 0;
}