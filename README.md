# Parsely - Describe & deploy net protocol with simply a JSON file.
## Inspiration

* Nowadays, although is it very easy to create an App with internet communication module, it is still difficult to achive fast development of *high performance* server and clients. 
* Especially when devloping an App with customized network protocol, every time the developer add or delete something from the protocol, they need to rewrite, in the worst case, the whole parsing logic.
* We decided that we are going to simplify this process by building a *pre-processor/pre-compiler* called **POP** (Pre-processor of Parsely) with a library called **Parsely** working with it. And the pre-processor pushes all the nasty time consuming work to compile/pre-compile time. 

## What it does

* Parsely, by it name, must to have something to do with parsing. It deserializes **TCP** stream in **Binary** into small packets. **UDP** will be supported in the future.
* Parsely is a library which helps user, as a developer, **serialize** runtime **application data** into **network packets**, according to the **network protocol** defined by the user in a **JSON file**.

#### How it works:

* Step 1: Design and define your protocol in a  json file

  * How `proto.json` is defined (example):

  ```json
  {
  	"version" : [0, 0, 0],
  	"protocol" : {
  		"header" : 4,
  		"flags" : ["HeartBeat", "ConnectionInfo", "TextMessage", "ImageMessage"]
  	},
  
  	"fields" : {
  		"HeartBeat" : [
  			["string", "uuid"],
  			["string", "usrName"],
  			["string", "publicKey"],
  			["uint32", "timestamp"]
  		],
  	
  		"ConnectionInfo" : [
  			["string", "uuid"],
  			["string", "peers"]
  		],
  		
  		"TextMessage" : [
  			["string", "uuid"],
  			["string", "msgId"],
  			["string", "msg"]
  		],
  		
  		"ImageMessage" : [
  			["string", "uuid"],
  			["string", "msgId"],
  			["string", "msg"]
  		]
  	}
  }
  ```

  * `version` : POP version.
  * `protocol` : An overview of the protocol.
  * `header` : The size of header, which packetize the TCP stream. It is the size of the whole packet except the size of it self.
  * `flags` : Flags are used for application to determine what type of message the packet is transmitting. Different type of message has different fields, defined in `fields`.
  * `fields` : The message fields of `flag`s. Consisted of an **order sensitive** array of sub fields. So that the binary will be serialized and deserialized **sequencially** described here. The first element of a subfield, like in `["string", "uuid"]`, is the type of the subfield data. And the second is the same of the data, which is just a label for your and the pre-processor's reference when debugging.

* STEP 2: Compile your protocol to `ParseEngine`:

  * It translates the given **protocol description JSON file** to C++ code, which is a part of what we called the **Parse Engine**

  ```bash
  $ python3 pop.py ./my_proto_v1.json ./my_proj/src/
  Pre-processor of Parsely v1.0.1 stable 
  pop: Parsing /home/han/my_proto_v1.json ...
  pop: Generating decoder in C++ ...
  pop: Injecting compiled code to ./my_proj/src/parse_engine_decode_pop.cpp
  Sucessful!
  $ make -j8
  ```

* STEP 3: Encapsulate your own network stack:

  * The user first need to inherit his/her network class from our interface called the `NetStack`.
  * Note: you need to implement `virtual int NetStack::write(char* data, string &ip)` so that `ParseEngine` can automatically call `NetStack` to send out  message

  ```c++
  #include "parsely/net_stack.h"
  using namespace std;
  
  class ChatServer : public NetStack
  {
  public:
  	ChatServer(string &ip, const int &port);
  	
  	virtual int NetStack::write(char* data, string &ip);
  }
  ```

* STEP 4: Send message with `ParseEngine`:

  * How `ParseEngine` is used (example):

  ```c++
  #include "chat_server.h"
  #include "parse_engine.h"
  
  enum ProtoMsgType {
      HeartBeat,
      Text,
      Image,
  }
  
  void readMessage(Packet* p){
      // Do something...
  }
  
  int main(int argc, char **argv  ){
      // User code...
      
      ChatServer  *s = new ChatServer();
      ParseEngine *e = new ParseEngine(s);
      //bind read message callback
      e->onMessage = &readMessage;
      
      // construct packet according to the protocol
      Packet *p = new Packet{ 
          {
              "{cfceb206-290e-4b60-b596-1a08a2c8d36a}", // UUID
              "731948", 								  // Message ID
              "Hello?"								  // Message Text
          },
          Text
      };
      e->message(p, Text}, "155.246.104.55");
      
      // User code...
  }
  ```

  

  

## How we built it

* Parsing utility (library it self) functions and classes: **C++**.
* POP pre-compiler: **Python**

## Challenges we ran into

* Our wheel `Variant` class got its data member's memory corrupted several times because of a deep-copy that is not deep enough.

## Accomplishments that we're proud of

* Its is really fast and easy to use!!!!

- We wrote and used our own **wheels**!!!! 
- All the wheels are well test-cased and uses modern C++ templates for high runtime performance.

## What's next for Parsely

* We will further **simplify** the usage 
* Add packet oriented protocol support, like **UDP**
* Merge into opensource project [libParsley - Asynchronous cross-platform C++ library with delicate OOP callback system](https://github.com/ultrasilicon/libParsley) as a module. 
