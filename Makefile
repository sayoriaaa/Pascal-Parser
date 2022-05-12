parser:
	g++ lexer.cpp lexer.h parser.cpp parser.h -o parser

table:
	g++ get_predict_table.cpp -o table