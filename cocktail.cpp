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
    double max_amount_cL; // in cL, 0 heisst unlimitiert
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


// randomness als reference
Ingrediant read_input(){
    Ingrediant tmp;
    return tmp;
}

List read_ingreds_txt(){}

//returns a Vector of possible ingrediants to add to the drink. Sorted from most to least fitting
List sort_ingreds(List& ingrediants, List& drink, Ingrediant& input)
{
    // Sam does his magic
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

    srand(1);
    std::cout << rand() << rand() << rand() << rand() << rand() << rand() << std::endl;

    srand(1);
    std::cout << rand() << rand() << rand() << rand() << rand() << rand();

    return 0;
}