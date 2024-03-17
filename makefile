
gccFlags = -Wall -g -o indexPage.exe

make:
	gcc source/main.c source/trie.c $(gccFlags)

publish:
	cat source/publish.c source/trie.h source/main.c source/trie.c> indexPage.c
	gcc indexPage.c $(gccFlags)

publish-win:
	type source\publish.c source\trie.h source\main.c source\trie.c > indexPage.c
	gcc indexPage.c $(gccFlags)

clean:
	rm indexPage.c

