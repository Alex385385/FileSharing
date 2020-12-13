main_compile :
	g++ -std=c++11 -w src/main.cpp src/server.cpp src/client.cpp src/login.cpp -o Sharing -l sqlite3