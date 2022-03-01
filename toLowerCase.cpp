// File server.c

#include <regex>
#include <iostream>
#include "toLowerCase.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "connection.h"

using namespace std;

bool toLowerCase(string data, string toSearch) {
    transform(data.begin(), data.end(), data.begin(), ::tolower);
    transform(toSearch.begin(), toSearch.end(), toSearch.begin(), ::tolower);
    std::regex e{"\\b" + toSearch + "\\b"};
    return regex_search(data, e);
}