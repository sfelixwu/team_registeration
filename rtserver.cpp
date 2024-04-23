
#include "ecs36b_Common.h"

#include "JvTime.h"

// for JsonRPCCPP
#include <iostream>
#include "rtserver.h"
#include <jsonrpccpp/server/connectors/httpserver.h>

using namespace jsonrpc;
using namespace std;

class myrtServer : public rtServer
{
public:
  myrtServer(jsonrpc::AbstractServerConnector &conn, jsonrpc::serverVersion_t type);
  // pure virtual function/method below --> we need to have it
  virtual Json::Value register_team(const std::string& action, const Json::Value& your_json);
};

myrtServer::myrtServer(AbstractServerConnector &connector, serverVersion_t type)
  : rtServer(connector, type)
{
  std::cout << "myrtServer Object created" << std::endl;
}

// member functions

Json::Value
myrtServer::register_team
(const std::string& action, const Json::Value& your_json)
{
  Json::Value result;
  std::cout << action << " " << your_json << std::endl;

  JvTime *jvt_ptr = getNowJvTime();
  Json::Value *jv_ptr = jvt_ptr->dump2JSON();
  
  result["time"]   = *(jv_ptr);
  delete jvt_ptr;
  delete jv_ptr;

  result["status"] = "failed";
  result["registration"] = your_json;

  if (your_json.isObject() == true)
    {
      if ((your_json["team name"].isNull() == false) &&
	  (your_json["team name"].isString() == true))
	{
	  if ((your_json["students"].isNull() == false) &&
	      (your_json["students"].isArray() == true))
	    {
	      result["status"] = "successful";
	    }
	}
    }

  char file_name[256];
  bzero(file_name, 256);
  snprintf(file_name, 15, "./rt_teams.log");
  std::string s { file_name };
  myPrintLog(result.toStyledString(), s);
  
  return result;
}

int
main
(void)
{
  HttpServer httpserver(8300);
  myrtServer s(httpserver,
	       JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}
