#pragma once

#include <eosio/eosio.hpp>
#include <eosio/system.hpp>

class [[eosio::contract("eosio")]] eosiosystem : public eosio::contract {
   public:
      using contract::contract;

      [[eosio::action]]
      void claimrewards( const eosio::name owner );

      using claimrewards_action = eosio::action_wrapper<"claimrewards"_n, &eosiosystem::claimrewards>;
};