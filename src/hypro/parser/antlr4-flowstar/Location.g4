/*
 * Location.g4
 *
 * @author Phillip Tse
 * @date 20.6.2017
 *
 * A grammar for AnTLR to generate a parser for the location of a hybrid automaton.
 */

grammar Location;

import Formula;

////// Parser Rules

modes			: 'modes' '{' location* '}' ;

location 		: VARIABLE '{' activities invariants '}' ;

activities		: 'poly ode 1' '{' equation* '}' ;				//can be poly ode 1/2/3 or linear ode 1

invariants		: 'inv' '{' (boolexpr | intervalexpr)* '}' ;

////// Lexer Rules

