//
//  hello.cpp
//

#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

class hello : public contract {
public:
    using contract::contract;

    [[eosio::action]]
    void hi (account_name user) {
        require_auth( user ); // ensures the authorizing user must be the same as
                                // the user we are saying "hi" to
        print ("Hi, ", name{user} );
    }
};
EOSIO_ABI( hello, (hi))
