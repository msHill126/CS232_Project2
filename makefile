
gccFlags = -Wall -g -o indexPage.exe -std=gnu11

make:
	gcc source/main.c source/trie.c $(gccFlags)

publish: 
	cat source/publish.c source/trie.h source/main.c source/trie.c> indexPage.c
	gcc indexPage.c $(gccFlags)

publish-win:
	type source\publish.c source\trie.h source\main.c source\trie.c > indexPage.c
	gcc indexPage.c $(gccFlags)

testing:
	gcc source/trieTesting.c source/trie.c $(gccFlags)

clean:
	rm indexPage.c

