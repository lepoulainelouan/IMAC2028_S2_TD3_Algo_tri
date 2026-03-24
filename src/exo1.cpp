#include <cassert>
#include <charconv>
#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <stack>
#include <cmath>
#include <system_error>

//exercice 3 : Conversion en NPI, convertire en notation infixe 
//Algorithme de Shunting Yard, creation de la fonction infix_to_npi_tokens

enum class Operator { ADD, SUB, MUL, DIV, POW, OPEN_PAREN, CLOSE_PAREN };
enum class TokenType { OPERATOR, OPERAND };

void infix_to_npi_tokens(std::string const& expression) {
    std::stack<Operator> operators_stack {};
    std::vector<Token> output {};

    std::vector<Token> const tokens { tokenize(split_string(expression)) };

    for(Token const& token : tokens)
    {
        if (token.type == TokenType::OPERAND)
        {
            output.push_back(token);
        }
        else
        {
            Operator const& op { token.op };

            if (op == Operator::OPEN_PAREN)
            {
                operators_stack.push(op);
            }
            else if (op == Operator::CLOSE_PAREN)
            {
                while (!operators_stack.empty() && operators_stack.top() != Operator::OPEN_PAREN) {
                    output.push_back(make_token(operators_stack.top()));
                    operators_stack.pop();
                }
                if (!operators_stack.empty() && operators_stack.top() == Operator::OPEN_PAREN) {
                    operators_stack.pop();
                } else {
                    throw std::runtime_error("soucis avec les parenthèses la mon reuf");
                }
            }
            else {
                while (!operators_stack.empty() && operator_precedence(operators_stack.top()) >= operator_precedence(op)) {
                    output.push_back(make_token(operators_stack.top()));
                    operators_stack.pop();
                }
                operators_stack.push(op);
            }
        }
    }

    while (!operators_stack.empty()) {
        if (operators_stack.top() == Operator::OPEN_PAREN || operators_stack.top() == Operator::CLOSE_PAREN) {
            throw std::runtime_error("Erreur avec les parenthèses la mon reuf");
        }
        output.push_back(make_token(operators_stack.top()));
        operators_stack.pop();
    }

    return output;
}
