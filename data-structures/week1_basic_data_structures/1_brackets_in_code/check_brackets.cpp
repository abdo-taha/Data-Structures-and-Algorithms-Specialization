#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    bool good = 1; int pos = 0;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push(Bracket(next,position+1));
        }

        if (next == ')' || next == ']' || next == '}') {
            if(opening_brackets_stack.empty()) {
                good = 0; pos = position+1; break;
            }
            Bracket temp_Bracket = opening_brackets_stack.top();
            opening_brackets_stack.pop();
            if(!temp_Bracket.Matchc(next)){
                good = 0; pos = position+1; break;
            }
        }
    }
    if(good && (!opening_brackets_stack.empty())){
        good = 0;
        Bracket temp_Bracket =opening_brackets_stack.top() ;
        while(!opening_brackets_stack.empty()){
            temp_Bracket = opening_brackets_stack.top();
            opening_brackets_stack.pop();
        }
        pos = temp_Bracket.position;

    }
    if(good) std::cout<<"Success";
    else std::cout<<pos;



    return 0;
}
