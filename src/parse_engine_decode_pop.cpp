#include "parse_engine.h"

#include "net_stack.h"

#include <libagio/protocol_utils.h>

using namespace Agio::ProtocolUtils;

Packet* ParseEngine::decode(char* stream, const size_t &size)
{
  if(!decodable(stream, size))
    return nullptr;

  auto pos = scopeBegin<uint32_t>(stream);
  auto end = scopeEnd<uint32_t>(stream);
  auto flag = redeemVal<uint8_t>(pos, end);

  ///[BEGIN _POP_DECODER_INJECT_POINT]////
	switch (flag) {
	case 0: { // HeartBeat
		return new Packet{{
			redeemVal<int32_t>(pos, end), // timestamp
		}, flag};
		break;
	}
	case 1: { // AuthReq
		return new Packet{{
			redeemStr<pe_str_len_t>(pos, end), // pubKey
		}, flag};
		break;
	}
	case 2: { // AuthRes
		return new Packet{{
			redeemStr<pe_str_len_t>(pos, end), // sessionKey@pubKey
		}, flag};
		break;
	}
	case 3: { // LoginReq
		return new Packet{{
			redeemStr<pe_str_len_t>(pos, end), // pubKey@sessionKey
		}, flag};
		break;
	}
	case 4: { // LoginRes
		return new Packet{{
			redeemVal<bool>(pos, end), // success
			redeemStr<pe_str_len_t>(pos, end), // msg
		}, flag};
		break;
	}
	case 5: { // MsgTxt
		return new Packet{{
			redeemStr<pe_str_len_t>(pos, end), // receiverPubKey
			redeemVal<int32_t>(pos, end), // timestamp
			redeemStr<pe_str_len_t>(pos, end), // msg
		}, flag};
		break;
	}
	}
  ///[END _POP_DECODER_INJECT_POINT]////

  decodeCleanup(pos, stream, size);
  return nullptr;
}
