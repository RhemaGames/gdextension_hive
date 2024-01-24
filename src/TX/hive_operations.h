#ifndef HIVE_OPS_H
#define HIVE_OPS_H

#include <godot_cpp/core/class_db.hpp>
using namespace godot;


	
/*#ifdef HIVE_ENABLE_SMT
        /// SMT operations
        claim_reward_balance2_operation, // last_pre_smt + 1

        smt_setup_operation, // last_pre_smt + 2
        smt_setup_emissions_operation, // last_pre_smt + 3
        smt_set_setup_parameters_operation, // last_pre_smt + 4
        smt_set_runtime_parameters_operation, // last_pre_smt + 5
        smt_create_operation, // last_pre_smt + 5
        smt_contribute_operation, // last_pre_smt + 6
#endif

        /// virtual operations below this point
        fill_convert_request_operation, // last_regular + 1
        author_reward_operation, // last_regular + 2
        curation_reward_operation, // last_regular + 3
        comment_reward_operation, // last_regular + 4
        liquidity_reward_operation, // last_regular + 5
        interest_operation, // last_regular + 6
        fill_vesting_withdraw_operation, // last_regular + 7
        fill_order_operation, // last_regular + 8
        shutdown_witness_operation, // last_regular + 9
        fill_transfer_from_savings_operation, // last_regular + 10
        hardfork_operation, // last_regular + 11
        comment_payout_update_operation, // last_regular + 12
        return_vesting_delegation_operation, // last_regular + 13
        comment_benefactor_reward_operation, // last_regular + 14
        producer_reward_operation, // last_regular + 15
        clear_null_account_balance_operation, // last_regular + 16
        proposal_pay_operation, // last_regular + 17
        dhf_funding_operation, // last_regular + 18
        hardfork_hive_operation, // last_regular + 19
        hardfork_hive_restore_operation, // last_regular + 20
        delayed_voting_operation, // last_regular + 21
        consolidate_treasury_balance_operation, // last_regular + 22
        effective_comment_vote_operation, // last_regular + 23
        ineffective_delete_comment_operation, // last_regular + 24
        dhf_conversion_operation, // last_regular + 25
        expired_account_notification_operation, // last_regular + 26
        changed_recovery_account_operation, // last_regular + 27
        transfer_to_vesting_completed_operation, // last_regular + 28
        pow_reward_operation, // last_regular + 29
        vesting_shares_split_operation, // last_regular + 30
        account_created_operation, // last_regular + 31
        fill_collateralized_convert_request_operation, // last_regular + 32
        system_warning_operation, // last_regular + 33,
        fill_recurrent_transfer_operation, // last_regular + 34
        failed_recurrent_transfer_operation, // last_regular + 35
        limit_order_cancelled_operation,  // last_regular + 36
        producer_missed_operation, // last_regular + 37
        proposal_fee_operation, //last_regular + 38
        collateralized_convert_immediate_conversion_operation, //last_regular + 39
        escrow_approved_operation, //last_regular + 40
        escrow_rejected_operation, //last_regular + 41
        proxy_cleared_operation, //last_regular + 42
        declined_voting_rights_operation //last_regular + 43
*/	

Dictionary vote(String account,String author, String permlink, int weight);
Dictionary vote2(String account,String author, String permlink, int weight);

String vote_serialized(Dictionary operation);

Dictionary comment(String parent_author, String parent_permlink, String author, String permlink, String title, String body, Dictionary json_metadata);
Dictionary custom_json(Array required_auths, String reqired_posting_auths, String id, Dictionary json);
int get_operation(String t);

String reendian(String hex);





#endif
