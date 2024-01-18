#include "hive.h"
#include "RX/general_rx.h"
#include "core/cache.h"
#include "TX/signTransaction.h"
//#include "wallet/wallet.h"
#include <godot_cpp/core/class_db.hpp>
using namespace godot;

void HIVE::_bind_methods() {

	ClassDB::bind_method(D_METHOD("init"), &HIVE::init);
	ClassDB::bind_method(D_METHOD("post","data"), &HIVE::post);
	ClassDB::bind_method(D_METHOD("authenticate","account","key"), &HIVE::authenticate);
	ClassDB::bind_method(D_METHOD("get_blog_history","account","start","count"), &HIVE::get_blog_history);
	ClassDB::bind_method(D_METHOD("get_blog_entry","account","post","use_cache"), &HIVE::get_blog_entry);
	ClassDB::bind_method(D_METHOD("get_profile","account","use_cache"), &HIVE::get_profile);
	ClassDB::bind_method(D_METHOD("get_history","account","start","count","use_cache"), &HIVE::get_history);
	ClassDB::bind_method(D_METHOD("get_img","type","url","obj","use_cache"), &HIVE::get_img);
	
	ClassDB::bind_method(D_METHOD("set_hive_node","node"), &HIVE::set_hive_node);
	ClassDB::bind_method(D_METHOD("get_hive_node"), &HIVE::get_hive_node);
	ClassDB::bind_method(D_METHOD("get_dynamic_globals"), &HIVE::get_globals);
	
	ADD_SIGNAL(MethodInfo("received_profile",PropertyInfo(Variant::STRING, "json")));
	ADD_SIGNAL(MethodInfo("received_history",PropertyInfo(Variant::STRING, "json")));
	ADD_SIGNAL(MethodInfo("received_blog_history",PropertyInfo(Variant::STRING, "json")));
	ADD_SIGNAL(MethodInfo("received_blog_entry",PropertyInfo(Variant::STRING, "json")));
	ADD_SIGNAL(MethodInfo("received_img",PropertyInfo(Variant::DICTIONARY,"data")));
	ADD_SIGNAL(MethodInfo("tick", PropertyInfo(Variant::FLOAT,"time_passed")));
	
	ADD_SIGNAL(MethodInfo("published",PropertyInfo(Variant::STRING, "postId"), PropertyInfo(Variant::DICTIONARY, "data")));
	ADD_SIGNAL(MethodInfo("error",PropertyInfo(Variant::INT, "type"), PropertyInfo(Variant::DICTIONARY, "data")));
	
	ClassDB::add_property("HIVE", PropertyInfo(Variant::STRING, "hive_node", PROPERTY_HINT_TYPE_STRING, "https://api.hive.blog"), "set_hive_node", "get_hive_node");
	ClassDB::add_property("hive_dynamic_globals",PropertyInfo(Variant::DICTIONARY, "globals"),"get_dynamic_globals","");
}

HIVE::HIVE() {
	// Initialize any variables here.
	time_passed = 0.0;
	hive_node = "https://api.hive.blog";
  	chain_id = "beeab0de00000000000000000000000000000000000000000000000000000000";
  	address_prefix = "STM";
  	globals = get_globals();
}

HIVE::~HIVE() {
	//Add clean up here
}

void HIVE::_process(double delta) {
	time_passed += delta;
	emit_signal("tick",time_passed);
}

Dictionary HIVE::init() {
globals = get_globals();
return globals;
}

Dictionary HIVE::get_globals() {
    Array params;

    Dictionary fields;
   	fields["jsonrpc"] ="2.0";
    fields["method"] = "condenser_api.get_dynamic_global_properties";
    fields["params"] = params;
    fields["id"] = 1;

    Dictionary results;
    results = get_from_hive(20,hive_node,443,fields,false);
    
return results;
}


int HIVE::post(String data) {
	//data = {"post":"tests"};
	emit_signal("published","test_post",data);	
return 1;
}

int HIVE::authenticate(String account,String private_key) {

return 1;
}

int HIVE::get_blog_entry(String account,int post, bool cache) {
	int error = 0;
    Array params;
    params.append(account);
    params.append(post);
    params.append(1);
    
    Dictionary fields;
   	fields["jsonrpc"] ="2.0";
    fields["method"] = "condenser_api.get_blog";
    fields["params"] = params;
    fields["id"] = 1;
	if (hive_node == "") {
		error = 1;
		}
	Dictionary data = get_from_hive(3,hive_node,443,fields,false);
	emit_signal("received_blog_entry",data);

return error;
}

