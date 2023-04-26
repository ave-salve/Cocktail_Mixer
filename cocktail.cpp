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
    std::string name;
    double alk; // prozent alkohol
    double amount;
    double cost_permax; // in CHF

    double sweet;
    double sour;
    double bitter;

    double co2;
    double viscosity;
    double randomness;
    // colour

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

List read_ingreds_txt(){
    std::ifstream stream_ingr;
    stream_ingr.open("ingredients.txt");
    assert(stream_ingr.is_open());
    std::string skip;
    while(stream_ingr >> skip && !(skip == "#"));

    List ingrediants;
    

    std::string tmp;
    while(stream_ingr >> tmp){
        Ingrediant new_one;
        new_one.name = tmp;
        stream_ingr >> new_one.alk;
        stream_ingr >> new_one.amount;
        stream_ingr >> new_one.cost_permax;

        stream_ingr >> new_one.sweet;
        stream_ingr >> new_one.sour;
        stream_ingr >> new_one.bitter;
        
        stream_ingr >> new_one.co2;
        stream_ingr >> new_one.viscosity;
        stream_ingr >> new_one.randomness;

        ingrediants.push_back(new_one);
        std::cout << new_one.name << std::endl;
    }

    return ingrediants;
}

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
    double evaluation = 0;
    double eval = 0;
    for(Ingrediant i: ingrediants){
        eval += pow(average.alk*average.amount/(average.amount + i.amount) + i.alk*i.amount/(average.amount + i.amount) - input.alk,2);
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
    read_ingreds_txt();

    // desired drink: colour, volume, alkohol
    Ingrediant input = read_input();
    List ingrediants; // read all ingrediants from extra file
    srand(time(0)); // start randomizer

    return 0;
}