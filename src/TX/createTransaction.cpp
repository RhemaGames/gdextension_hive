
#include "createTransaction.h"
#include "../hive.h"
#include "hive_operations.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/http_client.hpp>
#include <godot_cpp/classes/http_request.hpp>
#include <godot_cpp/classes/crypto.hpp>
#include <godot_cpp/classes/crypto_key.hpp>
#include <godot_cpp/classes/time.hpp>

#include <godot_cpp/core/class_db.hpp>
using namespace godot;

//#include <openssl/ssl.h>

//import { getGlobalProps } from '../helpers/globalProps.js'

/** Create transaction by operations */
/*
export const createTransaction = async (operations, exp) => {
  const expireTime = exp ? 1000 * exp : 1000 * 60
  const props = await getGlobalProps()
  const refBlockNum = props.head_block_number & 0xffff
  const refBlockPrefix = Buffer.from(props.head_block_id, 'hex').readUInt32LE(4)
  const expiration = new Date(Date.now() + expireTime)
    .toISOString()
    .slice(0, -5)
  const extensions = []
  return {
    expiration,
    extensions,
    operations,
    ref_block_num: refBlockNum,
    ref_block_prefix: refBlockPrefix
  }
}
*/

Dictionary create_transaction(Array operations, String expr_date) {
	HIVE hive;
	String string;
	Time ticktock;
	
	Array extensions;
	Array signatures;
	Dictionary globals = hive.globals["received"];
	Dictionary gd = globals["result"];
	
	int head_block_number = gd["head_block_number"];
	String head_block_id = gd["head_block_id"];
	float expr_time = 60;
	float added_time = ticktock.get_unix_time_from_system() + expr_time;
	String date = ticktock.get_datetime_string_from_unix_time(added_time);
	String experation;
	//experation = date + expr_time;
	Array p_dhex;
	PackedByteArray dhex;
	if (head_block_id.is_valid_hex_number() == true) {
			int offset;
			int hbi_length = head_block_id.length();
			for(offset = 0;offset < hbi_length -2;offset += 2) {
				String subby = "0x"+head_block_id.substr(offset,2);
				p_dhex.append(subby.hex_to_int());
				}
			PackedByteArray temp(p_dhex);
			dhex = temp;
		}
	
	/*Dictionary transaction;
		transaction["ref_block_num"] = head_block_number & 0xffff;
		transaction["ref_block_prefix"] = dhex.decode_u32(4);
  		transaction["expiration"] = date;
  		transaction["operations"] = operations;
  		transaction["extensions"] = extensions;
  		transaction["signatures"] = signatures;
  		//transaction["globals"] = gd;
	*/
	// Test transactions based on online example
	Dictionary amount;
		amount["amount"] = 8204;
		amount["precusion"] = 3;
		amount["nai"] = "@@000000021";
	
	Dictionary ttvo;
		ttvo["from"] = "alice";
        ttvo["to"] = "bob";
        ttvo["amount"] = amount;
	
	Dictionary test_operation;
         test_operation["type"] = "transfer_to_vesting_operation",
         test_operation["value"] = ttvo;
      
	Array test_operations;
		test_operations.append(test_operation);
	
	Dictionary transaction;
		transaction["ref_block_num"] = 20;
		transaction["ref_block_prefix"] = 2890012981;
		transaction["experation"] = "2018-10-15T19:52:09";
		transaction["operations"] = test_operations;
		transaction["extensions"] = extensions;
		
	
	PackedByteArray seal = serializer(transaction);
	Dictionary test;
	test["serial"] = seal;

return transaction;
}

PackedByteArray serializer(Dictionary transaction) {

	Array opts;
	opts.append(transaction["ref_block_num"]);
	opts.append(transaction["ref_block_prefix"]);
	opts.append(transaction["experation"]);
	opts.append(1);
	opts.append(0);
	opts.append(0);
	opts.append(transaction["extensions"]);
	
	PackedByteArray serialized = opts;
	//serialized.encode_u16(0,transaction["ref_block_num"]);
	
	
	
return serialized;
}



