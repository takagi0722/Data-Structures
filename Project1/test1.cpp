#include <iostream>
#include <cmath>

enum signType { plus, minus };

class currency
{
public:
    currency(signType theSign = plus, unsigned long theDollars = 0, unsigned int theCents = 0)
        : sign(theSign), dollars(theDollars), cents(theCents) {}


    ~currency() {}

    void setValue(signType theSign, unsigned long theDollars, unsigned int theCents)
    {
        sign = theSign;
        dollars = theDollars;
        cents = theCents;
    }

    void setValue(double amount)
    {
        sign = (amount < 0) ? minus : plus;
        amount = std::fabs(amount);
        dollars = static_cast<unsigned long>(amount);
        cents = static_cast<unsigned int>((amount - dollars) * 100);
    }

    signType getSign() const { return sign; }
    unsigned long getDollars() const { return dollars; }
    unsigned int getCents() const { return cents; }

    currency add(const currency& other) const
    {
        double total1 = this->dollars + this->cents / 100.0;
        double total2 = other.dollars + other.cents / 100.0;
        double result = total1 + total2;
        return currency(plus, static_cast<unsigned long>(result), static_cast<unsigned int>((result - static_cast<unsigned long>(result)) * 100));
    }

    currency& increment(const currency& other)
    {
        *this = this->add(other);
        return *this;
    }

    void output() const
    {
        std::string signStr = (sign == plus) ? "+" : "-";
        std::cout << signStr << dollars << "." << (cents < 10 ? "0" : "") << cents << std::endl;
    }

    void input()
    {
        double amount;
        std::cout << "Enter the currency value: ";
        std::cin >> amount;
        setValue(amount);
    }

    currency subtract(const currency& other) const
    {
        double total1 = this->dollars + this->cents / 100.0;
        double total2 = other.dollars + other.cents / 100.0;
        double result = total1 - total2;
        return currency((result < 0 ? minus : plus), static_cast<unsigned long>(std::fabs(result)), static_cast<unsigned int>((std::fabs(result) - static_cast<unsigned long>(std::fabs(result))) * 100));
    }


    currency percent(double x) const
    {
        double total = dollars + cents / 100.0;
        double result = total * (x / 100.0);
        return currency(plus, static_cast<unsigned long>(result), static_cast<unsigned int>((result - static_cast<unsigned long>(result)) * 100));
    }

    currency multiply(double x) const
    {
        double total = dollars + cents / 100.0;
        double result = total * x;
        return currency(plus, static_cast<unsigned long>(result), static_cast<unsigned int>((result - static_cast<unsigned long>(result)) * 100));
    }

    currency divide(double x) const
    {
        double total = dollars + cents / 100.0;
        double result = total / x;
        return currency(plus, static_cast<unsigned long>(result), static_cast<unsigned int>((result - static_cast<unsigned long>(result)) * 100));
    }

private:
    signType sign;              
    unsigned long dollars;       
    unsigned int cents;          
};

int main()
{
    currency c1(plus, 10, 50);
    currency c2(minus, 5, 75);

    std::cout << "Currency 1: ";
    c1.output();

    std::cout << "Currency 2: ";
    c2.output();

    currency result = c1.subtract(c2);
    std::cout << "Result of subtraction: ";
    result.output();

    currency percentResult = c1.percent(50);
    std::cout << "50% of Currency 1: ";
    percentResult.output();

    currency multiplyResult = c1.multiply(2.5);
    std::cout << "Currency 1 multiplied by 2.5: ";
    multiplyResult.output();

    currency divideResult = c1.divide(2);
    std::cout << "Currency 1 divided by 2: ";
    divideResult.output();

    return 0;
}
