#ifndef CACHE
#define CACHE

#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/json.hpp>
#include <godot_cpp/classes/dir_access.hpp>
#include <godot_cpp/classes/file_access.hpp>

#include <godot_cpp/core/class_db.hpp>
using namespace godot;

int create_cache(int type);
Dictionary to_cache(int type,Dictionary data);
Dictionary from_cache(int type,Array data);
Dictionary check_cache(int type,Array data);
int clear_cache(int type, int age);

#endif
