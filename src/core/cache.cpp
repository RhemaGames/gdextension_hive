#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/json.hpp>

#include <godot_cpp/core/class_db.hpp>
using namespace godot;

#include "cache.h"


// Creates cache if not avaiable

int create_cache(int type) { 
	int error = 0;
	OS os;
	String cache_dir = os.get_cache_dir();
	DirAccess dir;

	// We need to first check if directories exist. If not then we create. We'll have a check_cache function to query 	
	switch(type) {
		case 1: // blog
			break;	
		case 2: {// profile
			String full_path = cache_dir+"/hive/profile";
			error = dir.make_dir_absolute(full_path);
			break;
			}
		case 3: //history
			break;		
	
	}
	
return error;
}

Dictionary check_cache(int type, Array data) {
	Dictionary error;
	OS os;
	String cache_dir = os.get_cache_dir();
	String cache_path;
	DirAccess dir;
	FileAccess file;
	if(type == 2) {
		if (dir.dir_exists_absolute(cache_dir+"/hive/profile") == true) {
			cache_path = cache_dir+"/hive/profile";
			} else {
				if (create_cache(type) == 0) {
					cache_path = cache_dir+"/hive/profile";
				} else {
						cache_path = "error";
					}
				}
		if (cache_path != "error") {
			String file_path;
			if (data[0]) {
				String cp = cache_path+"/";
				String dat = data[0];
				file_path = cp+dat;
				error["filename"] = file_path;
				
			} else {
				error["error"] = "No file name";
				return error;
			}	
				error["cached"] = file.file_exists(file_path);
		}
	}
	error["cache dir"] = cache_path;
return error;
}

Dictionary to_cache(int type, Dictionary data) {
	Dictionary error;
	error["recieved"] = "error";

return error;
}

Dictionary from_cache(int type, Array data) {
	Dictionary error;
	error["recieved"] = "error";

return error;
}




int clear_cache(int type, int age) {


return 1;
}
