# BP Rewards EOSIO Smart Contract

## ON_NOTIFY

- [`transfer`](#on-notify-transfer)

## ON_NOTIFY `transfer`

Handle `eosio.token` EOS transfer when coming from `eosio.vpay` or `eosio.bpay`

### Handle `vpay` & `bpay`

Customize handling of incoming transfer from BP rewards

```c++
[[eosio::on_notify("eosio.token::transfer")]]
void on_transfer( const name from, const name to, const asset quantity, const std::string memo )
{
    require_auth( from );
    if ( to != get_self() ) return;
    if ( from == "eosio.vpay"_n ) vpay( quantity );
    else if ( from == "eosio.bpay"_n  ) bpay( quantity );
}

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
```

## Build

```bash
eosio-cpp claimrewards.cpp -I include
```

## Deploy

```bash
cleos set code <bpaccount> . claimrewards.wasm
```