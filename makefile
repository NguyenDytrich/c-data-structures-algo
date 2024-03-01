hello:
	gcc src/main.c -o hello

linked_list:
	gcc src/linked_list.c -o linked_list

clean:
	rm -f hello
	rm -f linked_list
