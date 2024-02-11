#include<iostream> // Include the IO stream library for console input and output
#include<vector>   // Include the vector library to use the vector container

// Declare an abstract class named Ingredient
class Ingredient {
   public:
       virtual std::string name() = 0; // Pure virtual function for the name
       virtual int calories() = 0;     // Pure virtual function for calories
       virtual int cost() = 0;         // Pure virtual function for cost
};

// Declare a class named Bread that inherits from Ingredient
class Bread : public Ingredient {
   public:
       // Pure virtual functions that will be overridden by derived classes
       virtual std::string name() = 0;
       virtual int calories() = 0;
       virtual int cost() = 0;
};

// Declare a class named Bagel that inherits from Bread
class Bagel: public Bread {
   public:
       // Override functions from the Bread class to return Bagel-specific details
       std::string name() override {
           return "Bagel";
       }
       int calories() override {
           return 250;
       }
       int cost() override {
           return 20;
       }
};

// Declare a class named Bun that inherits from Bread
class Bun: public Bread {
   public:
       // Override functions from the Bread class to return Bun-specific details
       std::string name() override {
           return "Bun";
       }
       int calories() override {
           return 170;
       }
       int cost() override {
           return 30;
       }
};

// Declare a class named Filling that inherits from Ingredient
class Filling : public Ingredient {
   public:
       // Pure virtual functions that will be overridden by derived classes
       virtual std::string name() = 0;
       virtual int calories() = 0;
       virtual int cost() = 0;
};

// Declare a class named CreamCheese that inherits from Filling
class CreamCheese: public Filling {
   public:
       // Override functions from the Filling class to return CreamCheese-specific details
       std::string name() override {
           return "CreamCheese";
       }
       int calories() override {
           return 340;
       }
       int cost() override {
           return 120;
       }
};

// Declare a class named Salmon that inherits from Filling
class Salmon: public Filling {
   public:
       // Override functions from the Filling class to return Salmon-specific details
       std::string name() override {
           return "Salmon";
       }
       int calories() override {
           return 150;
       }
       int cost() override {
           return 80;
       }
};

// Declare a class named Sandwich
class Sandwich {
   private:
       // Vector to store pointers to Ingredient objects
       std::vector<Ingredient*> ingredients;

   public:
   // Function to add ingredients to the sandwich
   void addIngredients(Ingredient* i)  {
       ingredients.emplace_back(i);
   }
   // Function to display all ingredients in the sandwich with their details
   void getSandwich() {
       for(Ingredient* i:ingredients) {
           std::cout<<i->name()<<" : "<<i->calories()<<" kcal"<<" Cost: "<<i->cost()<<std::endl;
       }
   }
   // Function to calculate and display the total calories of the sandwich
   void getCalories() {
       int totCalories = 0;
       for(Ingredient* i:ingredients) {
           totCalories+=i->calories();
       }
       std::cout<<"Total calories: "<<totCalories<<std::endl;
   }
};

// Declare a class named Sandwich_Builder
class Sandwich_Builder {
   public:
   // Function to create a pre-defined sandwich
   static Sandwich readyMade() {
       Sandwich s;
       s.addIngredients(new Bagel());
       s.addIngredients(new Salmon());
       s.addIngredients(new CreamCheese());
       return s;
   }
   // Function to add an ingredient to a sandwich and return it
   static Sandwich build(Sandwich &s, Ingredient* i) {
       s.addIngredients(i);
       return s;
   }
};


int main() {
   // Main function starting point
   std::cout<<"Sandwich Builder"<<std::endl;
   Sandwich custom; 
   // Build a custom sandwich
   Sandwich_Builder::build(custom,new Bun());
   Sandwich_Builder::build(custom,new Salmon());
   std::cout<<"Customised Sandwich"<<std::endl;
   custom.getSandwich();
   custom.getCalories();

   // Create a ready-made sandwich
   Sandwich offTheShelf = Sandwich_Builder::readyMade(); 
   std::cout<<"ReadyMade Sandwich: "<<std::endl;
   offTheShelf.getSandwich();
   offTheShelf.getCalories();

   return 0;   
}