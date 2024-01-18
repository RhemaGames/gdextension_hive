#include "signTransaction.h"

#include <godot_cpp/godot.hpp>
#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/class_db.hpp>
#include "../hive.h"

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
	Dictionary digest;
	
// Not sure what to do with these 
	/*const buffer = new ByteBuffer(
    ByteBuffer.DEFAULT_CAPACITY,
    ByteBuffer.LITTLE_ENDIAN
  ) */
   // Need to see if this needs to be created or if Godot already has the proper Serializer
   // Serializer.Transaction(buffer, transaction)
  
  //buffer.flip() //Switches from writing to reading mode Is this needed?
  
  //const transactionData = Buffer.from(buffer.toBuffer())
  //const txId = sha256(transactionData).toString('hex').slice(0, 40)
  //const digest = sha256(Buffer.concat([chainId, transactionData]))
  //return { digest, txId }
	
	
return digest;
}

String signTransaction(String transaction, String keys,String chain_id) {
	String signedTransaction;
	Dictionary tD;
	tD = transactionDigest(transaction,chain_id);
 
return signedTransaction;
}

/*
import { Serializer } from '../helpers/serializer.js'

/**
 * Sign a transaction by keys (supports multi signature)
 * @param transaction - transaction to be signed
 * @param keys - Array of keys<Buffer>
 */
/*
export const signTransaction = (transaction, keys) => {
  const CHAIN_ID = Buffer.from(config.chain_id, 'hex')
  const { digest, txId } = transactionDigest(transaction, CHAIN_ID)
  const signedTransaction = { ...transaction }
  if (!signedTransaction.signatures) {
    signedTransaction.signatures = []
  }
  if (!Array.isArray(keys)) {
    keys = [keys]
  }
  for (const key of keys) {
    const signature = key.sign(digest)
    signedTransaction.signatures.push(signature.customToString())
  }

  return { signedTransaction, txId }
}
*/

/** Serialize transaction */
/*
export const transactionDigest = (transaction, chainId = CHAIN_ID) => {
  const buffer = new ByteBuffer(
    ByteBuffer.DEFAULT_CAPACITY,
    ByteBuffer.LITTLE_ENDIAN
  )
  try {
    Serializer.Transaction(buffer, transaction)
  } catch (cause) {
    throw new Error('Unable to serialize transaction')
  }
  buffer.flip()
  const transactionData = Buffer.from(buffer.toBuffer())
  const txId = sha256(transactionData).toString('hex').slice(0, 40)
  const digest = sha256(Buffer.concat([chainId, transactionData]))
  return { digest, txId }
}
*/
