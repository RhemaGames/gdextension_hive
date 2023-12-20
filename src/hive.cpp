#include "hive.h"
#include <string>
#include "wallet/wallet.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void HIVE::_bind_methods() {
	ClassDB::bind_method(D_METHOD("post","data"), &HIVE::post);
	ClassDB::bind_method(D_METHOD("authenticate","account","key"), &HIVE::authenticate);
	ClassDB::bind_method(D_METHOD("get_post_history","account","count"), &HIVE::get_post_history);
	ClassDB::bind_method(D_METHOD("get_post","account","url"), &HIVE::get_post);
	
	ADD_SIGNAL(MethodInfo("recieved_post_history",PropertyInfo(Variant::STRING, "json")));
	ADD_SIGNAL(MethodInfo("recieved_post",PropertyInfo(Variant::STRING, "json")));
	ADD_SIGNAL(MethodInfo("published",PropertyInfo(Variant::STRING, "postId"), PropertyInfo(Variant::DICTIONARY, "data")));
	ADD_SIGNAL(MethodInfo("error",PropertyInfo(Variant::INT, "type"), PropertyInfo(Variant::DICTIONARY, "data")));
	
}

HIVE::HIVE() {
	// Initialize any variables here.
	time_passed = 0.0;
}

HIVE::~HIVE() {
	//Add clean up here
}

void HIVE::_process(double delta) {
	time_passed += delta;
}

int HIVE::post(String data) {
	//data = {"post":"tests"};
	emit_signal("published","test_post",data);	
return 1;
}

int HIVE::authenticate(String account,String private_key) {

return 1;
}

void HIVE::get_post_history(String account,int count) {

}

void HIVE::get_post(String account,String url) {

}



void HIVE_WALLET::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_private_key","type"), &HIVE_WALLET::get_private_key);
	ClassDB::bind_method(D_METHOD("get_wallet_info","account"), &HIVE_WALLET::get_wallet_info);
	ClassDB::bind_method(D_METHOD("get_transfers","account","count"), &HIVE_WALLET::get_transfers);
	ClassDB::bind_method(D_METHOD("get_memos","account","count"), &HIVE_WALLET::get_memos);
	//ClassDB::bind_method(D_METHOD("set_private_key", "key","type"), &HIVE_WALLET::set_private_key);
	//ClassDB::add_property("HIVE_WALLET", PropertyInfo(Variant::FLOAT,"something"), "get_private_key");
	ADD_SIGNAL(MethodInfo("rewards_available", PropertyInfo(Variant::STRING, "type"), PropertyInfo(Variant::FLOAT, "amount")));
	ADD_SIGNAL(MethodInfo("transfer_sent", PropertyInfo(Variant::STRING, "account"), PropertyInfo(Variant::FLOAT, "amount")));
	ADD_SIGNAL(MethodInfo("transfer_recieved", PropertyInfo(Variant::STRING, "account"), PropertyInfo(Variant::FLOAT, "amount")));
	ADD_SIGNAL(MethodInfo("account_info", PropertyInfo(Variant::STRING, "account"), PropertyInfo(Variant::DICTIONARY, "data")));
}

HIVE_WALLET::HIVE_WALLET() {
	time_passed = 0.0;
}

HIVE_WALLET::~HIVE_WALLET() {
}

void HIVE_WALLET::_process(double delta) {
	time_passed += delta;
}

String HIVE_WALLET::get_private_key(int type) {
	String key = "No Key";
	
	switch(type) {
		case 0:
			key = HIVE_WALLET::private_posting_key;
			break;
		case 1:
			key = HIVE_WALLET::private_active_key;
			break;
		case 2:
			key = HIVE_WALLET::private_memo_key;
			break;
	}
return key;
} 

String HIVE_WALLET::get_wallet_info(String account) {

}

String HIVE_WALLET::get_transfers(String account, int count) {

}


String HIVE_WALLET::get_memos(String account, int count) {

}
