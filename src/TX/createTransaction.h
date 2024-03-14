#ifndef HIVE_CTX
#define HIVE_CTX

#include "../hive.h"
#include "hive_operations.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/http_client.hpp>
#include <godot_cpp/classes/http_request.hpp>
#include <godot_cpp/classes/crypto.hpp>
#include <godot_cpp/classes/crypto_key.hpp>
#include <godot_cpp/classes/time.hpp>
#include <sys/time.h>

#include <godot_cpp/core/class_db.hpp>
using namespace godot;

//#include <openssl/ssl.h>


Dictionary create_transaction(Array operations,String expr_date);
String serializer(Dictionary transaction);









#endif
