
// ecs36b rt client

#include "ecs36b_Common.h"

// JSON RPC part
#include "rtclient.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;
using namespace std;

int
main(void)
{
  HttpClient httpclient { "https://ethikos.ngrok.io" };
  rtClient myClient { httpclient, JSONRPC_CLIENT_V2 };
  Json::Value my_json;
  Json::Value result;

  my_json["team name"] = "My Team Name"; // replace this with your own team name
  my_json["students"][0] = "123456789";  // student ID 1
  my_json["students"][1] = "987654321";  // student ID 2
  // my_json["students"][2] = "345678901";  // student ID 3, if needed

  try {
    result = myClient.register_team("register team", my_json);
    cout << result.toStyledString() << endl;
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  return 0;
}
