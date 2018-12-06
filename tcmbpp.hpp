#ifndef TCMBPP_HPP
#define TCMBPP_HPP

#include <iostream>
#include <vector>
#include <algorithm>

#include <cpr/cpr.h>
#include <tinyxml2.h>

struct Currency
{
    std::string CurrencyCode;
    int Unit;
    std::string CurrencyNameTR, CurrencyNameEN;
    double ForexBuying, ForexSelling, BanknoteBuying, BanknoteSelling;
    double CrossRateUSD, CrossRateOther;
};

class TCMB
{
private:

public:
    // https://stackoverflow.com/questions/29435870/read-an-xml-file-using-tinyxml2-in-c
    // https://kokkachiprogramming.wordpress.com/2012/11/23/using-tinyxml2-for-xml-parsing-in-c/
    // https://shilohjames.wordpress.com/2014/04/27/tinyxml2-tutorial/
    tinyxml2::XMLDocument xmlDoc;

    std::vector<Currency> currencyList;

    // https://www.tcmb.gov.tr/kurlar/201812/03122018.xml
    // https://www.tcmb.gov.tr/kurlar/today.xml
    std::string tcmbAddress = std::string("https://www.tcmb.gov.tr/kurlar/");

    TCMB(const char* date = "today.xml");

    Currency getCurrency(std::string currencyCode);

    void printCurrency(const Currency &currency);

    // https://stackoverflow.com/questions/21169419/whats-the-equivalent-of-nets-string-isnullorwhitespace-in-c
    bool isNullOrWhiteSpace( std::string const& str );

    // https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
    static inline void ltrim(std::string &s);

    static inline void rtrim(std::string &s);

    // https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
    std::vector<std::string> extractDate(const std::string &arg);
};
#endif // TCMBPP_HPP
