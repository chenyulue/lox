ast: com/craftinginterpreters/tool/GenerateAst.class
	java com.craftinginterpreters.tool.GenerateAst com/craftinginterpreters/lox

com/craftinginterpreters/tool/GenerateAst.class: com/craftinginterpreters/tool/GenerateAst.java
	javac $<

run: com/craftinginterpreters/lox/Lox.class
	java com.craftinginterpreters.lox.Lox

com/craftinginterpreters/lox/Lox.class: com/craftinginterpreters/lox/Lox.java com/craftinginterpreters/lox/Interpreter.java com/craftinginterpreters/lox/Parser.java
	javac $<
