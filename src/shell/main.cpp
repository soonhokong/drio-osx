// Copyright 2014 Jichao Sun
// Email: Jichaos@andrew.cmu.edu

#include <istream>
#include <iostream>
#include <cstdio>

// Forward delcarations
void init();
void next();
double expr();
void error(const char *msg);

// input buffer
char *input;

// Toke buffer
char buf[1024];
int n = 0;

// Current character
int ch;

// Look_ahead token
enum LL { ADD_OP, MUL_OP, LEFT_PAREN, RIGHT_PAREN, NUMBER, END_INPUT } look_ahead;

int main(int argc, char const *argv[]){
    printf(">");
    char cmd[1024];
    while (std::cin.getline(cmd, 1024)){
        input = cmd;
        init();
        printf("%f\n", expr());
        printf(">");
    }
    printf("\n");
    return 0;
}

void error(const char *msg){
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

// Reset the token buffer
void reset(){
    n = 0;
    buf[0] = '\0';
}

// Buffers the current character, then get new character
void read(){
    buf[n++] = ch;
    buf[n] = '\0';
    ch = input[0];
    input++;
}

// Ignore current character, gets new character
void ignore(){
    ch = *input;
    input++;
}

int scan(){
    reset();
START:
    switch (ch){
    case ' ': case '\t': case '\r':
        ignore();
        goto START;

    case '-': case '+':
        read();
        return ADD_OP;

    case '*': case '/':
        read();
        return MUL_OP;

    case '(':
        read();
        return LEFT_PAREN;

    case ')':
        read();
        return RIGHT_PAREN;

    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        read();
        goto IN_LEADING_DIGITS;

    case '\0':
        ch = ' ';    //  delayed ignore()
        return END_INPUT;

    default:
        error("bad character");
    }

IN_LEADING_DIGITS:
    switch (ch){
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        read();
        goto IN_LEADING_DIGITS;

    case '.':
        read();
        goto IN_TRAILING_DIGITS;

    default:
        return NUMBER;
    }

IN_TRAILING_DIGITS:
    switch (ch){
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        read();
        goto IN_TRAILING_DIGITS;

    default:
        return NUMBER;
    }
}

void next(){
    look_ahead = (LL)scan();
}

// Initialize scanner
void init(){
    reset();
    ignore(); // gets current character
    next();
}

double unsigned_factor(){
    double res = 0;

    switch (look_ahead){
    case NUMBER:
        sscanf(buf, "%lf", &res);
        next();
        break;

    case LEFT_PAREN:
        next();
        res = expr();
        if (look_ahead != RIGHT_PAREN)
            error("Missing ')'");
        next();
        break;

    default:
        error("Unexpected token");
        break;
    }
    return res;
}

double factor(){
    double res = 0;
    // Check for leading minus
    if (look_ahead == ADD_OP && buf[0] == '-'){
        next();
        res = -unsigned_factor();
    } else {
        res = unsigned_factor();
    }
    return res;
}

double term(){
    double res = factor();
    while (look_ahead == MUL_OP){
        switch (buf[0]){
        case '*':
            next();
            res *= factor();
            break;
        case '/':
            next();
            res /= factor();
            break;
        }
    }
    return res;
}

double expr(){
    double res = term();
    while (look_ahead == ADD_OP){
        switch (buf[0]){
        case '+':
            next();
            res += term();
            break;

        case '-':
            next();
            res -= term();
            break;
        }
    }
    return res;
}
