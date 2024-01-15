#ifndef GENERAL_RX
#define GENERAL_RX

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/http_client.hpp>
#include <godot_cpp/classes/http_request.hpp>
#include <godot_cpp/classes/crypto.hpp>
#include <godot_cpp/classes/crypto_key.hpp>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/json.hpp>
#include <godot_cpp/classes/engine.hpp>
//#include <godot_cpp/core/class_db.hpp>
//using namespace godot;


godot::Dictionary get_from_hive(int output,godot::String url, int port, godot::Dictionary fields, bool debug);

godot::Dictionary get_from_web(godot::String type, godot::String url, int port, bool debug);


#endif
