hello:
	gcc src/main.c -o hello

linked_list:
	g++ src/linked_list.cpp -o linked_list

clean:
	rm -f hello
	rm -f linked_list
