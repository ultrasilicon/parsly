#include "parse_engine.h"

#include "net_stack.h"
#include "packet.h"

#include "sized_mask.h"


iovec ParseEngine::encode(Packet *packet)
{
    std::vector<char> stream(sizeof(uint32_t) + 1); // vector as memory management helper
    size_t pos = decltype (stream)::size_type{};
    const auto flag = packet->msgType;

    ///[BEGIN _POP_ENCODER_INJECT_POINT]///
	switch (flag) {
	case 0: { // HeartBeat
			insertStr(stream, pos, packet->data[0].get<std::string>()); // uuid
			insertStr(stream, pos, packet->data[1].get<std::string>()); // usrName
			insertStr(stream, pos, packet->data[2].get<std::string>()); // publicKey
			insertVal(stream, pos, packet->data[3].get<uint32_t>()); // timestamp
		break;
	}
	case 1: { // ConnectionInfo
			insertStr(stream, pos, packet->data[0].get<std::string>()); // uuid
			insertStr(stream, pos, packet->data[1].get<std::string>()); // peers
		break;
	}
	case 2: { // TextMessage
			insertStr(stream, pos, packet->data[0].get<std::string>()); // uuid
			insertStr(stream, pos, packet->data[1].get<std::string>()); // msgId
			insertStr(stream, pos, packet->data[2].get<std::string>()); // msg
		break;
	}
	case 3: { // ImageMessage
			insertStr(stream, pos, packet->data[0].get<std::string>()); // uuid
			insertStr(stream, pos, packet->data[1].get<std::string>()); // msgId
			insertStr(stream, pos, packet->data[2].get<std::string>()); // msg
		break;
	}
	}
    ///[END _POP_ENCODER_INJECT_POINT]///

    size_t mainHeader = stream.size() - sizeof(uint32_t); // total size excluding main header
    memcpy(&((SizedMask<uint32_t>*) &stream.front())->header, &mainHeader, sizeof(uint32_t)); // set main header

    auto* data = new char[stream.size()]; // to return
    memcpy(data, stream.data(), stream.size());

    iovec r{data, stream.size()};
    return r;
}
