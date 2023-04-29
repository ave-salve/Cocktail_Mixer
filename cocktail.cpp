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
    double co2; 
    double cost_permax; // in CHF
    double randomness;
    // colour

    std::string name;

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




Ingrediant read_input(){
    Ingrediant tmp;
    return tmp;
}

List read_ingreds_txt(){}

Ingrediant average_drink(List& drink){
    Ingrediant average;
    average.name = "average";
    for(Ingrediant i: drink){average.amount += i.amount;}
    for(Ingrediant i: drink){
        average.alk += i.alk*i.amount/average.amount;
        average.sweet += i.sweet*i.amount/average.amount;
        average.bitter += i.bitter*i.amount/average.amount;
        average.sour += i.sour*i.amount/average.amount;
        average.viscosity += i.viscosity*i.amount/average.amount;
        average.co2 += i.co2*i.amount/average.amount;
        average.cost_permax += i.cost_permax*i.amount/average.amount;
        average.randomness += i.randomness*i.amount/average.amount;
    }
    return average;
}

//returns a Vector of possible ingrediants to add to the drink. Sorted from most to least fitting
List sort_ingreds(List& ingrediants, List& drink, Ingrediant& input)
{
    Ingrediant average = average_drink(drink);
    List sorted_ingreds;
    std::vector<int> sorting_values;
    
    for(Ingrediant i: ingrediants){
        double eval = 0;
        eval += pow(average.alk*average.amount/(average.amount + i.amount) + i.alk*i.amount/(average.amount + i.amount) - input.alk,2);
        eval += pow(average.sweet*average.amount/(average.amount + i.amount) + i.sweet*i.amount/(average.amount + i.amount) - input.sweet,2);
        eval += pow(average.bitter*average.amount/(average.amount + i.amount) + i.bitter*i.amount/(average.amount + i.amount) - input.bitter,2);
        eval += pow(average.sour*average.amount/(average.amount + i.amount) + i.sour*i.amount/(average.amount + i.amount) - input.sour,2);
        eval += pow(average.viscosity*average.amount/(average.amount + i.amount) + i.viscosity*i.amount/(average.amount + i.amount) - input.viscosity,2);
        eval += pow(average.co2*average.amount/(average.amount + i.amount) + i.co2*i.amount/(average.amount + i.amount) - input.co2,2);
        eval += pow(average.randomness*average.amount/(average.amount + i.amount) + i.randomness*i.amount/(average.amount + i.amount) - input.randomness,2);
        sorted_ingreds.push_back(i);
        sorting_values.push_back(sqrt(eval));
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
    while(input.amount > 0){
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

    srand(1);
    std::cout << rand() << rand() << rand() << rand() << rand() << rand() << std::endl;

    srand(1);
    std::cout << rand() << rand() << rand() << rand() << rand() << rand();


    //test sam


    return 0;
}