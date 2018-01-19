//
// Created by igor on 19.01.18.
//

#ifndef TONEPICK_LOCALIZEDSTRINGS_H
#define TONEPICK_LOCALIZEDSTRINGS_H

#include "rapidjson/document.h"

using namespace rapidjson;
using namespace std;

class LocalizedStrings {
public:
    static LocalizedStrings *getInstance();

    void setLanguage(string language);

    const char *getString(const char *message);

private:
    string _language;
    Document _document;
};

#endif //TONEPICK_LOCALIZEDSTRINGS_H
