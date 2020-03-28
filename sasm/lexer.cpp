#include "lexer.h"

strings Lexer::lex(std::string s){
	strings strlst;
	char lexeme[256];
	int i, j, done, balance = 0;
	State state = START;
	int len = s.length();

	while (i < len){
		switch(state) {
			case START:
				if (_isspace(s[i])){
					state = SKIP;
				} else if (_isgroup(s[i])){
					if (s[i] == '"'){
						lexeme[j] = s[i];
						j++;
						i++;
					}
					state = READBLOCK;
				} else if (s[i] == '/' && s[i + 1] =='/') {
					i += 2;
					state = COMMENT;
				} else {
					state = READCHAR;
				}
				break;
			case READCHAR:
				if (_isspace(s[i])) {
					state = DUMP;
				} else if (s[i] == '\\'){
					i += 2;
				} else if (_isgroup(s[i])) {
					if (s[i] == '"'){
						lexeme[j] = s[i];
						j++;
						i++;
					}
					state = READCHAR;
				} else if (_isspecial(s[i])) {
					if (j == 0) {
						lexeme[j] = s[i];
						j++;
						i++;
					}
					state = DUMP;
				} else if (s[i] == '/' && s[i + 1] == '/') {
					i += 2;
					state = COMMENT;
				} else {
					lexeme[j] = s[i];
					i++;
					j++;
				}
				break;
			case READBLOCK:
				if (s[i] == beg_char && s[i] != '"') {
					balance++;
					lexeme[j] = s[i];
					j++;
					i++;
					if (balance <= 0) {
						state = DUMP;
					}
				} else if (end_char == '"' && s[i] == '\\') {
					i += 2;
				} else {
					lexeme[j] = s[i];
					j++;
					i++;
				}
				break;
			case SKIP:
				if (_isspace(s[i])){
					i++;
				}  else{
					state = READCHAR;
				} 
				break;
			case DUMP:
				if (j > 0){
					lexeme[j] = 0;
					strlst.push_back(lexeme);
					j = 0;
				}
				state = START;
				break;
			case COMMENT:
				if (s[i] != '\n') {
					i++;
				} else {
					state = READCHAR;
				}
				break;
			case END:
				i = len;
				break;
		}
	}
	if (j > 0){
		lexeme[j] = 0;
		strlst.push_back(lexeme);
	}
	return strlst;	
}

//define what a space is ->  more control than standard isspace func

bool Lexer::_isspace(char c) {
	switch(c){
		case '\n':
		case '\r':
		case '\t':
		case '\v':
		case ' ':
		case '\f':
			return true;
		default:
			return false;
	}
}

bool Lexer::_isgroup(char c) {
	beg_char = c;
	switch(c){
		case '"':
			end_char = '"';
			return true;
		case '(':
			end_char = ')';
			return true;
		case ')':
			return true;
		default:
			return false;
	}
}

bool Lexer::_isspecial(char c) {
	switch(c) {
		case '[':
		case ']':
			return true;
		default:
			return false;
	}
}