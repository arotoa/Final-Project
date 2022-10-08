cmake_minimum_required(VERSION 3.16.3)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_executable(main.cpp
        Lexer.cpp
        Lexer.h
        QueriesAutomaton.cpp
        QueriesAutomaton.h
        IDAutomaton.cpp
        IDAutomaton.h
        StringAutomaton.cpp
        StringAutomaton.h
        SingleSymbolAutomaton.h
        SingleSymbolAutomaton.cpp
        SchemesAutomaton.cpp
        SchemesAutomaton.h
        Automaton.h
        RulesAutomaton.cpp
        RulesAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        FactsAutomaton.cpp
        FactsAutomaton.h
        main.cpp
        Token.h
        Token.cpp
        CommentAutomaton.cpp
        CommentAutomaton.h
        DatalogProgram.cpp
        DatalogProgram.h
        Rule.cpp
        Rule.h
        Predicate.cpp
        Predicate.h
        Parameter.h Parser.cpp Parser.h Database.h Relation.cpp Relation.h Header.h Tuple.h Interpreter.cpp Interpreter.h Graph.cpp Graph.h)
