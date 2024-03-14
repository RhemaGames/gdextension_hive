#include "signTransaction.h"

#include <godot_cpp/godot.hpp>
#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/class_db.hpp>
#include "../hive.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <secp256k1.h>

using namespace godot;


bool check_signature(String public_key,Dictionary data) {


return true;

}


String create_signature(String private_key,Dictionary data,String chain_id) {
	String signature = chain_id;
	String utf8_buffer = signature.to_utf8_buffer().hex_encode();
	
	
return utf8_buffer;
}

Dictionary transactionDigest(String transaction,String chain_id) {
    Dictionary data;
	String part1;
	String txID;
	part1 = chain_id+transaction;
	txID = transaction.sha256_text().substr(0,40);
	String digest;
	digest = part1.sha256_text();
    data["txid"] = txID;
    data["digest"] = digest;
	
return data;
}

String signTransaction(String transaction, String keys,String chain_id) {
	String signedTransaction;
	Dictionary tD;
	//tD = transactionDigest(transaction,chain_id);
 
return signedTransaction;
}

String wif_decode(String wif) {
    String data;
    CharString b58;
    b58 = b58decode(wif,1).utf8().get_data();
    data = String(b58);
    
    UtilityFunctions::print("BFN Multiply TEST 1-1:",bfn_multiplication("9","9"));
    UtilityFunctions::print("BFN Multiply TEST 1-2:",bfn_multiplication("9","99"));
    UtilityFunctions::print("BFN Multiply TEST 2-1:",bfn_multiplication("99","9"));
   // UtilityFunctions::print("BFN Multiply TEST 2-2:",bfn_multiplication("22","22"));
    UtilityFunctions::print("BFN Multiply TEST 2-2:",bfn_multiplication("33","33"));
    //UtilityFunctions::print("BFN Multiply TEST 2-2:",bfn_multiplication("66","66"));
    //UtilityFunctions::print("BFN POW TEST: ",bfn_POW("58","6"));
    UtilityFunctions::print("wiffer: ", data);
return String(data);
}


String b58decode(String b58,int return_type) {
    Array bytecodes;
    String data = b58encode("BenjaminFlanagin");
    //String data = b58;
    String alph = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
    PackedByteArray bytearray = data.to_utf8_buffer();
    String reverse_it = data.reverse();
    Array core_array = reverse_it.split();
    Array to_array;
    
    UtilityFunctions::print("array size: ",core_array.size());
    
    for(int i = 0;i < core_array.size();i++) { 
        to_array.append(alph.find(core_array[i]));
    }
    
    long renumerated = 0;
    for(int i = 0; i < to_array.size(); i++) {
        long offset = pow(58,i);
        long newnum = int(to_array[i]) * offset;
        UtilityFunctions::print("offset: ",offset,"\n newnum: ",newnum);
        renumerated += newnum;
    }
    UtilityFunctions::print("b58: ",b58);
    UtilityFunctions::print("Renumerated: ",renumerated);
    
    if (return_type == 0) {
         String decimal = String::num_uint64(renumerated,10);
         UtilityFunctions::print(decimal);
         
     return decimal;
     
    } else if (return_type == 1) {
         String hexified = String::num_uint64(renumerated,16);
         UtilityFunctions::print(hexified);
         
     return hexified;
     
    } else if (return_type == 2) {
         String text = String::num_uint64(renumerated,16).hex_decode().get_string_from_utf8();
         UtilityFunctions::print(text);
         
     return text;
     
    }
    
return data;

}

String b58encode(String data) {
    Array bytecodes;
    String output;
    PackedByteArray byteArray = data.to_utf8_buffer();
    UtilityFunctions::print("byteArray: ",byteArray);
    String alph = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
    long enumerated = 0;
    byteArray.reverse();
    for(int r = 0;r < byteArray.size();r++) {
       long offset = pow(2,r*8);
       long newnum = byteArray[r] * offset;
       UtilityFunctions::print("Char: ",newnum);
       enumerated += newnum;
    }
    UtilityFunctions::print("Enumerated: ",enumerated);
    long countdown = enumerated;
    while (countdown > 0) {
        long remainder = countdown % 58;
        bytecodes.append(remainder);
       // UtilityFunctions::print(bytecodes);
        countdown = countdown /58;
        
    }
    bytecodes.reverse();
    for (int b = 0; b < bytecodes.size(); b++) { 
        output += alph[bytecodes[b]];
    }

return output;    
} 

