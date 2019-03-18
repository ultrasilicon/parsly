#include "parse_engine.h"

#include "net_stack.h"
#include "packet.h"

#include "sized_mask.h"

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
			redeemStr<pe_str_len_t>(pos, end), // uuid
			redeemStr<pe_str_len_t>(pos, end), // usrName
			redeemStr<pe_str_len_t>(pos, end), // publicKey
			redeemVal<uint32_t>(pos, end), // timestamp
		}, flag};
		break;
	}
	case 1: { // ConnectionInfo
		return new Packet{{
			redeemStr<pe_str_len_t>(pos, end), // uuid
			redeemStr<pe_str_len_t>(pos, end), // peers
		}, flag};
		break;
	}
	case 2: { // TextMessage
		return new Packet{{
			redeemStr<pe_str_len_t>(pos, end), // uuid
			redeemStr<pe_str_len_t>(pos, end), // msgId
			redeemStr<pe_str_len_t>(pos, end), // msg
		}, flag};
		break;
	}
	case 3: { // ImageMessage
		return new Packet{{
			redeemStr<pe_str_len_t>(pos, end), // uuid
			redeemStr<pe_str_len_t>(pos, end), // msgId
			redeemStr<pe_str_len_t>(pos, end), // msg
		}, flag};
		break;
	}
	}
  ///[END _POP_DECODER_INJECT_POINT]////

  decodeCleanup(pos, stream, size);
  return nullptr;
}
