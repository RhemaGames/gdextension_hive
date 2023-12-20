#ifndef WALLET_H
#define WALLET_H

#include <iostream>
#include <string>
//using namespace std;

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/http_client.hpp>
#include <godot_cpp/classes/http_request.hpp>
#include <godot_cpp/classes/crypto.hpp>
#include <godot_cpp/classes/crypto_key.hpp>

#include <godot_cpp/core/class_db.hpp>


namespace hive_wallet {

	class HW {	
		private:
			double time_passed;
			struct {
				String posting;
				String active;
				String memo;
			} private_key;
			
			
		protected:
			static void _bind_methods();

		public:
			//HIVE_WALLET();
			//~HIVE_WALLET();
			
			//void _process(double delta);
			std::string hive_wallet_get_private_key(int type = 0);
			bool hive_wallet_set_private_key(String key, String type = "posting");
	};

}

#endif
