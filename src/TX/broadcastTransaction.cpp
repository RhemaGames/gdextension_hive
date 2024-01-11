#include "broadcastTransaction.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/http_client.hpp>
#include <godot_cpp/classes/http_request.hpp>
#include <godot_cpp/classes/crypto.hpp>
#include <godot_cpp/classes/crypto_key.hpp>
//#include <openssl/ssl.h>


/** Broadcast signed transaction */
/* 
export const broadcastTransaction = async signedTransaction => {
  const result = await call('condenser_api.broadcast_transaction', [
    signedTransaction
  ])
  return result
}
*/
