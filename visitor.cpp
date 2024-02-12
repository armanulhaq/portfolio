
#include<iostream>
#include<vector>
#include<variant>

class House;
class StudentLoan;

//Auditor 
class Visitor {
   public: 
       // taking Visitable(Home/StudentLoan) in - dispatch 2: Visitable(House/StudentLoan) is dispatched to Auditor
       virtual double visit(House&) = 0;
       virtual double visit(StudentLoan&) = 0;
};

// You, Node
class Visitable {
   public: 
       // taking auditor in - dispatch 1: Auditor dispatched to Visitable
       virtual double accept(Visitor&) = 0;  
};

class House : public Visitable {
   private: 
       double val;
   public:
       House(double v) : val(v) {};

       double getVal() {   return val;     }

       double accept(Visitor& v) override {   
           return v.visit(*this);
       }
};

class StudentLoan : public Visitable {
   private: 
       double val;
   public:
       StudentLoan(double v) : val(v) {};

       double getAmount() {   return val;     }

       double accept(Visitor& v) override {   
           return v.visit(*this);
       }
};

class TaxVisitor : public Visitor {
   public:
       double visit(House& h) override {
           std::cout<<"Housing loan ----"<<std::endl;
           return h.getVal() * 0.1; 
       }

       double visit(StudentLoan& s) override {
           std::cout<<"Student loan ----"<<std::endl;
           return s.getAmount() * 0.05;
       }
};

int main() {
   // legacy
   std::vector<Visitable*> visitable;
   visitable.emplace_back(new House(500000));
   visitable.emplace_back(new StudentLoan(100000));

   TaxVisitor taxVisitor;
   double totTax = 0.0;

   for(auto asset : visitable) {
       totTax += asset->accept(taxVisitor);
   }
   std::cout<<"Total tax = "<<totTax<<std::endl<<std::endl;


   // mix of legacy and modern
   std::vector<std::variant<House,StudentLoan>> loans = { House{500000}, StudentLoan{100000}};
   TaxVisitor taxVisitor2;
   for(auto& loan : loans) {
                               // visitable                                                   visitor
       double tax = std::visit( [&taxVisitor2](auto&& s){  return s.accept(taxVisitor2);   }, loan );
       std::cout<<"Variant visit TaxVisitor: "<<tax<<std::endl;
   }


   // modern - no double dispatching 
   // variant and visit camr to break the visitor design pattern
   
   
   return 0;
}