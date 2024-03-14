
#include "createTransaction.h"
#include "../hive.h"
#include "hive_operations.h"
#include "signTransaction.h"

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
		ttvo["author"] = "xeroc";
        ttvo["permlink"] = "piston";
        ttvo["voter"] = "xeroc";
        ttvo["weight"] = 10000;	
       // ttvo["amount"] = amount;
	
	Array test_operation;
         test_operation.append("vote"),
         test_operation.append(ttvo);
      
	Array test_operations;
		test_operations.append(test_operation);
		//test_operations.append(test_operation);
	
	Dictionary transaction;
		transaction["ref_block_num"] = 61828;
		transaction["ref_block_prefix"] = 3564338418;
		transaction["experation"] = "2016-08-09T10:06:15";
		transaction["operations"] = test_operations;
		transaction["extensions"] = extensions;
	
	String chainId;
        for (int i = 0; i < 256/4; i++) {
            chainId += "0";
        }
	
	Array wifs;
	wifs.append("5JRaypasxMx1L97ZUX7YuC5Psb5EAbF821kkAGtBj7xCJFQcbLg");
	String privatekey;
	for (int i = 0;i < wifs.size(); i++) {
	    privatekey += wif_decode(wifs[0]);
	}
	
	String seal = serializer(transaction);
	Dictionary container;
	container["serialized"] = seal;
	container["digest"] = transactionDigest(seal,chainId);
	container["privatekey"] = privatekey;
	transaction["signatures"] = container;

return transaction;
}

String serializer(Dictionary transaction) {

	String serialized;
	
	// Ref block Num
	String rbf;
	rbf = String().num_uint64(transaction["ref_block_num"],16,false);
	serialized += reendian(rbf);
	
	// Ref block prefix
	String rbp;
	rbp = String().num_uint64(transaction["ref_block_prefix"],16,false);
	serialized += reendian(rbp);
	
	// Experation Date
	
	Time expr;
	int to_number = expr.get_unix_time_from_datetime_string(transaction["experation"]);
	String ed;
	ed = String().num_uint64(to_number,16,false);
	serialized += reendian(ed);
	
	// Operations
	int num_of_operations;
		num_of_operations = Array(transaction["operations"]).size();
	String hexed_num_of_operations;
		hexed_num_of_operations = String().num_uint64(num_of_operations,16,false).pad_zeros(2);
	serialized +=hexed_num_of_operations;
	// - Operation id
	String opt_type = Array(Array(transaction["operations"])[0])[0];
	int opt = get_operation(opt_type);
	serialized += String().num_uint64(opt,16,false).pad_zeros(2);
	Dictionary ope = Array(Array(transaction["operations"])[0])[1];			
	serialized += vote_serialized(ope);
	
	int num_of_exten;
	 num_of_exten = Array(transaction["extensions"]).size();
	String hex_num_of_exten;
	hex_num_of_exten = String().num_uint64(num_of_exten,16,false).pad_zeros(2);
	serialized += hex_num_of_exten;
	/*
	//PackedByteArray serialized = opts;
	//serialized.encode_u16(0,transaction["ref_block_num"]);
	*/
	
	
return serialized;
}


