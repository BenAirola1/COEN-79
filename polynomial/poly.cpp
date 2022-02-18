// BENJAMIN AIROLA
// COEN 79
// PROFESSOR Behnam Dezfouli
// IMPLEMENTATION FOR POLYNOMIAL CLASS

#include "poly.h"
#include <cassert>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

namespace coen79_lab4 {
    // CONSTRUCTOR FOR CLASS POLYNOMIAL
    polynomial::polynomial(double c, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        for(int i = 0; i <= MAXIMUM_DEGREE; i++) {
            data[i] = 0.0;
        }
        data[exponent] = c;
    }

    // ASSIGNS COEFFICIENT TO EXPONENT
    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        data[exponent] = coefficient;
    }

    // ADDS DOUBLE AMOUNT TO COEFFICIENT OF DEGREE EXPONENT
    void polynomial::add_to_coef(double amount, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        data[exponent] += amount;
    }

    // CLEARS ALL COEFFICIENTS OF POLYNOMIAL
    void polynomial::clear() {
        for(int i = 0; i <= MAXIMUM_DEGREE; i++) {
            data[i] = 0.0;
        }
    }

    // RETURNS THE ANTI-DERIVATIVE OF POLYNOMIAL
    polynomial polynomial::antiderivative( ) const {
        assert(degree() < MAXIMUM_DEGREE);
        polynomial temp;
        for(int i = 0; i < MAXIMUM_DEGREE; i++) {
            temp.data[i+1] = (data[i]/(i+1));
        }
        return temp;
    }

    // RETURNS COEFFICIENT AT SPECIFIED EXPONENT OF POLYNOMIAL
    double polynomial::coefficient(unsigned int exponent) const {
        if(exponent > MAXIMUM_DEGREE)
            return 0;
        return data[exponent];
    }

    // RETURNS VALUE OF DEFINITE INTEGRAL COMPUTED FROM x0 to x1
    double polynomial::definite_integral(double x0, double x1) const {
        polynomial temp = antiderivative();
        return (temp.eval(x1) - temp.eval(x0));
    }

    // RETURNS THE HIGHEST DEGREE EXPONENT IN POLYNOMIAL
    unsigned int polynomial::degree() const {
        for(int i = MAXIMUM_DEGREE; i >= 0; i--) {
            if(data[i] != 0)
                return i;
        }
        return 0;
    }

    // RETURNS THE DERIVATIVE OF POLYNOMIAL
    polynomial polynomial::derivative() const {
        polynomial temp;
        for(int i = 1; i < MAXIMUM_DEGREE; i++) {
            temp.data[i-1] = (data[i] * i);
        }
        return temp;
    }

    // RETURNS THE VALUE OF THE POLYNOMIAL EVALUATED AT X
    double polynomial::eval(double x) const {
        double sum = 0.0;
        for(int i = 0; i <= MAXIMUM_DEGREE; i++) {
            sum += data[i] * pow(x, i);
        }
        return sum;
    }

    // RETURNS TRUE IF POLYNOMIAL HAS NO COEFFICIENTS
    bool polynomial::is_zero( ) const {
        for(int i = 0; i <= MAXIMUM_DEGREE; i++) {
            if(data[i] != 0)
                return false;
        }
        return true;
    }

    // RETURNS NEXT EXPONENT LARGER THAN "e"
    unsigned int polynomial::next_term(unsigned int e) const {
        for(int i = e+1; i <= MAXIMUM_DEGREE; i++) {
            if(data[i] != 0)
                return i;
        }
        return 0;
    }

    // RETURNS NEXT EXPONENT SMALLER THAN "e"
    unsigned int polynomial::previous_term(unsigned int e) const {
        for(int i = e-1; i >= 0; i--) {
            if(data[i] != 0)
                return i;
        }
        return UINT_MAX;
    }

    // OVERLOADED OPERATOR -- SAME AS EVAL
    double polynomial::operator() (double x) const {
        return eval(x);
    }

    // RETURNS POLYNOMIAL WITH COEFFICIENTS BEING THE SUM OF "p1" AND "p2"
    polynomial operator +(const polynomial& p1, const polynomial& p2) {
        polynomial temp;
        for(int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++) {
            temp.assign_coef(p1.coefficient(i) + p2.coefficient(i), i);
        }
        return temp;
    }

    // RETURNS POLYNOMIAL WITH COEFFICIENTS BEING THE DIFFERENCE OF "p1" AND "p2"
    polynomial operator -(const polynomial& p1, const polynomial& p2) {
        polynomial temp;
        for(int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++) {
            temp.assign_coef(p1.coefficient(i) - p2.coefficient(i), i);
        }
        return temp;
    }

    // RETURNS POLYNOMIAL PRODUCT OF "p1" AND "p2"
    polynomial operator *(const polynomial& p1, const polynomial& p2) {
        assert(p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);
        polynomial temp;
        for(int i = 0; i <= p1.degree(); i++)
            for(int j = 0; j <= p2.degree(); j++)
                temp.add_to_coef(p1.coefficient(i)*p2.coefficient(j), i+j);
        return temp;
    }

    // PRINTS POLYNOMIAL TO OSTREAM OUT
    ostream& operator << (ostream& out, const polynomial& p) {
        unsigned int i = p.degree();
        streamsize s = out.precision();
        out << fixed;
        out << setprecision(1);
        for(int i = p.degree(); i >= 0; i--) {              
            if(p.degree() == 0) 
                out << p.coefficient(0);
            else if(p.coefficient(i) != 0) {        
                if(i == p.degree())                             
                    out << p.coefficient(i) << "x^" << i << ' ';   
                else if(i < p.degree() && i > 1) {   
                    if(p.coefficient(i) < 0)
                        out << "- ";                            
                    else    
                        out << "+ ";                            
                    out << fabs(p.coefficient(i)) << "x^" << i << ' ';   
                }
                else if(i == 1) {
                    if(p.coefficient(i) < 0)
                        out << "- ";                            
                    else
                        out << "+ ";                            
                    out << fabs(p.coefficient(i)) << "x ";             
                }
                else if(i == 0) {
                    if(p.coefficient(i) < 0)
                        out << "- ";                            
                    else
                        out << "+ ";                            
                    out << fabs(p.coefficient(i));                    
                }
            }
        }
        out.unsetf(ios_base::floatfield);
        out << setprecision(s);
        return out;
    }



    // PRINTS POLYNOMIAL TO OSTREAM OUT
    // THIS IS A COMPLETE MESS: ALL THE MATH TURNS OUT CORRECT, BUT THE PRINTING
    // IS OFF CONSIDERABLY
    ostream& operator << (ostream& out, const polynomial& p) {
        unsigned int i = p.degree();
        streamsize s = out.precision();
        out << fixed;
        out << setprecision(1);
        for(int i = p.degree(); i >= 0; i--) {              
            if(p.degree() == 0) 
                out << p.coefficient(0);
            else if(p.coefficient(i) != 0) {     
                    if(i == p.degree()) {}                          
                        if(p.degree() == 1)
                            out << p.coefficient(i) << "x";   
                        else
                            out << p.coefficient(i) << "x^" << i << ' ';
                    }
                    else if(i < p.degree() && i > 1) {   
                        if(p.coefficient(i) < 0)
                            out << "- ";                            
                        else    
                            out << "+ ";                            
                        out << fabs(p.coefficient(i)) << "x^" << i << ' ';   
                    }
                    else if(i == 1) {
                        if(p.coefficient(i) < 0)
                            out << "- ";                            
                        else
                            out << "+ ";                            
                        out << fabs(p.coefficient(i)) << "x ";             
                    }
                    else if(i == 0) {
                        if(p.coefficient(i) < 0)
                            out << "- ";                            
                        else
                            out << "+ ";                            
                        out << fabs(p.coefficient(i));                    
                    }
                }
            }
        }
        out.unsetf(ios_base::floatfield);
        out << setprecision(s);
        return out;
    }
}
