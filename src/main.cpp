#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "lexer.h"

using namespace std;

class CmdOptions {
public:
    string input_path;
    string output_path;

    int parse(int argc, char* argv[]) { 
        for (int i=1; i<argc; ++i) {
            auto arg = string(argv[i]);
            if (arg == "-o")  output_path = string(argv[++i]);
            else input_path = string(argv[i]);
        }

        return 0;
    }
};

string read_file(const string& file_path) {
    ifstream input;
    input.open(file_path);

    if (!input.is_open()) {
        cerr << "cannot open file " << file_path << endl;
        exit(1);
    }

    istreambuf_iterator<char> beg(input), end;
    string code(beg, end);

    input.close();
    return code;
}

void check_status(int status) {
    if (status != 0) {
        exit(status);
    } 
}

int compile(const string& code, CmdOptions options) {
    Lexer lexer(code);
    vector<Token> tokens;
    while (true) {
        Token token = lexer.lex();
        tokens.push_back(token);
        if(token.type == TokenType::END) break;
    }
    for(const auto& token : tokens) {
        cout << token << endl;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    CmdOptions options;
    int status = options.parse(argc, argv);
    check_status(status);
    
    string code = read_file(options.input_path);

    status = compile(code, options);
    check_status(status);

    return 0;
}