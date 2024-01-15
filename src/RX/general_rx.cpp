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
	if (output == "history") {
		num = 6;
	}
	if(output == "img") {
		num = 7;
	}

return num;
}

Dictionary get_from_hive(int output,String url, int port, Dictionary fields, bool debug = false) {
	HTTPClient http;
    OS os;
    JSON json;
    Engine engine;

    int error = 0;
    
    Dictionary data;
    data["error"] = "not a valid type";
   	PackedByteArray rb;
    http.set_blocking_mode(false);
    error = http.connect_to_host(url,port);
  
    if (debug == true) {
    	Dictionary dict;
    	dict["errornum"] = error;
    	dict["error"] = "Connecting";
    	dict["connecting_to"] = url;
		data["first step"] = dict;
	}
	
    while (http.get_status() == HTTPClient::STATUS_CONNECTING or http.get_status() == 	HTTPClient::STATUS_RESOLVING) {
		http.poll();
		//engine.get_main_loop();
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
    	Dictionary dict;
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
    		Dictionary dict;
    		dict["errornum"] = bl;
    		dict["error"] = "Repsonse length";
    		dict["connecting_to"] = url;
    		dict["fields"] = headers;
   	    	data["third step"] = dict;
   	    }
   		
   		
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
   		//data["recieved"] = json.parse_string(rb.get_string_from_ascii());
   		//data = rb;
	}
	switch(output) {
		case 1: {
				data["received"] = json.parse_string(rb.get_string_from_ascii());
				Dictionary rec = data["received"];
				if (rec.has("result") == true) {
					Array account = rec["result"];
					return account[0];
				} else {
					return data;
				}
			}
		case 2:{
				data["received"] = json.parse_string(rb.get_string_from_ascii());
				Dictionary rec = data["received"];
				if (rec.has("result") == true) {
					Dictionary history = rec["result"];
					return history;
				} else {
					return data;
				}
			}
		case 3:  
			return data;
		//parse_post(parse_json(text))
		case 4:
			return data;
		//parse_age(parse_json(text))
		
		case 5:
			return data;
		
		case 6:
			return data;
		
		case 7:
			data["received"] = rb;
			return data;
		
		default:
			data["received"] = rb;
			return data;
	};
return data;
}

Dictionary get_from_web(String type,String url, int port, bool debug = false) {
	HTTPClient http;
    OS os;
    JSON json;
    Engine engine;
    
	Dictionary data;
	
	int error = 0;

	String base_dir = url.get_base_dir();
	String file = url.get_file();
	Array split_url = url.split("/");
	String mode = split_url[0];
	String base_url = split_url[2];
	String full_url = mode +"//"+base_url;
	//data["base_url"] = base_url;
	//data["base_dir"] = base_dir;
	String full_path;
	int url_size = split_url.size();
	int i;
	for(i = 3;i < url_size;i++) {
		String t= split_url[i];
		full_path += "/";
		full_path += t;
	}
	data["file name"] = full_path;
	
	PackedByteArray rb;
    http.set_blocking_mode(false);
    error = http.connect_to_host(full_url,port);
    
     if (debug == true) {
    	Dictionary dict;
    	dict["errornum"] = error;
    	dict["error"] = "Connecting";
    	dict["connecting_to"] = full_url;
    	dict["base_dir"] = base_dir;
    	dict["full_path"] = full_path;
    	dict["url_size"] = url_size;
    	
		data["first step"] = dict;
	}
	
	while (http.get_status() == HTTPClient::STATUS_CONNECTING or http.get_status() == HTTPClient::STATUS_RESOLVING) {
		http.poll();

	}
	
	if (debug == true) {
		Dictionary dict;
		dict = data["first step"];
		dict["status"] = http.get_status();
		
		data["first step"] = dict;
	}
	if (http.get_status() == HTTPClient::STATUS_CONNECTED) {
	
		Array headers;
    	headers.append("User-Agent: Pirulo/1.0 (Godot)");
    	headers.append("Accept: */*");
    
    	//String f = json.stringify(fields);
    	error = http.request(HTTPClient::METHOD_GET,full_path,headers);
    
    	if (debug == true) {
    		Dictionary dict;
    		dict["errornum"] = error;
    		dict["error"] = "Requesting";
    		dict["connecting_to"] = url;
    		dict["base"] = base_dir;
    		dict["file"] = full_path;
    	
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
    			Dictionary dict;
    			dict["errornum"] = bl;
    			dict["error"] = "Repsonse length";
    			dict["connecting_to"] = url;
    			dict["fields"] = headers;
   	    		data["third step"] = dict;
   	   	 	}
   		
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
   			data["content-type"] = headers["Content-Type"];
   			data["received"] = rb;
   			//data["text"] = rb.get_string_from_ascii();
   			
		} 
		
	}
	
return data;
}


