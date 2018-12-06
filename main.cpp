#include "tcmbpp.hpp"

int main()
{
    TCMB tcmb;
    TCMB tcmb2("20.1.2009");

    Currency dolar = tcmb.getCurrency("USD");
    Currency dolar2 = tcmb2.getCurrency("USD");
    Currency euro = tcmb.getCurrency("EUR");
    Currency euro2 = tcmb2.getCurrency("EUR");

    tcmb.printCurrency(dolar);
    tcmb2.printCurrency(dolar2);

    tcmb.printCurrency(euro);
    tcmb2.printCurrency(euro2);

    std::cout << "USD Forex Buying: " << dolar.ForexBuying
              << " USD Forex Selling: " << dolar.ForexSelling << '\n';

    std::cout << "20.1.2009 USD Forex Buying: " << dolar2.ForexBuying
              << " 20.1.2009 USD Forex Selling: " << dolar2.ForexSelling << '\n';

    std::cout << "The dollar value difference from 2009 to 2018: "
              << dolar.ForexBuying - dolar2.ForexBuying << '\n';

    std::cout << "EUR Forex Buying: " << euro.ForexBuying
              << " EUR Forex Selling " << euro.ForexSelling << '\n';

    std::cout << "20.1.2009 EUR Forex Buying: " << euro2.ForexBuying
              << " 20.1.2009 EUR Forex Selling " << euro2.ForexSelling << '\n';

    //for (const auto &i : tcmb.currencyList)
    //    tcmb.printCurrency(i);
}
