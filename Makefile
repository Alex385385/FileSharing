main_compile :
	g++ -std=c++11 main.cpp server.cpp client.cpp login.cpp -o Sharing -l sqlite3