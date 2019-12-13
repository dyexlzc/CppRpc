Server:RpcServer.o ServType.o Server.o 
	g++ Server.o RpcServer.o ServType.o -g -o Server -lpthread -lboost_system

Server.o:Server.cpp
	g++ -g  -c Server.cpp
RpcServer.o:./RpcSrc/RpcServer.cpp
	g++ -g  -c ./RpcSrc/RpcServer.cpp
ServType.o:./RpcSrc/ServType.cpp
	g++ -g  -c ./RpcSrc/ServType.cpp
clean:
	rm -rf *.o 
	rm ./Server