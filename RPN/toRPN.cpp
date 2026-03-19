#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cctype>
using namespace std;

vector<string> split_to_parts(string a){
    vector<char> ops = {'+', '-', '*', '/', '@'};
    vector<string> parts;
    string num = "";
    string op = "";

    if(a == ""){
        parts.push_back("no formula");
        return parts;
    }

    int str_size = a.size();
    if(!isdigit(a[str_size-1]) && a[str_size-1] != ')'){ // 末尾に数字が来ない場合
            parts.push_back("end parts is not number");
            return parts;
    }
    if(!isdigit(a[0]) && a[0] != '@' && a[0] != '(' && a[0] != '-'){
            parts.push_back("first is not number");
            return parts;
        }
    for(int i = 0; i < str_size; i++){
        if(a[i] == ' ') continue; //空白が混じっていた場合

        auto is_op = find(ops.begin(), ops.end(), a[i]);
        if(isdigit(a[i]) || a[i] == '.'){ // 自然数もしくは小数
            num += a[i];
        } else if(a[i] == '-'){ // 単項マイナス判定
            if(i == 0 || a[i-1] == '(' || find(ops.begin(), ops.end(), a[i-1]) != ops.end()){
                parts.push_back("@");
            } else {
                if(num != "") parts.push_back(num);
                num = "";
                parts.push_back("-");
            }
        } else if (a[i] == '(') {
            op = a[i];
            if(op != "") parts.push_back(op);
            op = "";
        } else if (i > 0 && a[i] == ')' || // 文頭でない、かつ記号が連続していないなら
                  (is_op != ops.end() &&
                   find(ops.begin(), ops.end(), a[i-1]) == ops.end())) { // 演算子
            if(num != "") parts.push_back(num);
            op = a[i];
            if(op != "") parts.push_back(op);
            op = "";
            num = "";
        } else {
            parts.clear();
            parts.push_back("error");
            return parts;
        }
    }
    if(num != "") parts.push_back(num);
    int open = 0, close = 0;
    for(int i = 0; i < parts.size(); i++){
        if(parts[i] == "("){
            open++;
        }else if(parts[i] == ")"){
            close++;
        }
    }
    if(open != close){
        parts.clear();
        parts.push_back("() error");
        return parts;
    }
    return parts;
}

void show_vector(vector<string> a){
    for(int i = 0; i < a.size(); i++){
        cout << a[i] << " ";
    }
    cout << "|";
}

void show_stack(vector<string> a){
    for(int i = a.size() - 1; i >= 0; i--){
        cout << " " << a[i];
    }
    cout << "|";
}

int rpn(vector<string> input){
    vector<string> ops = {"+", "-", "*", "/", "@"};
    map<string, int> priority_map;
    priority_map["$"] = 0;
    priority_map["+"] = 2;
    priority_map["-"] = 2;
    priority_map["*"] = 3;
    priority_map["/"] = 3;
    priority_map["@"] = 4;

    vector<string> stack;
    vector<string> output;
    string end_op;
    string op;

    stack.push_back("$");

    show_vector(input);
    show_stack(stack);
    show_vector(output);
    cout << endl;
    while(input.size() > 0){
        if(input[0] == "("){ // 前括弧はそのままstack
            stack.push_back(input[0]);
        }else if(input[0] == ")"){ // 後括弧の時は前括弧が現れるまで演算子を出力し続ける
            while(!stack.empty() && stack.back() != "("){
                output.push_back(stack.back());
                stack.pop_back();
            }
            if(stack.back() == "(") stack.pop_back();
        }else if((find(ops.begin(), ops.end(), input[0]) == ops.end())){
            output.push_back(input[0]); // 数値ならそのまま出力
        }else if((find(ops.begin(), ops.end(), input[0]) != ops.end())){ // 演算子の場合
            op = input[0];
            while(stack.size() > 1 &&
                  stack.back() != "(" &&
                  (op != "@" && priority_map[op] <= priority_map[stack.back()] || // 演算子の左結合
                   op == "@" && priority_map[op] <  priority_map[stack.back()])){ // 単項マイナスの右結合
                output.push_back(stack.back());
                stack.pop_back();
            }
            stack.push_back(op);
        }

        input.erase(input.begin());
        show_vector(input);
        show_stack(stack);
        show_vector(output);
        cout << endl;
    }

    while(stack.size() > 1){
        output.push_back(stack.back());
        stack.pop_back();
        show_vector(input);
        show_stack(stack);
        show_vector(output);
        cout << endl;
    }
    cout << "RPN result" << endl;
    for(int i = 0; i < output.size(); i++){
        cout << output[i] << " ";
    }
    cout << endl;
    return 0;
}

int main() {
    string input;
    cout << "input formula" << endl;
    getline(cin, input);
    cout << endl;
    input.erase(remove_if(input.begin(), input.end(),
        [](unsigned char c){ return isspace(c); }),
        input.end());
    cout << input << endl;
    // string input = "(3+4)";
    // cout << "input\n" << input << endl;
    vector<string> parts = split_to_parts(input);
    int convert = rpn(parts);


    return 0;
}
