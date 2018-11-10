#include "Server.h"

using namespace std;

int main()
{
	Server server;
	
	server.startupWinsock()
		  .bindSocket()
		  .initClientMetaData()
		  .initLoop()
		  .closeSocket()
		  .cleanup();	
}