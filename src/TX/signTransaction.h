#ifndef HIVE_STX
#define HIVE_STX

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/http_client.hpp>
#include <godot_cpp/classes/http_request.hpp>
#include <godot_cpp/classes/crypto.hpp>
#include <godot_cpp/classes/crypto_key.hpp>
#include <openssl/ssl.h>
#include <godot_cpp/core/class_db.hpp>


using namespace godot;

String create_signature(String private_key, Dictionary data,String chain_id);
bool check_signature(String public_key,Dictionary data);
Dictionary transactionDigest(String transaction,String keys,String chain_id);
String signTransaction(String transaction,String keys,String chain_id);









#endif
