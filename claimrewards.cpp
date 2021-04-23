#include <eosio.token.hpp>

using namespace eosio;

static constexpr extended_symbol EOS{{"EOS", 4}, "eosio.token"_n };

class [[eosio::contract("claimrewards")]] claimrewards : public contract {
public:
    using contract::contract;

    [[eosio::on_notify("eosio.token::transfer")]]
    void on_transfer( const name from, const name to, const asset quantity, const std::string memo )
    {
        require_auth( from );
        if ( to != get_self() ) return;
        if ( from == "eosio.vpay"_n ) vpay( quantity );
        else if ( from == "eosio.bpay"_n  ) bpay( quantity );
    }

private:
    void vpay( const asset quantity )
    {
        const int64_t amount = quantity.amount;
        transfer( get_self(), "toaccount"_n, { amount, EOS }, "vpay" );
    }

    void bpay( const asset quantity )
    {
        const int64_t amount = quantity.amount;
        transfer( get_self(), "toaccount"_n, { amount, EOS }, "bpay" );
    }

    void transfer( const name from, const name to, const extended_asset value, const std::string memo )
    {
        eosio::token::transfer_action transfer( value.contract, { from, "active"_n });
        transfer.send( from, to, value.quantity, memo );
    }
};