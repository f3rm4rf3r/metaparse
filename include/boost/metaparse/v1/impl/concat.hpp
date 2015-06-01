#ifndef BOOST_METAPARSE_V2_IMPL_CONCAT_HPP
#define BOOST_METAPARSE_V2_IMPL_CONCAT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/config.hpp>
#include <boost/metaparse/v1/fwd/string.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/mul.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class A, class B>
        struct concat;

#ifdef BOOST_VARIADIC_STRING
        template <char... As, char... Bs>
        struct concat<string<As...>, string<Bs...>> : string<As..., Bs...> {};
#else
        template <class A, class B>
        struct concat_impl;

        #ifdef BOOST_ARG
        #  error BOOST_ARG already defined
        #endif
        #define BOOST_ARG(z, n, unused) BOOST_PP_CAT(B, BOOST_PP_INC(n))

        #ifdef BOOST_CONCAT
        #  error BOOST_CONCAT already defined
        #endif
        #define BOOST_CONCAT(z, n, unused) \
          template < \
            BOOST_PP_ENUM_PARAMS(n, int A) BOOST_PP_COMMA_IF(n) \
            BOOST_PP_ENUM_PARAMS(BOOST_LIMIT_STRING_SIZE, int B) \
          > \
          struct \
            concat_impl< \
              string< \
                BOOST_PP_ENUM_PARAMS(n, A) \
                BOOST_PP_COMMA_IF( \
                  BOOST_PP_MUL(BOOST_PP_SUB(BOOST_LIMIT_STRING_SIZE, n), n) \
                ) \
                BOOST_PP_ENUM( \
                  BOOST_PP_SUB(BOOST_LIMIT_STRING_SIZE, n), \
                  BOOST_NO_CHAR BOOST_PP_TUPLE_EAT(3), \
                  ~ \
                ) \
              >, \
              string<BOOST_PP_ENUM_PARAMS(BOOST_LIMIT_STRING_SIZE, B)> \
            > : \
            concat< \
              string<BOOST_PP_ENUM_PARAMS(n, A) BOOST_PP_COMMA_IF(n) B0>, \
              string< \
                BOOST_PP_ENUM( \
                  BOOST_PP_DEC(BOOST_LIMIT_STRING_SIZE), \
                  BOOST_ARG, \
                  ~ \
                ) \
              > \
            > \
          {};

        BOOST_PP_REPEAT(BOOST_LIMIT_STRING_SIZE, BOOST_CONCAT, ~)

        #undef BOOST_ARG
        #undef BOOST_CONCAT

        template <class S>
        struct concat<S, string<> > : S {};

        template <class A, class B>
        struct concat : concat_impl<A, B> {};
#endif
      }
    }
  }
}

#endif

