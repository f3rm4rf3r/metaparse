#ifndef BOOST_METAPARSE_V2_ERROR_LETTER_EXPECTED_HPP
#define BOOST_METAPARSE_V2_ERROR_LETTER_EXPECTED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/define_error.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace error
      {
        BOOST_V2_DEFINE_ERROR(letter_expected, "Letter expected");
      }
    }
  }
}

#endif

