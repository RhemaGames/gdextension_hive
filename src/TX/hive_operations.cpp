#include "./hive_operations.h"

#include <godot_cpp/core/class_db.hpp>
using namespace godot;



int get_operation(String t) {
	String type = t.to_upper();
	if (type == "VOTE" ) { // 0
		return 0;
	}		
    if (type == "COMMENT" ) { // 1
		return 0;
	}	
    if (type == "TRANSFER" ) { // 2
    	return 2;
	}	
    if (type == "TRANSFER_TO_VESTING" ) { // 3
    	return 3;
	}	
    if (type == "WITHDRAW_VESTING" ) { // 4
    	return 4;
	}	

    if (type == "LIMIT_ORDER_CREATE" ) { // 5
    	return 5;
	}	
    if (type == "LIMIT_ORDER_CANCEL" ) { // 6
    	return 6;
	}	

    if (type == "FEED_PUBLISH" ) { // 7
    	return 7;
	}	
    if (type == "CONVERT" ) { // 8
    	return 8;
	}	

    if (type == "ACCOUNT_CREATE" ) { // 9
    	return 9;
	}	
    if (type == "ACCOUNT_UPDATE" ) { // 10
    	return 10;
	}	

   if (type == "WITNESS_UPDATE" ) { // 11
   	return 11;
	}	
   if (type == "ACCOUNT_WITNESS_VOTE" ) { // 12
   	return 12;
	}	
   if (type == "ACCOUNT_WITNESS_PROXY" ) { // 13
   	return 13;
	}	

   if (type == "POW" ) { // 14
   	return 14;
	}	

    if (type == "CUSTOM" ) { // 15
    	return 15;
	}	

    if (type == "WITNESS_BLOCK_APPROVE" ) { // 16
    	return 16;
	}	

    if (type == "DELETE_COMMENT" ) { // 17
    	return 17;
	}	
    if (type == "CUSTOM_JSON" ) { // 18
    	return 18;
	}	
    if (type == "COMMENT_OPTIONS" ) { // 19
    	return 19;
	}	
    if (type == "SET_WITHDRAW_VESTING_ROUTE" ) { // 20
    	return 20;
	}	
    if (type == "LIMIT_ORDER_CREATE2" ) { // 21
    	return 21;
	}	
    if (type == "CLAIM_ACCOUNT" ) { // 22
    	return 22;
	}	
    if (type == "CREATE_CLAIMED_ACCOUNT" ) { // 23
    	return 23;
	}	
    if (type == "REQUEST_ACCOUNT_RECOVERY" ) { // 24
    	return 24;
	}	
   if (type == "RECOVER_ACCOUNT" ) { // 25
   	return 25;
	}	
    if (type == "CHANGE_RECOVERY_ACCOUNT" ) { // 26
    	return 26;
	}	
    if (type == "ESCROW_TRANSFER" ) { // 27
    	return 27;
	}	
    if (type == "ESCROW_DISPUTE" ) { // 28
    	return 28;
	}	
    if (type == "ESCROW_RELEASE" ) { // 29
    	return 29;
	}	
    if (type == "POW2" ) { // 30
    	return 30;
	}	
    if (type == "ESCROW_APPROVE" ) { // 31
    	return 31;
	}	
    if (type == "TRANSFER_TO_SAVINGS" ) { // 32
    	return 32;
	}	
    if (type == "TRANSFER_FROM_SAVINGS" ) { // 33
    	return 33;
	}	
    if (type == "CANCEL_TRANSFER_FROM_SAVINGS" ) { // 34
    	return 34;
	}	
    if (type == "CUSTOM_BINARY" ) { // 35
    	return 35;
	}	
    if (type == "DECLINE_VOTING_RIGHTS" ) { // 36
    	return 36;
	}	
    if (type == "RESET_ACCOUNT" ) { // 37
    	return 37;
	}	
    if (type == "SET_RESET_ACCOUNT" ) { // 38
    	return 38;
	}	
    if (type == "CLAIM_REWARD_BALANCE" ) { // 39
    	return 39;
	}	
    if (type == "DELEGATE_VESTING_SHARES" ) { // 40
    	return 40;
	}	
    if (type == "ACCOUNT_CREATE_WITH_DELEGATION" ) { // 41
    	return 41;
	}	
    if (type == "WITNESS_SET_PROPERTIES" ) { // 42
    	return 42;
	}	
    if (type == "ACCOUNT_UPDATE2" ) { // 43
    	return 43;
	}	
    if (type == "CREATE_PROPOSAL" ) { // 44
    	return 44;
	}	
    if (type == "UPDATE_PROPOSAL_VOTES" ) { // 45
    	return 45;
	}	
    if (type == "REMOVE_PROPOSAL" ) { // 46
    	return 46;
	}	
    if (type == "UPDATE_PROPOSAL" ) { // 47
    	return 47;
	}	
    if (type == "COLLATERALIZED_CONVERT" ) { // 48
    	return 48;
	}	
    if (type == "RECURRENT_TRANSFER" ) { // 49
    	return 49;
	}	
return -1;	
}


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

String vote_serialized(Dictionary operation) {
	String serialized;
	
	String voter = operation["voter"];
	String voter_length =  String().num_uint64(voter.length(),16,false).pad_zeros(2);
	serialized +=voter_length;
	serialized += voter.to_utf8_buffer().hex_encode();
	
	String author = operation["author"];
	String author_length =  String().num_uint64(author.length(),16,false).pad_zeros(2);
	serialized += author_length;
	serialized += author.to_utf8_buffer().hex_encode();
	
	String permlink = operation["permlink"];
	String permlink_length =  String().num_uint64(permlink.length(),16,false).pad_zeros(2);
	serialized += permlink_length;
	serialized += permlink.to_utf8_buffer().hex_encode();
	
	short weight = operation["weight"];

	serialized += reendian(String().num_int64(weight,16,false));


return serialized; 
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


String reendian(String hex) {
	Array p_dhex;
	String dhex;
	if (hex.is_valid_hex_number() == true) {
			int offset;
			int hex_length = hex.length();
			for(offset = 0;offset < hex_length ;offset += 2) {
				String subby = hex.substr(offset,2);
				p_dhex.append(subby);
				}
			int i;
			p_dhex.reverse();
			for(i = 0;i < p_dhex.size(); i++) {
				dhex += String(p_dhex[i]);
			}
	}
return dhex;

}
