#include "hive.h"
#include <string>
#include <iostream>
using namespace std;

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void HIVE::_bind_methods() {
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

int HIVE::post(string data) {
	cout << data;
return 1;
}

void HIVE_WALLET::_bind_methods() {
}

HIVE_WALLET::HIVE_WALLET() {
	time_passed = 0.0;
}

HIVE_WALLET::~HIVE_WALLET() {
}

void HIVE_WALLET::_process(double delta) {
	time_passed += delta;
}

string HIVE_WALLET::get_private_key(int type = 0) {
	string key = "No Key";
	
	switch(type) {
		case 0:
			key = HIVE_WALLET::private_key.posting;
			break;
		case 1:
			key = HIVE_WALLET::private_key.posting;
			break;
		case 2:
			key = HIVE_WALLET::private_key.memo;
			break;
	}
return key;
}
