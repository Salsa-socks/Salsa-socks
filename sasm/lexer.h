#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>

typedef uint8_t byte;
typedef std::vector<std::string> strings;

enum State : byte {
	START,
	READCHAR,
	READBLOCK,
	SKIP,
	DUMP,
	COMMENT,
	END
};

class Lexer {
	bool _isspace(char c);
	bool _isspecial(char c);
	bool _isgroup(char c);
	char end_char, beg_char;

	public:
		strings lex(std::string s);
};

#endif