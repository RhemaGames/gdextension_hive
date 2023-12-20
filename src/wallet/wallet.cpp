#include "wallet.h"
#include <string>
using namespace std;

#include <godot_cpp/core/class_db.hpp>


int HW::does_wallet_exist(account) {

return 0;
}

string HW::hive_wallet_get_private_key(int type = 0) {
	String key = "No Key";
	
	switch(type) {
		case 0:
			key = "TESTING RETURN";
			//key = private_key.posting;
			break;
		case 1:
			key = private_key.posting;
			break;
		case 2:
			key = private_key.memo;
			break;
	}
return key;
}

bool HW::set_private_key(String key, String type = "posting") {

return true;
}
