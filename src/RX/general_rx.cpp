#include "general_rx.h"

//#include "wallet/wallet.h"
#include <godot_cpp/core/class_db.hpp>
using namespace godot;

int enumerate_output(String output) {
	int num = -1;
	if (output == "userinfo") /*== true)*/ {
		num = 1;
	}
	if (output == "blog") /* == true) */ {
		num = 2;
	}
	if (output.match("post") == true) {
		num = 3;
	}
	if (output.match("age") == true) {
		num = 4;
	}
	if (output.match("auth") == true) {
		num = 5;
	}

return num;
}

Dictionary get_from_hive(int output,String url, int port, Dictionary fields, bool debug = false) {
	HTTPClient http;
    OS os;
    JSON json;
    Engine engine;

	//String url = "https://api.hive.blog";
    int error = 0;
    Dictionary dict;
    Dictionary data;
    data["error"] = "not a valid type";
    //emit_signal("error",0,data);
   
    http.set_blocking_mode(false);
    error = http.connect_to_host(url,port);
    dict.clear();
    
    
    if (debug == true) {
    	dict["errornum"] = error;
    	dict["error"] = "Connecting";
    	dict["connecting_to"] = url;
   		//emit_signal("error",1,dict);
		data["first step"] = dict;
	}
	
    while (http.get_status() == HTTPClient::STATUS_CONNECTING or http.get_status() == 	HTTPClient::STATUS_RESOLVING) {
		http.poll();
		//if (os.has_feature("web") != true) {
		//	os.delay_msec(500);
		//} else {
			//await(engine.get_main_loop(), "idle_frame");
		//}
	}
    Array headers;
    headers.append("User-Agent: Pirulo/1.0 (Godot)");
    headers.append("Accept: */*");
    
    String f = json.stringify(fields);
    error = http.request(HTTPClient::METHOD_POST,"/",headers,f);
    
    
    if (debug == true) {
    	dict["errornum"] = error;
    	dict["error"] = "request";
    	dict["connecting_to"] = url;
    	dict["fields"] = f;
    	data["second step"] = dict;
    }
    
    while (http.get_status() == HTTPClient::STATUS_REQUESTING) {
        // Keep polling for as long as the request is being processed.
		http.poll();
	}
    if (http.has_response() == true) {
    	int bl = http.get_response_body_length();
    	Dictionary headers = http.get_response_headers_as_dictionary();
    	
    	if (debug == true) {
    		dict["errornum"] = bl;
    		dict["error"] = "Repsonse length";
    		dict["connecting_to"] = url;
    		dict["fields"] = headers;
   		//	emit_signal("error",4,dict);
   	    	data["third step"] = dict;
   	    }
   		PackedByteArray rb;
   		
   		while (http.get_status() == HTTPClient::STATUS_BODY) {
            // While there is body left to be read
			http.poll();
			PackedByteArray chunk;
			chunk = http.read_response_body_chunk(); // Get a chunk.
			if (chunk.size() == 0) {
                // Got nothing, wait for buffers to fill a bit.
				os.delay_usec(100);
			} else {
				rb = rb + chunk; // Append to read buffer.
   			}
   		}
   		data.clear();
   		data["recieved"] = json.parse_string(rb.get_string_from_ascii());
	}
	switch(output) {
		case 1: 
			return data;
			//parse_userinfo(parse_json(text))
		case 2:
			return data;
			//parse_blog(parse_json(text))
		case 3:  
			return data;
		//parse_post(parse_json(text))
		case 4:
			return data;
		//parse_age(parse_json(text))
		
		case 5:
			return data;
			
		default:
			return data;
	};
return data;
}
