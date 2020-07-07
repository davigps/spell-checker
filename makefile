all: ./source/spell_checker.c 
	gcc ./source/spell_checker.c -o ./source/SpellChecker -lm

clean:
	rm -rf ./source/*.o ./main