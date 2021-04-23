# BP Rewards EOSIO Smart Contract

## ON_NOTIFY

- [`transfer`](#on-notify-transfer)

## ON_NOTIFY `transfer`

Handle `eosio.token` EOS transfer when coming from `eosio.vpay` or `eosio.bpay`

### Handle `vpay` & `bpay`

Customize handling of incoming transfer from BP rewards

```c++
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