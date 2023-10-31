#ifndef HIVE_H
#define HIVE_H

#include <iostream>
#include <string>
using namespace std;

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/http_client.hpp>
#include <godot_cpp/classes/http_request.hpp>
#include <godot_cpp/classes/crypto.hpp>
#include <godot_cpp/classes/crypto_key.hpp>

// Transaction headers for sending data to the chain.
#include "TX/signTransaction.h"
#include "TX/broadcastTransaction.h"
#include "TX/createTransaction.h"

// Receieve header for retrieveing and processing data from the chain.

//TBR

// Wallet headers for storing, retrieving and securing keys and other "owned" items from the chain

#include "wallet/wallet.h"


namespace godot {

	class HIVE:public Node {
		GDCLASS(HIVE,Node)

		private:
			double time_passed;
			
			
		protected:
			static void _bind_methods();

		public:
			HIVE();
			~HIVE();

			void _process(double delta);
			int post(string data);
			
		};
	class HIVE_WALLET:public HIVE {
		GDCLASS(HIVE_WALLET,HIVE)

		private:
			double time_passed;
			struct {
				string posting;
				string active;
				string memo;
			} private_key;

		protected:
			static void _bind_methods();

		public:
			HIVE_WALLET();
			~HIVE_WALLET();

			void _process(double delta);
			string get_private_key(int type);
			bool set_private_key(int type,string key);
		};
}

#endif
