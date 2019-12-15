Server:RpcServer.o ServType.o Server.o 
	g++ Server.o RpcServer.o ServType.o -ldl -g -o Server -lpthread -lboost_system

Server.o:Server.cpp
	g++ -g -ldl -c Server.cpp
RpcServer.o:./RpcSrc/RpcServer.cpp
	g++ -g -ldl -c ./RpcSrc/RpcServer.cpp
ServType.o:./RpcSrc/ServType.cpp
	g++ -g -ldl -c ./RpcSrc/ServType.cpp

client:Client.cpp
	g++ Client.cpp -o Client -lboost_system -lpthread
rpcclient:RpcClient.cpp
	g++ RpcClient.cpp -o rc -lboost_system -lpthread
clean:
	rm -rf *.o 
	rm ./Server