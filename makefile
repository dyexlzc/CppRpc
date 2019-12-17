Server:RpcServer.o ServType.o Server.o 
	g++ Server.o RpcServer.o ServType.o -ldl -g -o Server -lpthread -lboost_system -std=c++11

Server.o:Server.cpp
	g++ -g -ldl -c Server.cpp -std=c++11
RpcServer.o:./RpcSrc/RpcServer.cpp
	g++ -g -ldl -c ./RpcSrc/RpcServer.cpp -std=c++11
ServType.o:./RpcSrc/ServType.cpp
	g++ -g -ldl -c ./RpcSrc/ServType.cpp -std=c++11

client:Client.cpp
	g++ Client.cpp -o Client -lboost_system -lpthread -std=c++11
rpcclient:RpcClient.cpp
	g++ RpcClient.cpp -o rc -lboost_system -lpthread -std=c++11
clean:
	rm -rf *.o 
	rm ./Server