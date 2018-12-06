#include "tcmbpp.hpp"

TCMB::TCMB(const char* date)
{
    std::string date2 = date;
    if (date != "today.xml")
    {
        std::vector<std::string> dateElement = extractDate(date);

        std::string month = dateElement[1];
        if (std::stoi(dateElement[1]) < 10)
            if(dateElement[1].at(0) != '0')
                month = '0' + dateElement[1];

        std::string day = dateElement[0];
        if (std::stoi(dateElement[0]) < 10)
            if(dateElement[0].at(0) != '0')
                day = '0' + dateElement[0];

        // https://stackoverflow.com/questions/41201696/how-to-append-const-char-to-a-const-char
        date2 = dateElement[2] + month + '/' + day + month + dateElement[2] + ".xml";
    }
    // https://stackoverflow.com/questions/4832357/whats-the-difference-between-text-xml-vs-application-xml-for-webservice-respons
    auto r = cpr::Get(cpr::Url{tcmbAddress + date2},
    cpr::Header{{"Content-Type", "text/xml"}},
    cpr::Header{{"User-Agent", "maidis"}});

    // https://stackoverflow.com/questions/2862892/can-tinyxml-load-xml-from-string-instead-of-file
    const char* hede = r.text.c_str();
    // std::cout << hede;
    xmlDoc.Parse(hede);
    //tinyxml2::XMLError eResult = xmlDoc.LoadFile(date);
    //if (eResult != tinyxml2::XML_SUCCESS)
    //    return false;

    tinyxml2::XMLNode* root = xmlDoc.FirstChildElement("Tarih_Date");
    //if (root == nullptr)
    //    return false;

    tinyxml2::XMLElement* pListElement = root->FirstChildElement("Currency");
    //if (pListElement == nullptr)
    //    return false;

    while (pListElement != nullptr)
    {
        Currency currency;

        // In *.xml files if a foreign currency is expensive than US Dollar
        // it has CrossRateOther (for now: EUR, GBP, KWD), otherwise it has CrossRateUSD
        currency.CurrencyCode = pListElement->Attribute("CurrencyCode");
        pListElement->FirstChildElement("Unit")->QueryIntText(&currency.Unit);
        currency.CurrencyNameTR = pListElement->FirstChildElement("Isim")->GetText();
        rtrim(currency.CurrencyNameTR);
        currency.CurrencyNameEN = pListElement->FirstChildElement("CurrencyName")->GetText();
        rtrim(currency.CurrencyNameEN);
        pListElement->FirstChildElement("ForexBuying")->QueryDoubleText(&currency.ForexBuying);
        pListElement->FirstChildElement("ForexSelling")->QueryDoubleText(&currency.ForexSelling);
        if (pListElement->FirstChildElement("BanknoteBuying")->GetText() != nullptr)
            pListElement->FirstChildElement("BanknoteBuying")->QueryDoubleText(&currency.BanknoteBuying);
        else
            currency.BanknoteBuying = 0.0;
        if (pListElement->FirstChildElement("BanknoteSelling")->GetText() != nullptr)
            pListElement->FirstChildElement("BanknoteSelling")->QueryDoubleText(&currency.BanknoteSelling);
        else
            currency.BanknoteSelling = 0.0;
        if (pListElement->FirstChildElement("CrossRateUSD")->GetText() != nullptr)
            pListElement->FirstChildElement("CrossRateUSD")->QueryDoubleText(&currency.CrossRateUSD);
        else
            currency.CrossRateUSD = 0.0;
        if (pListElement->FirstChildElement("CrossRateOther")->GetText() != nullptr)
            pListElement->FirstChildElement("CrossRateOther")->QueryDoubleText(&currency.CrossRateOther);
        else
            currency.CrossRateOther = 0.0;

        currencyList.push_back(currency);

        pListElement = pListElement->NextSiblingElement("Currency");
    }
}

Currency TCMB::getCurrency(std::string currencyCode)
{
    Currency *currency = new Currency();

    for (const auto &i : currencyList)
    {
        if (i.CurrencyCode == currencyCode)
        {
            currency->CurrencyCode = i.CurrencyCode;
            currency->Unit = i.Unit;
            currency->CurrencyNameTR = i.CurrencyNameTR;
            currency->CurrencyNameEN = i.CurrencyNameEN;
            currency->ForexBuying = i.ForexBuying;
            currency->ForexSelling = i.ForexSelling;
            currency->BanknoteBuying = i.BanknoteBuying;
            currency->BanknoteSelling = i.BanknoteSelling;
            currency->CrossRateUSD = i.CrossRateUSD;
            currency->CrossRateOther = i.CrossRateOther;
        }
    }
    return *currency;
}

void TCMB::printCurrency(const Currency &currency)
{
    std::cout << currency.CurrencyCode << "\t"
              << currency.Unit << "\t"
              << currency.CurrencyNameTR << "\t"
              //<< currency.CurrencyNameEN << "\t"
              << currency.ForexBuying << "\t"
              << currency.ForexSelling << "\t"
              //<< currency.BanknoteBuying << "\t"
              //<< currency.BanknoteSelling << "\t"
              << currency.CrossRateUSD << "\t"
              << currency.CrossRateOther << '\n';
}

// https://stackoverflow.com/questions/21169419/whats-the-equivalent-of-nets-string-isnullorwhitespace-in-c
bool TCMB::isNullOrWhiteSpace( std::string const& str )
{
    return std::find_if(
               str.begin(),
               str.end(),
    []( unsigned char ch ) {
        return !isspace( ch );
    } )
    == str.end();
}

// https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
inline void TCMB::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

inline void TCMB::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
std::vector<std::string> TCMB::extractDate(const std::string &arg)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(arg);
    while (std::getline(tokenStream, token, '.'))
    {
        tokens.push_back(token);
    }
    return tokens;
}