String bfn_addition(String num1,String num2) {
    String bfn;
    PackedByteArray array1 = num1.to_utf8_buffer();
    array1.reverse();
    PackedByteArray array2 = num2.to_utf8_buffer();
    array2.reverse();
    
    String num1_start_with_one = array1.get_string_from_utf8();
    String num2_start_with_one = array2.get_string_from_utf8();

    String bigger = num1_start_with_one;
    String smaller = num2_start_with_one;
  
    if (num1_start_with_one.length() < num2_start_with_one.length()) {
        bigger = num2_start_with_one;
        smaller = num1_start_with_one;
    }
    int carrier = 0;
    for (int i= 0; i < bigger.length(); i++) {
        if (smaller.length() > i) {
            int added = String::chr(smaller[i]).to_int() + String::chr(bigger[i]).to_int() + carrier;
            if(added > 9) {
                    carrier = 1;
                    int t = added % 10;
                    bfn += UtilityFunctions::str(t);
                } else {
                    carrier = 0;
                    bfn += UtilityFunctions::str(added);
                 }
        } else {
            int added = String::chr(bigger[i]).to_int() + carrier;
            if(added > 9) {
                    carrier = 1;
                    int t = added % 10;
                    bfn += UtilityFunctions::str(t);
                } else {
                    carrier = 0;
                    bfn += UtilityFunctions::str(added);
                 }
        }
        //UtilityFunctions::print(bfn);
    }
    if (carrier == 1) {
        bfn += "1";
        carrier = 0;
    }    
    PackedByteArray BigFunNumber = bfn.to_utf8_buffer();
    BigFunNumber.reverse();
    
return BigFunNumber.get_string_from_utf8();
}

String bfn_multiplication(String base, String multiple) {
    Array multiple_array;
    Array base_array; 
   
    for (int i = 0; i <= multiple.length();i ++) {
        if (multiple.substr(i,1) != "") {
            multiple_array.append(multiple.substr(i,1));
            }  
    }
    multiple_array.reverse();
    
    for (int i = 0; i <= base.length();i ++) {
        if (base.substr(i,1) != "") {
            base_array.append(base.substr(i,1));
            }
    }
    base_array.reverse();

    String bfn = base;
    
    Array bigger = base_array;
    Array smaller = multiple_array;
  
    if (base_array.size() < multiple_array.size()) {
        bigger = multiple_array;
        smaller = base_array;
    }
    
    Array first_run;
    
    for (int i = 0; i < bigger.size(); i++) {
       
        String append_zeros;
        for (int m = 0; m < smaller.size(); m++) {
           int added = 0; 
           String append_zeros;
           while(append_zeros.length() < m) {
            append_zeros += UtilityFunctions::str("0");
           } 
           int times = String(smaller[m]).to_int();
           for (int add = 1; add <= times; add ++ ) {
                added += String(bigger[i]).to_int();
               }
               String to_string = UtilityFunctions::str(added);
               if(append_zeros.length() > 0) {
                to_string +=append_zeros;
               }
               UtilityFunctions::print(to_string);
               first_run.append(to_string);
        }
        while(append_zeros.length() < i) {
            append_zeros += UtilityFunctions::str("0");
           }
        if(append_zeros.length() > 0) {
                first_run[i] = UtilityFunctions::str(first_run[i])+append_zeros;
        } 
    } 
    
    UtilityFunctions::print("First Run: ",first_run); 
    String second_run;
    
 /*   for (int p = 0; p < first_run.size(); p ++) {
        if (p < first_run.size()) {
            second_run = bfn_addition(first_run[p],second_run);
            //UtilityFunctions::print("second run: ",second_run);
        }
    }
    
    UtilityFunctions::print("possible total: ",second_run,"\n"); */
    
    PackedByteArray BigFunNumber = second_run.to_utf8_buffer();
    //BigFunNumber.reverse();
return BigFunNumber.get_string_from_utf8();
}

String bfn_POW(String base, String power) {

   int m = power.to_int();
    String bfn = base;
    
    for (int i = 1; i < m; i++) {
        bfn = bfn_multiplication(base,bfn);
        UtilityFunctions::print("POW: ",bfn);
    
    }
    
    PackedByteArray BigFunNumber = bfn.to_utf8_buffer();
    //BigFunNumber.reverse();
return BigFunNumber.get_string_from_utf8();
}