int HIVE::get_blog_history(String account,int start,int count) {

	int error = 0;
    Array params;
    params.append(account);
    params.append(start);
    params.append(count);
    
    Dictionary fields;
   	fields["jsonrpc"] ="2.0";
    fields["method"] = "condenser_api.get_blog_entries";
    fields["params"] = params;
    fields["id"] = 1;
	if (hive_node == "") {
		error = 1;
		}
	Dictionary data = get_from_hive(6,hive_node,443,fields,false);
	emit_signal("received_blog_history",data);

return error;
}

Dictionary HIVE::get_profile(String account,bool cache) {
	Dictionary error;
	error["error"] = 0;
	Array enclosure;
    Array params;
    params.append(account);
    enclosure.append(params);
    
    Dictionary fields;
   	fields["jsonrpc"] ="2.0";
    fields["method"] = "condenser_api.get_accounts";
    fields["params"] = enclosure;
    fields["id"] = 1;
	if (hive_node == "") {
		error["error"] = 1;
		}
	if (cache == true) {
		Array test;
		test.append(account);
		error["from cache"] = check_cache(2,test);
	}
	Dictionary data = get_from_hive(1,hive_node,443,fields,false);
	//error["fields"] = fields;
	//error["returned"] = data;
	emit_signal("received_profile",data);
	
return error;
}

int HIVE::get_history(String account,int start,int count,bool cache) {

	int error = 0;
	//Array enclosure;
    Dictionary params;
    params["account"] = account;
    params["start"] = start;
    params["limit"] = count;
   // enclosure.append(params);
    
    Dictionary fields;
   	fields["jsonrpc"] ="2.0";
    fields["method"] = "account_history_api.get_account_history";
    fields["params"] = params;
    fields["id"] = 1;
	if (hive_node == "") {
		error = 1;
		}
	Dictionary data = get_from_hive(2,hive_node,443,fields,false);
	emit_signal("received_history",data);

return error;
}

Dictionary HIVE::get_img(String type,String url,String obj, bool cache) {
	Dictionary fields;
	Dictionary data;
	Dictionary da = get_from_web(type,url,443,false);
	Image img;
	if (da["content-type"] == "image/png") {
		img.load_png_from_buffer(da["received"]);
	}	
	if (da["content-type"] == "image/jpeg" or da["content-type"] == "image/jpeg") {
		img.load_jpg_from_buffer(da["received"]);
	}	
	if (da["content-type"] == "image/webp") {
		img.load_webp_from_buffer(da["received"]);
	}
	
	data["content-type"] = da["content-type"];
	data["received"] = &img;
	data["type"] = type;
	data["obj"] = obj;
	emit_signal("received_img",data);
	
return data;
}


void HIVE::set_hive_node(String p_hive_node) {
	hive_node = p_hive_node;
}

String HIVE::get_hive_node() {
	return hive_node;
}


void HIVE_WALLET::_bind_methods() {
	
	// RX functions
	ClassDB::bind_method(D_METHOD("get_private_key","type"), &HIVE_WALLET::get_private_key);
	ClassDB::bind_method(D_METHOD("get_wallet_info","account"), &HIVE_WALLET::get_wallet_info);
	ClassDB::bind_method(D_METHOD("get_transfers","account","count"), &HIVE_WALLET::get_transfers);
	ClassDB::bind_method(D_METHOD("get_memos","account","count"), &HIVE_WALLET::get_memos);
	
	
	//Lib Functions - remove after testing;!!!
	ClassDB::bind_method(D_METHOD("sign","private_key","data"), &HIVE_WALLET::sign);
	ClassDB::bind_method(D_METHOD("signature_check","private_key","data"), &HIVE_WALLET::signature_check);
	
	// TX Functions 
	
	
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
	String data = "not working yet";

return data;
}

String HIVE_WALLET::get_transfers(String account, int count) {
	String data = "not working yet";

return data;
}

String HIVE_WALLET::get_memos(String account, int count) {

	String data = "not working yet";

return data;
}

String HIVE_WALLET::sign(String private_key,Dictionary data) {
	String info;
	info = create_signature(private_key,data,chain_id);

return info;
}


bool HIVE_WALLET::signature_check(String public_key,Dictionary data) {
	bool info;
	info = check_signature(public_key,data);
	
return info;
}
