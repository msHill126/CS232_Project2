
gccFlags = -Wall -g -o indexPage.exe

make:
	gcc source/main.c source/trie.c $(gccFlags)

publish: clean
	cat source/publish.c source/trie.h source/main.c source/trie.c> indexPage.c
	gcc indexPage.c $(gccFlags)

publish-win: clean
	type source\publish.c source\trie.h source\main.c source\trie.c > indexPage.c
	gcc indexPage.c $(gccFlags)

testing:
	gcc source/trieTesting.c source/trie.c $(gccFlags)

clean:
	rm indexPage.c

