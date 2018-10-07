//
// basic.cpp
//

#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;
using namespace std;

class basic : public contract {
    using contract::contract; // api usage

public:
    basic( account_name self ) : // set up
        contract(self),
        _multistatus(_self, _self){} // this instantiates multi_index


    [[eosio::action]]
    void test( name sender, string status) {
      require_auth( sender );

      // find sender with primary_key within multistatus database
      auto iter = _multistatus.find(sender);
      // if nothing exists with the primary_key in the database
      if (iter == _multistatus.end()) _multistatus.emplace( sender, [&] (auto& row) {
          row.sender = sender;
          row.status = status;
      });
      else _multistatus.modify( iter, 0, [&] (auto& row){
        row.status = status;
      });

    }

private:


  struct [[eosio::table]] multistatus {
    name sender;
    string status;

    name primary_key() const { return sender; }
    EOSLIB_SERIALIZE( multistatus, (sender)(status) )
  };

  // create an actual table, which will hold the info
  multi_index<N(multistatus), multistatus> _multistatus;





};
EOSIO_ABI( basic, (test) )
