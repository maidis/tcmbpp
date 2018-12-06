#include "tcmbpp.hpp"

int main()
{
    TCMB tcmb;
    tcmb.printCurrency(tcmb.getCurrency("USD"));

    Currency dolar = tcmb.getCurrency("USD");
    std::cout << "Dolar alış: " << dolar.ForexBuying
              << " dolar satış " << dolar.ForexSelling << '\n';

    tcmb.printCurrency(tcmb.getCurrency("EUR"));
    Currency euro = tcmb.getCurrency("EUR");
    std::cout << "Euro alış: " << euro.ForexBuying
              << " euro satış " << euro.ForexSelling << '\n';

    TCMB tcmb2("20.1.2009");
    tcmb2.printCurrency(tcmb2.getCurrency("USD"));

    Currency dolar2 = tcmb2.getCurrency("USD");
    std::cout << "Dolar alış: " << dolar2.ForexBuying
              << " dolar satış " << dolar2.ForexSelling << '\n';

    tcmb2.printCurrency(tcmb2.getCurrency("EUR"));
    Currency euro2 = tcmb2.getCurrency("EUR");
    std::cout << "Euro alış: " << euro2.ForexBuying
              << " euro satış " << euro2.ForexSelling << '\n';

    /*for (const auto &i : tcmb.currencyList)
    {
        std::cout << i.CurrencyCode << '\t'
                  << i.Unit << '\t'
                  << i.CurrencyNameTR << '\t'
                  << i.ForexBuying << '\t'
                  << i.ForexSelling << '\t'
                  << i.CrossRateUSD << '\t'
                  << i.CrossRateOther << '\n';
    }*/

    std::cout << "2009'dan 2018'e dolar farki: "
              << dolar.ForexBuying - dolar2.ForexBuying << '\n';
}
