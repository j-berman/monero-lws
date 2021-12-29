// Copyright (c) 2018, The Monero Project
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include "string.h"

#include "config.h"
#include "cryptonote_basic/cryptonote_basic_impl.h"
#include "db/data.h"
#include "error.h"

namespace lws
{
namespace  db
{
  std::string address_string_::operator()(account_address const& address) const
  {
    const cryptonote::account_public_address address_{
      address.spend_public, address.view_public
    };
    return cryptonote::get_account_address_as_str(
      lws::config::network, address.is_subaddress, address_
    );
  }
  expect<account_address>
  address_string_::operator()(boost::string_ref address) const noexcept
  {
    cryptonote::address_parse_info info{};

    if (!cryptonote::get_account_address_from_str(info, lws::config::network, std::string{address}))
      return {lws::error::bad_address};
    if (info.has_payment_id)
      return {lws::error::bad_address};

    return account_address{
      info.address.m_view_public_key, info.address.m_spend_public_key, info.is_subaddress
    };
  }
} // db
} // lws
