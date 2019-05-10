#include "parse_engine.h"

#include "net_stack.h"
#include "packet.h"

#include "sized_mask.h"


iovec ParseEngine::encode(Packet *packet)
{
    std::vector<char> stream(sizeof(uint32_t) + 1); // vector as memory management helper
    size_t pos = decltype (stream)::size_type{};
    const auto flag = packet->msgType;

    insertVal(stream, pos, flag); // msgType

    ///[BEGIN _POP_ENCODER_INJECT_POINT]///
	switch (flag) {
	case 0: { // HeartBeat
			insertVal(stream, pos, packet->data[0].get<int32_t>()); // timestamp
		break;
	}
	case 1: { // AuthReq
			insertStr(stream, pos, packet->data[0].get<std::string>()); // pubKey
		break;
	}
	case 2: { // AuthRes
			insertStr(stream, pos, packet->data[0].get<std::string>()); // sessionKey@pubKey
		break;
	}
	case 3: { // LoginReq
			insertStr(stream, pos, packet->data[0].get<std::string>()); // pubKey@sessionKey
		break;
	}
	case 4: { // LoginRes
			insertVal(stream, pos, packet->data[0].get<bool>()); // success
			insertStr(stream, pos, packet->data[1].get<std::string>()); // msg
		break;
	}
	case 5: { // MsgTxt
			insertStr(stream, pos, packet->data[0].get<std::string>()); // receiverPubKey
			insertVal(stream, pos, packet->data[1].get<int32_t>()); // timestamp
			insertStr(stream, pos, packet->data[2].get<std::string>()); // msg
		break;
	}
	}
    ///[END _POP_ENCODER_INJECT_POINT]///

    size_t mainHeader = stream.size() - sizeof(uint32_t); // total size excluding main header

    memcpy(&((SizedMask<uint32_t>*) &stream.front() + sizeof (flag))->header, &mainHeader, sizeof(uint32_t)); // set main header

    auto* data = new char[stream.size()]; // to return
    memcpy(data, stream.data(), stream.size());

    iovec r{data, stream.size()};
    return r;
}
