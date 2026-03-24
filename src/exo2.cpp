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

// Opérateur de flux pour des vecteur, tiré du cours : https://dsmte.github.io/Learn--cpp_programming/Lessons/S2/Operators#op%C3%A9rateurs-de-flux
template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& array)
{
    os << "[";
    for (size_t i {0}; i<array.size()-1; ++i)
    {
        os << array[i] << ", ";
    }
    os << array[array.size()-1] << "]";
    return os;
}

// Version C++17 pour convertir une chaîne en float, avec gestion d'erreur sous forme de retour optionnel (std::nullopt en cas d'erreur)
std::optional<float> convert_to_float(std::string const& s)
{
    float value {};
    auto [p, ec] = std::from_chars(s.data(), s.data() + s.size(), value);
    return (ec == std::errc() && p == s.data() + s.size()) ? std::optional<float>{value} : std::nullopt;
}

std::vector<std::string> split_string(std::string const& s)
{
    std::istringstream in(s); // transforme une chaîne en flux de caractères, cela simule un flux comme l'est std::cin
    // l’itérateur va lire chaque element de "in", comme un flux d'entrée, chaque élément est séparé par un espace
    return std::vector<std::string>(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>()); 
}

enum class Operator { ADD, SUB, MUL, DIV, POW, OPEN_PAREN, CLOSE_PAREN };
enum class TokenType { OPERATOR, OPERAND };

struct Token {
    TokenType type {};
    float value {};
    Operator op {};
};

bool operator==(Token const& lhs, Token const& rhs) {
    if(lhs.type != rhs.type) {
        return false;
    }

    return lhs.type == TokenType::OPERAND ? lhs.value == rhs.value : lhs.op == rhs.op;
}

bool operator!=(Token const& lhs, Token const& rhs) {
    return !(lhs == rhs);
}

// Operator overload for printing tokens
std::ostream& operator<<(std::ostream& os, Token const& token) {
    if (token.type == TokenType::OPERAND) {
        os << token.value;
    } else {
        switch (token.op) {
            case Operator::ADD: os << "+"; break;
            case Operator::SUB: os << "-"; break;
            case Operator::MUL: os << "*"; break;
            case Operator::DIV: os << "/"; break;
            case Operator::POW: os << "^"; break;
            case Operator::OPEN_PAREN: os << "("; break;
            case Operator::CLOSE_PAREN: os << ")"; break;
        }
    }
    return os;
}

Token make_token(float value) {
    return {
    TokenType::OPERAND,
    value
    };
}

// Version en utilisant la syntaxe d'initialisation désignée de C++20
Token make_token(Operator op) {
    return Token {
        .type = TokenType::OPERATOR,
        .op = op
    };
}

size_t operator_precedence(Operator const op)
{
    switch (op)
    {
        case Operator::ADD:
        case Operator::SUB:
            return 1;
        case Operator::MUL:
        case Operator::DIV:
            return 2;
        case Operator::POW:
            return 3;
        default:
            return 0;
    }
}

std::vector<Token> tokenize(std::vector<std::string> const& words) {
    std::vector<Token> tokens {};
    for (auto const& word : words) {
        std::optional<float> maybe_float { convert_to_float(word) };
        if (maybe_float)
        {
            tokens.push_back(make_token(*maybe_float));
        }
        else
        {
            if (word == "+") {
                tokens.push_back(make_token(Operator::ADD));
            } else if (word == "-") {
                tokens.push_back(make_token(Operator::SUB));
            } else if (word == "*") {
                tokens.push_back(make_token(Operator::MUL));
            } else if (word == "/") {
                tokens.push_back(make_token(Operator::DIV));
            } else if (word == "^") {
                tokens.push_back(make_token(Operator::POW));
            } else if (word == "(") {
                tokens.push_back(make_token(Operator::OPEN_PAREN));
            } else if (word == ")") {
                tokens.push_back(make_token(Operator::CLOSE_PAREN));
            } else {
                throw std::runtime_error("Invalid token");
            }
        }
    }
    return tokens;
}

float npi_evaluate_with_tokens(std::vector<Token> const& tokens) {
    std::stack<float> stack {};

    for(auto const& token : tokens) {
        if (token.type == TokenType::OPERAND)
        {
            stack.push(token.value);
        }
        else
        {
            float rightOperand { stack.top() };
            stack.pop();
            float leftOperand { stack.top() };
            stack.pop();

            switch (token.op) {
                case Operator::ADD:
                    stack.push(leftOperand + rightOperand);
                    break;
                case Operator::SUB:
                    stack.push(leftOperand - rightOperand);
                    break;
                case Operator::MUL:
                    stack.push(leftOperand * rightOperand);
                    break;
                case Operator::DIV:
                    stack.push(leftOperand / rightOperand);
                    break;
                case Operator::POW:
                    stack.push(std::pow(leftOperand, rightOperand));
                    break;
                default:
                    throw std::runtime_error("Invalid token for evaluation");
            }
        }
    }
    return stack.top();
}

std::vector<Token> infix_to_npi_tokens(std::string const& expression) {
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

            // TODO: gérer les parenthèses
            if (op == Operator::OPEN_PAREN)
            {
                operators_stack.push(op);
            }
            else if (op == Operator::CLOSE_PAREN)
            {
                // TODO: enlever les opérateurs de la pile jusqu'à trouver une parenthèse ouvrante
            }
            else {
                // TODO: tant que la pile n'est pas vide et que l'opérateur au sommet de la pile a une priorité supérieure ou égale à celle de l'opérateur actuel, dépiler les opérateurs de la pile vers la sortie

                // Sinon: empiler l'opérateur actuel sur la pile
            }
        }
    }

    // TODO: une fois que tous les tokens ont été traités, dépiler tous les opérateurs restants de la pile vers la sortie
    // while ()
    // {

    // }

    return output;
}

int main()
{
    std::string input {};
	
    std::getline(std::cin, input);

    std::cout << "raw input: " << input << std::endl;

    std::vector<std::string> elements { split_string(input) };

    std::cout << "elements: " << elements << std::endl;

    std::vector<Token> tokens { tokenize(elements) };

    std::cout << "tokens: "  << tokens << std::endl;

    std::cout << "Evaluation: " << npi_evaluate_with_tokens(tokens) << std::endl;


    // test
    std::string const test_expression {
        "3 + 4 ^ 2 / ( 1 - 5 ) ^ 6"
    };

    std::vector<Token> const expected_npi_tokens {
            make_token(3),
            make_token(4),
            make_token(2),
            make_token(Operator::POW),
            make_token(1),
            make_token(5),
            make_token(Operator::SUB),
            make_token(6),
            make_token(Operator::POW),
            make_token(Operator::DIV),
            make_token(Operator::ADD)
        };

    std::cout << "Testing infix_to_npi_tokens with expression: " << test_expression << std::endl;

    std::vector<Token> const npi_tokens { infix_to_npi_tokens(test_expression) };

    std::cout << "Expected NPI tokens: " << expected_npi_tokens << std::endl;
    std::cout << "Computed NPI tokens: " << npi_tokens << std::endl;

    assert(npi_tokens == expected_npi_tokens);

	return 0;
}