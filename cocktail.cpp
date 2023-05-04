#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <ctime>
#include <cassert>
//#include "pbPlots.hpp" //only for plotting
//#include "supportLib.hpp" //only for plotting

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

    Ingrediant(std::string na, double al, double am, double co, double sw, double so, double bi, double co2_, double vi, double ra, int n_);
    Ingrediant();

    void print();
    
};

Ingrediant::Ingrediant(std::string na, double al, double am, double co, double sw, double so, double bi, double co2_, double vi, double ra, int n_)
    : name(na), alk(al), amount(am), cost_permax(co), sweet(sw), sour(so), bitter(bi), co2(co2_), viscosity(vi), randomness(ra), n(n_)
{}

Ingrediant::Ingrediant()
    : name(""), alk(0), amount(0), cost_permax(0), sweet(0), sour(0), bitter(0), co2(0), viscosity(0), randomness(0), n(0)
{}

void Ingrediant::print(){
    std::cout << "---------------------------" << std::endl;
    std::cout << "Name:     " << name << std::endl;
    std::cout << "Alc:      " << alk << std::endl;
    std::cout << "Amount:   " << amount << std::endl;
    std::cout << "Cost:     " << cost_permax << std::endl;
    std::cout << "Sweet:    " << sweet << std::endl;
    std::cout << "Sour:     " << sour << std::endl;
    std::cout << "Bitter:   " << bitter << std::endl;
    std::cout << "Co2:      " << co2 << std::endl;
    std::cout << "Viscos:   " << viscosity << std::endl;
    std::cout << "Random:   " << randomness << std::endl;
    std::cout << "---------------------------" << std::endl;
} 


using List = std::vector<Ingrediant>;

/*    //Plotting Distribution
void draw_dist_plot(std::vector<double> x, std::string png_name){
	StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
    RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
    std::vector<double> y;
    for(int i = 0; i < x.size(); ++i){
        //y.push_back((double)i/(double)x.size());
        y.push_back(i);
    }
    DrawScatterPlot(imageReference, 600, 400, &y, &x, errorMessage);
    std::vector<double> *pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, png_name);
	DeleteImage(imageReference->image);
    FreeAllocations();
}
*/

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
    int number = 1;
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

        new_one.n = number;
        ingrediants.push_back(new_one);
        ++number;
        //std::cout << new_one.name << std::endl;
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

//checks if ingrediant I is already in list D
bool ingred_duplicate(Ingrediant I, List D){
    for(auto i : D){
        if(i.name == I.name){return true;}
    }
    return false;
}

//returns a Vector of possible ingrediants to add to the drink. Sorted from most to least fitting
List sort_ingreds(List& ingrediants, List& drink, Ingrediant& input)
{
    Ingrediant average;
    List sorted_ingreds;
    std::vector<double> sorting_values;
    
    for(Ingrediant i: ingrediants){
        double eval = 0;
        drink.push_back(i);
        average = average_drink(drink);
        drink.pop_back();

        eval += fabs(average.alk - i.alk);
        eval += fabs(average.sweet - i.sweet);
        eval += fabs(average.sour  - i.sour);
        eval += fabs(average.bitter - i.bitter);
        eval += fabs(average.co2 - i.co2);
        eval += fabs(average.viscosity - i.viscosity)/2.0;


        if(average.co2 > 40 && 60 > average.co2){eval += 2;}
         
        sorted_ingreds.push_back(i);
        sorting_values.push_back(eval);
    }

    //sorting
    int n = sorting_values.size();
    for(int i = 0; i < n; ++i){
        for(int j = i+1; j < n; ++j){
            if(sorting_values.at(i) > sorting_values.at(j)){
                std::swap(sorting_values.at(i),sorting_values.at(j));
                std::swap(sorted_ingreds.at(i),sorted_ingreds.at(j));
            }
        }
    }

    




    //draw_dist_plot(sorting_values, "sorted_values_plot.png"); //Plott distribution function
    return sorted_ingreds;
}

    


// post: vector of probabilities (e^{-ax_i})
std::vector<double> make_dist(int n_ingreds, double randomness){
    std::vector<double> dist;
    double alpha = randomness*0.5*n_ingreds;
    for(int i = 0; i < n_ingreds; i++){
        dist.push_back(exp(-(alpha*i/(n_ingreds-1))));
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
        //draw_dist_plot(distribution, "dist_plot.png"); //Plott distribution function
        // compute distribution integral
        double integral = 0;
        for(auto i : distribution){integral += i; }
        // radnom generator -> choose ingrediant
        double rand_position = (double)rand()*integral/RAND_MAX;
        double sum_till_now = 0;
        for(int i = 0; i < distribution.size(); i++){
            sum_till_now += distribution.at(i);
            if(rand_position < sum_till_now){
                if(ingred_duplicate(possible_ingreds.at(i), drink)){break;}
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
    //Read the list of ingrediants from the file
    List ingrediants = read_ingreds_txt();

    // desired drink: colour, volume, alkohol
    //Ingrediant input = read_input();
    Ingrediant input("Test_Drink", 0.15, 1, 0.0, 0.5, 0.0, 0.0, 0, 0.1, 0.4, 0);
    
    srand(time(0)); // start randomizer
    //srand(1); //non random testing
    List drink = select_ingreds(ingrediants,input);
    std::cout << "---------------------------" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "The Cocktail Ingrediants are:" << std::endl;
    std::cout << "---------------------------" << std::endl;
    for(auto i : drink){
        std::cout << std::setw(5) << i.amount*150 << " ml |" << i.name << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
    average_drink(drink).print();
    std::cout << "---------------------------" << std::endl;

    return 0;
}