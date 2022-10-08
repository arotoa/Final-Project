#include "DatalogProgram.h"
#include "Parser.h"
#include <sstream>
#include <iostream>

void DatalogProgram::startParser() {
    Parser* parser = new Parser(tokens);
    parser->parse();
    schemes = parser->schemes;
    rules = parser->allRules;
    facts = parser->facts;
    queries = parser->queries;
    domains = parser->domains;

}

