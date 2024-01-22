#include <godot_cpp/core/class_db.hpp>
using namespace godot;

Dictionary vote(String account,String author, String permlink, int weight) {

	Dictionary transaction;
	Dictionary data1;
		data1["voter"] = account;
		data1["author"] = author;
		data1["permlink"] = permlink;
		data1["weight"] = weight;

	transaction["vote"] = data1;

return transaction;
}

Dictionary vote2(String account,String author, String permlink, int weight) {

	Dictionary transaction;
	
	Dictionary data1;
		data1["voter"] = account;
		data1["author"] = author;
		data1["permlink"] = permlink;
		data1["weight"] = weight;

	transaction["vote"] = data1;
	
	
return transaction;
}

/*    parent_author - the author that comment is being submitted to, when posting a new blog this is an empty string
    parent_permlink - specific post that comment is being submitted to, when posting a new blog this is an empty string
    author - author of the post/comment being submitted (account name)
    permlink - unique string identifier for the post, linked to the author of the post
    title - human readable title of the post being submitted, this is often blank when commenting
    body - body of the post/comment being submitted, or diff-match-patch when updating
    json_metadata - JSON object string

Rules:

    The “title” must not be longer than 256 bytes
    The “title” must be UTF-8
    The “body” must be larger than 0 bytes
    The “body” much also be UTF-8

Additional Parameter Definitions:

    permlink - Two authors may have the same permlink as it’s unique to the author only. For example, there could be two authors, alice and bob, and both could have a permlink of firstpost
    json_metadata - There is no blockchain enforced validation on json_metadata, but the community has adopted a particular structure. It should contain a JSON object with the following keys:
        tags - An array of up to 5 strings. Although the blockchain will accept more than 5, the tags plugin only looks at the first five
        app - A user agent style application identifier. Typically app_name/version, e.g. hiveblog/0.1
        format - The format of the body, e.g. markdown
        In addition to the above keys, application developers are free to add any other keys they want to help manage the content they broadcast.
*/


Dictionary comment(String parent_author, String parent_permlink, String author, String permlink, String title, String body, Dictionary json_metadata) {

	Dictionary transaction;
	//Dictionary json_metadata;
	
	Dictionary data1;
		data1["parent_author"] = parent_author;
		data1["parent_permlink"] = parent_permlink;
		data1["author"] = author;
		data1["permlink"] = permlink;
		data1["title"] = title;
		data1["body"] = body;
		data1["json_metadata"] = json_metadata;
	
	transaction["comment"] = data1;


return transaction;
} 


/* Serves the same purpose as custom but also supports required posting authorities. Unlike custom, this operation is designed to be human readable/developer friendly.
follow

As of HF9, the follow plugin will track follow/unfollow/ignore events.
reblog

As of HF14, allows users to share blogs they find with those who follow them. This change implemented entirely outside the blockchain consensus which means that reblogging does not create a new post, it merely shares an existing post with people who follow you.
witness

As of HF18, the witness plugin has a custom operation called enable_content_editing that allows a user to signal they want to edit their content. By consensus, content is editable indefinitely, but is soft forked to be frozen after payout. This operation requires an active key and is designed to prevent vandalism if a posting key is compromised. #1017
Roles: posting active owner
Parameters: required_auths required_posting_auths id json
*/

Dictionary custom_json(Array required_auths, String reqired_posting_auths, String id, Dictionary json) {

	Dictionary transaction;



return transaction;
} 

Dictionary custom(Array required_auths,int id,String data) {
	Dictionary transaction;
	Dictionary data1;
		data1["required_auths"] = required_auths;
		data1["id"] = id;
		data1["data"] = data;

  transaction["custom"] =  data1;
  
return transaction;
}
