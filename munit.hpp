/* µnit Testing Framework
 * Copyright (c) 2013-2017 Evan Nemerson <evan@nemerson.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#if !defined(MUNIT_PLUS_H)
#define MUNIT_PLUS_H

#include <cstdarg>
#include <cstdlib>
#include <cstring>

#define MUNIT_PLUS_VERSION(major, minor, revision) \
  (((major) << 16) | ((minor) << 8) | (revision))

#define MUNIT_PLUS_CURRENT_VERSION MUNIT_PLUS_VERSION(0, 4, 1)

#if defined(_MSC_VER) && (_MSC_VER < 1600)
#  define munit_plus_int8_t   __int8
#  define munit_plus_uint8_t  unsigned __int8
#  define munit_plus_int16_t  __int16
#  define munit_plus_uint16_t unsigned __int16
#  define munit_plus_int32_t  __int32
#  define munit_plus_uint32_t unsigned __int32
#  define munit_plus_int64_t  __int64
#  define munit_plus_uint64_t unsigned __int64
#else
#  include <cstdint>
#  define munit_plus_int8_t   int8_t
#  define munit_plus_uint8_t  uint8_t
#  define munit_plus_int16_t  int16_t
#  define munit_plus_uint16_t uint16_t
#  define munit_plus_int32_t  int32_t
#  define munit_plus_uint32_t uint32_t
#  define munit_plus_int64_t  int64_t
#  define munit_plus_uint64_t uint64_t
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1800)
#  if !defined(PRIi8)
#    define PRIi8 "i"
#  endif
#  if !defined(PRIi16)
#    define PRIi16 "i"
#  endif
#  if !defined(PRIi32)
#    define PRIi32 "i"
#  endif
#  if !defined(PRIi64)
#    define PRIi64 "I64i"
#  endif
#  if !defined(PRId8)
#    define PRId8 "d"
#  endif
#  if !defined(PRId16)
#    define PRId16 "d"
#  endif
#  if !defined(PRId32)
#    define PRId32 "d"
#  endif
#  if !defined(PRId64)
#    define PRId64 "I64d"
#  endif
#  if !defined(PRIx8)
#    define PRIx8 "x"
#  endif
#  if !defined(PRIx16)
#    define PRIx16 "x"
#  endif
#  if !defined(PRIx32)
#    define PRIx32 "x"
#  endif
#  if !defined(PRIx64)
#    define PRIx64 "I64x"
#  endif
#  if !defined(PRIu8)
#    define PRIu8 "u"
#  endif
#  if !defined(PRIu16)
#    define PRIu16 "u"
#  endif
#  if !defined(PRIu32)
#    define PRIu32 "u"
#  endif
#  if !defined(PRIu64)
#    define PRIu64 "I64u"
#  endif
#else
#  include <cinttypes>
#endif

extern "C++" {

#if defined(__GNUC__)
#  define MUNIT_PLUS_LIKELY(expr) (__builtin_expect ((expr), 1))
#  define MUNIT_PLUS_UNLIKELY(expr) (__builtin_expect ((expr), 0))
#  define MUNIT_PLUS_UNUSED __attribute__((__unused__))
#else
#  define MUNIT_PLUS_LIKELY(expr) (expr)
#  define MUNIT_PLUS_UNLIKELY(expr) (expr)
#  define MUNIT_PLUS_UNUSED
#endif

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) && !defined(__PGI)
#  define MUNIT_PLUS_ARRAY_PARAM(name) name
#else
#  define MUNIT_PLUS_ARRAY_PARAM(name)
#endif

#if !defined(_WIN32)
#  define MUNIT_PLUS_SIZE_MODIFIER "z"
#  define MUNIT_PLUS_CHAR_MODIFIER "hh"
#  define MUNIT_PLUS_SHORT_MODIFIER "h"
#else
#  if defined(_M_X64) || defined(__amd64__)
#    define MUNIT_PLUS_SIZE_MODIFIER "I64"
#  else
#    define MUNIT_PLUS_SIZE_MODIFIER ""
#  endif
#  define MUNIT_PLUS_CHAR_MODIFIER ""
#  define MUNIT_PLUS_SHORT_MODIFIER ""
#endif

#if __cplusplus >= 201103L
#  define MUNIT_PLUS_NO_RETURN [[noreturn]]
#elif defined(__GNUC__)
#  define MUNIT_PLUS_NO_RETURN __attribute__((__noreturn__))
#elif defined(_MSC_VER)
#  define MUNIT_PLUS_NO_RETURN __declspec(noreturn)
#else
#  define MUNIT_PLUS_NO_RETURN
#endif
#define MUNIT_NO_RETURN MUNIT_PLUS_NO_RETURN

#if defined(_MSC_VER) &&  (_MSC_VER >= 1500)
#  define MUNIT_PLUS_PUSH_DISABLE_MSVC_C4127 __pragma(warning(push)) __pragma(warning(disable:4127))
#  define MUNIT_PLUS_POP_DISABLE_MSVC_C4127 __pragma(warning(pop))
#else
#  define MUNIT_PLUS_PUSH_DISABLE_MSVC_C4127
#  define MUNIT_PLUS_POP_DISABLE_MSVC_C4127
#endif
#define MUNIT__PUSH_DISABLE_MSVC_C4127 MUNIT_PLUS_PUSH_DISABLE_MSVC_C4127
#define MUNIT__POP_DISABLE_MSVC_C4127 MUNIT_PLUS_POP_DISABLE_MSVC_C4127

#if defined(_MSC_VER) && (_MSC_VER < 1900)
#  define MUNIT_PLUS_CONSTEXPR
#  define MUNIT_PLUS_NOEXCEPT throw()
#  define MUNIT_PLUS_NOEXCEPT_FALSE
#else
#  define MUNIT_PLUS_CONSTEXPR constexpr
#  define MUNIT_PLUS_NOEXCEPT noexcept
#  define MUNIT_PLUS_NOEXCEPT_FALSE noexcept(false)
#endif /*_MSC_VER*/

typedef enum {
  MUNIT_PLUS_LOG_DEBUG,
  MUNIT_PLUS_LOG_INFO,
  MUNIT_PLUS_LOG_WARNING,
  MUNIT_PLUS_LOG_ERROR
} MunitPlusLogLevel;

#if defined(__GNUC__) && !defined(__MINGW32__)
#  define MUNIT_PLUS_PRINTF(string_index, first_to_check) __attribute__((format (printf, string_index, first_to_check)))
#else
#  define MUNIT_PLUS_PRINTF(string_index, first_to_check)
#endif
#define MUNIT_PRINTF MUNIT_PLUS_PRINTF

MUNIT_PLUS_PRINTF(4, 5)
void munit_plus_logf_ex(MunitPlusLogLevel level, const char* filename, int line, const char* format, ...) MUNIT_PLUS_NOEXCEPT_FALSE;

#define munit_plus_logf(level, format, ...) \
  munit_plus_logf_ex(level, __FILE__, __LINE__, format, __VA_ARGS__)

#define munit_plus_log(level, msg) \
  munit_plus_logf(level, "%s", msg)

MUNIT_PLUS_NO_RETURN
MUNIT_PLUS_PRINTF(3, 4)
void munit_plus_errorf_ex(const char* filename, int line, const char* format, ...) MUNIT_PLUS_NOEXCEPT_FALSE;

#define munit_plus_errorf(format, ...) \
  munit_plus_errorf_ex(__FILE__, __LINE__, format, __VA_ARGS__)

#define munit_plus_error(msg) \
  munit_plus_errorf("%s", msg)

#define munit_plus_assert(expr) \
  /*do*/ { \
    if (!MUNIT_PLUS_LIKELY(expr)) { \
      munit_plus_error("assertion failed: " #expr); \
    } \
  } /*while (0)*/

#define munit_plus_assert_true(expr) \
  /*do*/ { \
    if (!MUNIT_PLUS_LIKELY(expr)) { \
      munit_plus_error("assertion failed: " #expr " is not true"); \
    } \
  } /*while (0)*/

#define munit_plus_assert_false(expr) \
  /*do*/ { \
    if (!MUNIT_PLUS_LIKELY(!(expr))) { \
      munit_plus_error("assertion failed: " #expr " is not false"); \
    } \
  } /*while (0)*/

#define munit_plus_assert_char(a, op, b) \
  munit_plus_assert_type_full("'\\x", "'", char, "02" MUNIT_PLUS_CHAR_MODIFIER "x", a, op, b)
#define munit_plus_assert_uchar(a, op, b) \
  munit_plus_assert_type_full("'\\x", "'", unsigned char, "02" MUNIT_PLUS_CHAR_MODIFIER "x", a, op, b)
#define munit_plus_assert_short(a, op, b) \
  munit_plus_assert_type(short, MUNIT_PLUS_SHORT_MODIFIER "d", a, op, b)
#define munit_plus_assert_ushort(a, op, b) \
  munit_plus_assert_type(unsigned short, MUNIT_PLUS_SHORT_MODIFIER "u", a, op, b)
#define munit_plus_assert_int(a, op, b) \
  munit_plus_assert_type(int, "d", a, op, b)
#define munit_plus_assert_uint(a, op, b) \
  munit_plus_assert_type(unsigned int, "u", a, op, b)
#define munit_plus_assert_long(a, op, b) \
  munit_plus_assert_type(long int, "ld", a, op, b)
#define munit_plus_assert_ulong(a, op, b) \
  munit_plus_assert_type(unsigned long int, "lu", a, op, b)
#define munit_plus_assert_llong(a, op, b) \
  munit_plus_assert_type(long long int, "lld", a, op, b)
#define munit_plus_assert_ullong(a, op, b) \
  munit_plus_assert_type(unsigned long long int, "llu", a, op, b)

#define munit_plus_assert_size(a, op, b) \
  munit_plus_assert_type(std::size_t, MUNIT_PLUS_SIZE_MODIFIER "u", a, op, b)

#define munit_plus_assert_float(a, op, b) \
  munit_plus_assert_type(float, "f", a, op, b)
#define munit_plus_assert_double(a, op, b) \
  munit_plus_assert_type(double, "g", a, op, b)
#define munit_plus_assert_ptr(a, op, b) \
  munit_plus_assert_type(const void*, "p", a, op, b)

#define munit_plus_assert_int8(a, op, b)             \
  munit_plus_assert_type(munit_plus_int8_t, PRIi8, a, op, b)
#define munit_plus_assert_uint8(a, op, b) \
  munit_plus_assert_type(munit_plus_uint8_t, PRIu8, a, op, b)
#define munit_plus_assert_int16(a, op, b) \
  munit_plus_assert_type(munit_plus_int16_t, PRIi16, a, op, b)
#define munit_plus_assert_uint16(a, op, b) \
  munit_plus_assert_type(munit_plus_uint16_t, PRIu16, a, op, b)
#define munit_plus_assert_int32(a, op, b) \
  munit_plus_assert_type(munit_plus_int32_t, PRIi32, a, op, b)
#define munit_plus_assert_uint32(a, op, b) \
  munit_plus_assert_type(munit_plus_uint32_t, PRIu32, a, op, b)
#define munit_plus_assert_int64(a, op, b) \
  munit_plus_assert_type(munit_plus_int64_t, PRIi64, a, op, b)
#define munit_plus_assert_uint64(a, op, b) \
  munit_plus_assert_type(munit_plus_uint64_t, PRIu64, a, op, b)

#define munit_plus_assert_double_equal(a, b, precision) \
  munit_plus_assert_near_equal(double, a, b, precision)

#define munit_plus_assert_string_equal(a, b) \
  do { \
    const char* munit_tmp_a_ = a; \
    const char* munit_tmp_b_ = b; \
    if (MUNIT_PLUS_UNLIKELY(std::strcmp(munit_tmp_a_, munit_tmp_b_) != 0)) { \
      munit_plus_errorf("assertion failed: string %s == %s (\"%s\" == \"%s\")", \
                   #a, #b, munit_tmp_a_, munit_tmp_b_); \
    } \
    MUNIT__PUSH_DISABLE_MSVC_C4127 \
  } while (0) \
  MUNIT__POP_DISABLE_MSVC_C4127

#define munit_plus_assert_string_not_equal(a, b) \
  do { \
    const char* munit_tmp_a_ = a; \
    const char* munit_tmp_b_ = b; \
    if (MUNIT_PLUS_UNLIKELY(std::strcmp(munit_tmp_a_, munit_tmp_b_) == 0)) { \
      munit_plus_errorf("assertion failed: string %s != %s (\"%s\" == \"%s\")", \
                   #a, #b, munit_tmp_a_, munit_tmp_b_); \
    } \
    MUNIT__PUSH_DISABLE_MSVC_C4127 \
  } while (0) \
  MUNIT__POP_DISABLE_MSVC_C4127

#define munit_plus_assert_memory_equal(size, a, b) \
  do { \
    const unsigned char* munit_tmp_a_ = (const unsigned char*) (a); \
    const unsigned char* munit_tmp_b_ = (const unsigned char*) (b); \
    const std::size_t munit_tmp_size_ = (size); \
    if (MUNIT_PLUS_UNLIKELY(std::memcmp(munit_tmp_a_, munit_tmp_b_, munit_tmp_size_)) != 0) { \
      std::size_t munit_tmp_pos_; \
      for (munit_tmp_pos_ = 0 ; munit_tmp_pos_ < munit_tmp_size_ ; munit_tmp_pos_++) { \
        if (munit_tmp_a_[munit_tmp_pos_] != munit_tmp_b_[munit_tmp_pos_]) { \
          munit_plus_errorf("assertion failed: memory %s == %s, at offset %" MUNIT_PLUS_SIZE_MODIFIER "u", \
                       #a, #b, munit_tmp_pos_); \
          break; \
        } \
      } \
    } \
    MUNIT__PUSH_DISABLE_MSVC_C4127 \
  } while (0) \
  MUNIT__POP_DISABLE_MSVC_C4127

#define munit_plus_assert_memory_not_equal(size, a, b) \
  do { \
    const unsigned char* munit_tmp_a_ = (const unsigned char*) (a); \
    const unsigned char* munit_tmp_b_ = (const unsigned char*) (b); \
    const std::size_t munit_tmp_size_ = (size); \
    if (MUNIT_PLUS_UNLIKELY(std::memcmp(munit_tmp_a_, munit_tmp_b_, munit_tmp_size_)) == 0) { \
      munit_plus_errorf("assertion failed: memory %s != %s (%zu bytes)", \
                   #a, #b, munit_tmp_size_); \
    } \
    MUNIT__PUSH_DISABLE_MSVC_C4127 \
  } while (0) \
  MUNIT__POP_DISABLE_MSVC_C4127

#define munit_plus_assert_ptr_equal(a, b) \
  munit_plus_assert_ptr(a, ==, b)
#define munit_plus_assert_ptr_not_equal(a, b) \
  munit_plus_assert_ptr(a, !=, b)
#define munit_plus_assert_null(ptr) \
  munit_plus_assert_ptr(ptr, ==, nullptr)
#define munit_plus_assert_not_null(ptr) \
  munit_plus_assert_ptr(ptr, !=, nullptr)
#define munit_plus_assert_ptr_null(ptr) \
  munit_plus_assert_ptr(ptr, ==, nullptr)
#define munit_plus_assert_ptr_not_null(ptr) \
  munit_plus_assert_ptr(ptr, !=, nullptr)

/*** Memory allocation ***/
void* munit_plus_malloc_ex(const char* filename, int line, std::size_t size);


#define munit_plus_malloc(size) \
  munit_plus_malloc_ex(__FILE__, __LINE__, (size))


#define munit_plus_new(type) \
  munit_plus_new_ex<type>(#type, __FILE__, __LINE__)
#if defined(_MSC_VER) && (_MSC_VER < 1800)
#  define munit_plus_newp(type, ...) /* because no support for typename...D yet */ \
    [&](void) -> type * { \
      type * out; \
      try { \
        return new type(__VA_ARGS__); \
      } catch (std::exception const& e) { \
        munit_plus_logf(MUNIT_PLUS_LOG_ERROR, \
          "Failed to construct %s of %" MUNIT_PLUS_SIZE_MODIFIER "u bytes. (what(): %s)", #type, sizeof(type), e.what()); \
        throw; \
      } catch (...) { \
        munit_plus_logf(MUNIT_PLUS_LOG_ERROR, \
          "Failed to construct %s of %" MUNIT_PLUS_SIZE_MODIFIER "u bytes.", #type, sizeof(type)); \
        throw; \
      } \
      if (MUNIT_PLUS_UNLIKELY(out == nullptr)) { \
        munit_plus_logf(MUNIT_PLUS_LOG_ERROR, \
          "Failed to allocate %s of %" MUNIT_PLUS_SIZE_MODIFIER "u bytes.", #type, sizeof(type)); \
      } \
    }()
#else
#  define munit_plus_newp(type, ...) \
    munit_plus_new_ex<type>(#type, __FILE__, __LINE__, __VA_ARGS__)
#endif

#define munit_plus_calloc(nmemb, size) \
  munit_plus_malloc((nmemb) * (size))

#define munit_plus_newa(type, nmemb) \
  munit_plus_newa_ex<type>(#type, __FILE__, __LINE__, nmemb)


/*** Random number generation ***/

void munit_plus_rand_seed(munit_plus_uint32_t seed);
munit_plus_uint32_t munit_plus_rand_uint32(void);
int munit_plus_rand_int_range(int min, int max);
double munit_plus_rand_double(void);
void munit_plus_rand_memory(std::size_t size, munit_plus_uint8_t buffer[MUNIT_PLUS_ARRAY_PARAM(size)]);

/*** Tests and Suites ***/

typedef enum {
  /* Test successful */
  MUNIT_PLUS_OK,
  /* Test failed */
  MUNIT_PLUS_FAIL,
  /* Test was skipped */
  MUNIT_PLUS_SKIP,
  /* Test failed due to circumstances not intended to be tested
   * (things like network errors, invalid parameter value, failure to
   * allocate memory in the test harness, etc.). */
  MUNIT_PLUS_ERROR
} MunitPlusResult;

typedef struct {
  char*  name;
  char** values;
} MunitPlusParameterEnum;

typedef struct {
  char* name;
  char* value;
} MunitPlusParameter;

const char* munit_plus_parameters_get(const MunitPlusParameter params[], const char* key);

typedef enum {
  MUNIT_PLUS_TEST_OPTION_NONE             = 0,
  MUNIT_PLUS_TEST_OPTION_SINGLE_ITERATION = 1 << 0,
  MUNIT_PLUS_TEST_OPTION_TODO             = 1 << 1
} MunitPlusTestOptions;

typedef MunitPlusResult (* MunitPlusTestFunc)(const MunitPlusParameter params[], void* user_data_or_fixture);
typedef void*       (* MunitPlusTestSetup)(const MunitPlusParameter params[], void* user_data);
typedef void        (* MunitPlusTestTearDown)(void* fixture);

typedef struct {
  char*               name;
  MunitPlusTestFunc       test;
  MunitPlusTestSetup      setup;
  MunitPlusTestTearDown   tear_down;
  MunitPlusTestOptions    options;
  MunitPlusParameterEnum* parameters;
} MunitPlusTest;

typedef enum {
  MUNIT_PLUS_SUITE_OPTION_NONE = 0
} MunitPlusSuiteOptions;

typedef struct MunitPlusSuite_ MunitPlusSuite;

struct MunitPlusSuite_ {
  char*             prefix;
  MunitPlusTest*        tests;
  MunitPlusSuite*       suites;
  unsigned int      iterations;
  MunitPlusSuiteOptions options;
};

int munit_plus_suite_main(const MunitPlusSuite* suite, void* user_data, int argc, char* const argv[MUNIT_PLUS_ARRAY_PARAM(argc + 1)]);

/* Note: I'm not very happy with this API; it's likely to change if I
 * figure out something better.  Suggestions welcome. */

typedef struct MunitPlusArgument_ MunitPlusArgument;

struct MunitPlusArgument_ {
  char* name;
  bool (* parse_argument)(const MunitPlusSuite* suite, void* user_data, int* arg, int argc, char* const argv[MUNIT_PLUS_ARRAY_PARAM(argc + 1)]);
  void (* write_help)(const MunitPlusArgument* argument, void* user_data);
};

int munit_plus_suite_main_custom(const MunitPlusSuite* suite,
                            void* user_data,
                            int argc, char* const argv[MUNIT_PLUS_ARRAY_PARAM(argc + 1)],
                            const MunitPlusArgument arguments[]);

#if defined(MUNIT_ENABLE_ASSERT_ALIASES)

#define assert_true(expr) munit_plus_assert_true(expr)
#define assert_false(expr) munit_plus_assert_false(expr)
#define assert_char(a, op, b) munit_plus_assert_char(a, op, b)
#define assert_uchar(a, op, b) munit_plus_assert_uchar(a, op, b)
#define assert_short(a, op, b) munit_plus_assert_short(a, op, b)
#define assert_ushort(a, op, b) munit_plus_assert_ushort(a, op, b)
#define assert_int(a, op, b) munit_plus_assert_int(a, op, b)
#define assert_uint(a, op, b) munit_plus_assert_uint(a, op, b)
#define assert_long(a, op, b) munit_plus_assert_long(a, op, b)
#define assert_ulong(a, op, b) munit_plus_assert_ulong(a, op, b)
#define assert_llong(a, op, b) munit_plus_assert_llong(a, op, b)
#define assert_ullong(a, op, b) munit_plus_assert_ullong(a, op, b)
#define assert_size(a, op, b) munit_plus_assert_size(a, op, b)
#define assert_float(a, op, b) munit_plus_assert_float(a, op, b)
#define assert_double(a, op, b) munit_plus_assert_double(a, op, b)
#define assert_ptr(a, op, b) munit_plus_assert_ptr(a, op, b)

#define assert_int8(a, op, b) munit_plus_assert_int8(a, op, b)
#define assert_uint8(a, op, b) munit_plus_assert_uint8(a, op, b)
#define assert_int16(a, op, b) munit_plus_assert_int16(a, op, b)
#define assert_uint16(a, op, b) munit_plus_assert_uint16(a, op, b)
#define assert_int32(a, op, b) munit_plus_assert_int32(a, op, b)
#define assert_uint32(a, op, b) munit_plus_assert_uint32(a, op, b)
#define assert_int64(a, op, b) munit_plus_assert_int64(a, op, b)
#define assert_uint64(a, op, b) munit_plus_assert_uint64(a, op, b)

#define assert_double_equal(a, b, precision) munit_plus_assert_double_equal(a, b, precision)
#define assert_string_equal(a, b) munit_plus_assert_string_equal(a, b)
#define assert_string_not_equal(a, b) munit_plus_assert_string_not_equal(a, b)
#define assert_memory_equal(size, a, b) munit_plus_assert_memory_equal(size, a, b)
#define assert_memory_not_equal(size, a, b) munit_plus_assert_memory_not_equal(size, a, b)
#define assert_ptr_equal(a, b) munit_plus_assert_ptr_equal(a, b)
#define assert_ptr_not_equal(a, b) munit_plus_assert_ptr_not_equal(a, b)
#define assert_ptr_null(ptr) munit_plus_assert_null_equal(ptr)
#define assert_ptr_not_null(ptr) munit_plus_assert_not_null(ptr)

#define assert_null(ptr) munit_plus_assert_null(ptr)
#define assert_not_null(ptr) munit_plus_assert_not_null(ptr)

#endif /* defined(MUNIT_ENABLE_ASSERT_ALIASES) */

}


/*** Cxx-style macros ***/


#include <string>
#include <sstream>
#include <cstring>
#include <new>
#include <exception>
#include <type_traits>


/* General thing formatter. Now you can create your own fancy strings
 * for your thing type. */
template <typename A>
struct munit_plus_formatter {
  static std::string format(A const& val);
};

template <>
struct munit_plus_formatter<std::nullptr_t> {
  static std::string format(std::nullptr_t val);
};

template <>
struct munit_plus_formatter<bool> {
  static std::string format(bool val);
};

template <>
struct munit_plus_formatter<char> {
  static std::string format(char val);
};
template <>
struct munit_plus_formatter<signed char> {
  static std::string format(signed char val);
};
template <>
struct munit_plus_formatter<unsigned char> {
  static std::string format(unsigned char val);
};

template <>
struct munit_plus_formatter<short> {
  static std::string format(short val);
};
template <>
struct munit_plus_formatter<unsigned short> {
  static std::string format(unsigned short val);
};

template <>
struct munit_plus_formatter<int> {
  static std::string format(int val);
};
template <>
struct munit_plus_formatter<unsigned int> {
  static std::string format(unsigned int val);
};

template <>
struct munit_plus_formatter<long> {
  static std::string format(long val);
};
template <>
struct munit_plus_formatter<unsigned long> {
  static std::string format(unsigned long val);
};

template <>
struct munit_plus_formatter<long long> {
  static std::string format(long long val);
};
template <>
struct munit_plus_formatter<unsigned long long> {
  static std::string format(unsigned long long val);
};

template <>
struct munit_plus_formatter<float> {
  static std::string format(float val);
  static std::string precise_format(float val, int i);
};
template <>
struct munit_plus_formatter<double> {
  static std::string format(double val);
  static std::string precise_format(double val, int i);
};
template <>
struct munit_plus_formatter<long double> {
  static std::string format(long double val);
  static std::string precise_format(long double val, int i);
};
template <typename T>
struct munit_plus_formatter<T*> {
  static std::string format(T const* val);
};
template <>
struct munit_plus_formatter<void*> {
  static std::string format(void const* val);
};

template <typename T>
std::string munit_plus_formatter<T>::format(T const& val) {
  std::ostringstream out;
  out << val;
  return out.str();
}
template <typename T>
std::string munit_plus_formatter<T*>::format(T const* val) {
  return munit_plus_formatter<void*>::format(val);
}

struct munit_plus_ops {
  struct equal_to {
    static MUNIT_PLUS_CONSTEXPR char const* text(void) { return " == "; };
    bool value;
  };
  struct not_equal_to {
    static MUNIT_PLUS_CONSTEXPR char const* text(void) { return " != "; };
    bool value;
  };
  struct greater {
    static MUNIT_PLUS_CONSTEXPR char const* text(void) { return " > "; };
    bool value;
  };
  struct less {
    static MUNIT_PLUS_CONSTEXPR char const* text(void) { return " < "; };
    bool value;
  };
  struct greater_equal {
    static MUNIT_PLUS_CONSTEXPR char const* text(void) { return " >= "; };
    bool value;
  };
  struct less_equal {
    static MUNIT_PLUS_CONSTEXPR char const* text(void) { return " <= "; };
    bool value;
  };
};

template <typename A>
class munit_plus_op_switch {
private:
  A const& value;
public:
  munit_plus_op_switch(A const& value);
  template <typename B>
  struct munit_plus_ops::equal_to operator==(B const& ) const;
  template <typename B>
  struct munit_plus_ops::not_equal_to operator!=(B const& ) const;
  template <typename B>
  struct munit_plus_ops::greater operator>(B const& ) const;
  template <typename B>
  struct munit_plus_ops::less operator<(B const& ) const;
  template <typename B>
  struct munit_plus_ops::greater_equal operator>=(B const& ) const;
  template <typename B>
  struct munit_plus_ops::less_equal operator<=(B const& ) const;
};

template <typename C>
class munit_plus_precision {
private:
  C value;

public:
  munit_plus_precision(C&& diff);
  bool operator>(double eps) const;
};

template <typename A, typename B, typename C>
void munit_plus_assert_type_base
    (char const* filename, int line, char const* stra, char const* strb, A const& a, B const& b, C c);
template <typename A, typename B>
void munit_plus_assert_precision_base
    (char const* filename, int line, char const* stra, char const* strb, A const a, B const b, double eps, int prec);

#if defined(_MSC_VER) && (_MSC_VER < 1800)
template <typename A>
A* munit_plus_new_ex(const char* typetext, const char* filename, int line);
template <typename A, typename B>
A* munit_plus_new_ex(const char* typetext, const char* filename, int line, B, ...); /* will trigger static_assert! */
#else
template <typename A, typename... D>
A* munit_plus_new_ex(const char* typetext, const char* filename, int line, D... args);
#endif
template <typename A>
A* munit_plus_newa_ex(const char* typetext, const char* filename, int line, std::size_t nmemb);

/*** Random number generation / C++ ***/

template <typename A>
void munit_plus_rand_memory_ex(A &a);
template <typename It>
void munit_plus_rand_memory_ex(It const& begin, It const& end);


template <typename A, typename B, typename C>
inline void munit_plus_assert_type_base
    (char const* filename, int line, char const* stra, char const* strb, A const& a, B const& b, C c)
{
  if (!MUNIT_PLUS_LIKELY(c.value)) {
    std::string text = "assertion failed: ";
    text.reserve(100);
    (((text += stra) += C::text()) += strb);
    ((text += " (") += munit_plus_formatter<A>::format(a));
    text += C::text();
    (text += munit_plus_formatter<B>::format(b)) += ")";
    munit_plus_errorf_ex(filename, line, "%s", text.c_str());
  }
}

template <typename A, typename B>
inline void munit_plus_assert_precision_base
    (char const* filename, int line, char const* stra, char const* strb, A const a, B const b, double eps, int prec)
{
  MUNIT_PLUS_CONSTEXPR char const* C_text = " == ";
  typedef decltype(a-b) C;
  munit_plus_precision<C> const diff = ((a - b) < 0) ?
      -(a - b) :
      (a - b);
  if (MUNIT_PLUS_UNLIKELY(diff > static_cast<C>(eps))) {
    std::string text = "assertion failed: ";
    text.reserve(100);
    (((text += stra) += C_text) += strb);
    ((text += " (") += munit_plus_formatter<A>::precise_format(a,prec));
    text += C_text;
    (text += munit_plus_formatter<B>::precise_format(b,prec)) += ")";
    munit_plus_errorf_ex(filename, line, "%s", text.c_str());
  }
}

template <typename A>
inline munit_plus_op_switch<A>::munit_plus_op_switch(A const& v) : value(v) { }
template <typename A>
template <typename B>
inline struct munit_plus_ops::equal_to munit_plus_op_switch<A>::operator==(B const& x) const {
  struct munit_plus_ops::equal_to const out = { value == x };
  return out;
}
template <typename A>
template <typename B>
inline struct munit_plus_ops::not_equal_to munit_plus_op_switch<A>::operator!=(B const& x) const {
  struct munit_plus_ops::not_equal_to const out = { value != x };
  return out;
}
template <typename A>
template <typename B>
inline struct munit_plus_ops::greater munit_plus_op_switch<A>::operator>(B const& x) const {
  struct munit_plus_ops::greater const out = { value > x };
  return out;
}
template <typename A>
template <typename B>
inline struct munit_plus_ops::less munit_plus_op_switch<A>::operator<(B const& x) const {
  struct munit_plus_ops::less const out = { value < x };
  return out;
}
template <typename A>
template <typename B>
inline struct munit_plus_ops::greater_equal munit_plus_op_switch<A>::operator>=(B const& x) const {
  struct munit_plus_ops::greater_equal const out = { value >= x };
  return out;
}
template <typename A>
template <typename B>
inline struct munit_plus_ops::less_equal munit_plus_op_switch<A>::operator<=(B const& x) const {
  struct munit_plus_ops::less_equal const out = { value <= x };
  return out;
}

template <typename C>
munit_plus_precision<C>::munit_plus_precision(C&& diff) : value(diff) { }
template <typename C>
bool munit_plus_precision<C>::operator>(double eps) const { return value > eps; }

#define munit_plus_assert_type_full(prefix, suffix, T, fmt, a, op, b)   \
  /*do*/ { \
    T const& munit_tmp_a_ = (a); \
    T const& munit_tmp_b_ = (b); \
    munit_plus_assert_type_base(__FILE__, __LINE__, #a,#b,\
      munit_tmp_a_, munit_tmp_b_,\
      munit_plus_op_switch<T>(munit_tmp_a_) op munit_tmp_b_); \
  } /*while (0)*/

#define munit_plus_assert_type(T, fmt, a, op, b) \
  munit_plus_assert_type_full("", "", T, fmt, a, op, b)

#define munit_plus_assert_type2(T, a, op, b) \
  munit_plus_assert_type_full("", "", T, "", a, op, b)

#define munit_plus_assert_op(a, op, b) \
  /*do*/ { \
    std::remove_reference<decltype(a)>::type const& munit_tmp_a_ = (a); \
    std::remove_reference<decltype(b)>::type const& munit_tmp_b_ = (b); \
    munit_plus_assert_type_base(__FILE__, __LINE__, #a,#b,\
      munit_tmp_a_, munit_tmp_b_,\
      munit_plus_op_switch<decltype(munit_tmp_a_)>(munit_tmp_a_) op munit_tmp_b_); \
  } /*while (0)*/

#define munit_plus_assert_near_equal(T, a, b, precision) \
  /*do*/ { \
    T const& munit_tmp_a_ = (a); \
    T const& munit_tmp_b_ = (b); \
    munit_plus_assert_precision_base(__FILE__, __LINE__, #a,#b,\
      munit_tmp_a_,munit_tmp_b_,1e-##precision,precision); \
  } /*while (0)*/

#if defined(_MSC_VER) && (_MSC_VER < 1800)
template <typename A> /* because no support for typename...D yet */
inline A* munit_plus_new_ex(const char* typetext, const char* filename, int line)
{
  A* ptr;

  if (sizeof(A) == 0)
    return nullptr;

  try {
    ptr = new A;
  } catch (std::exception const& e) {
    munit_plus_logf_ex(MUNIT_PLUS_LOG_ERROR, filename, line,
      "Failed to construct %s of %" MUNIT_PLUS_SIZE_MODIFIER "u bytes. (what(): %s)",
      typetext, sizeof(A), e.what());
    throw;
  } catch (...) {
    munit_plus_logf_ex(MUNIT_PLUS_LOG_ERROR, filename, line,
      "Failed to construct %s of %" MUNIT_PLUS_SIZE_MODIFIER "u bytes.", typetext, sizeof(A));
    throw;
  }
  if (MUNIT_PLUS_UNLIKELY(ptr == nullptr)) {
    munit_plus_logf_ex(MUNIT_PLUS_LOG_ERROR, filename, line,
      "Failed to allocate %s of %" MUNIT_PLUS_SIZE_MODIFIER "u bytes.", typetext, sizeof(A));
  }

  return ptr;
}
template <typename A, typename B> /* because no support for typename...D yet */
inline A* munit_plus_new_ex(const char* typetext, const char* filename, int line, B, ...)
{
  static_assert(sizeof(A) == 0u, "Parameter pack syntax unavailable. Use the munit_plus_newp macro.");
  return nullptr;
}
#else
template <typename A, typename ...D>
inline A* munit_plus_new_ex(const char* typetext, const char* filename, int line, D... args)
{
  A* ptr;

  if (sizeof(A) == 0)
    return nullptr;

  try {
    ptr = new A(static_cast<D&&>(args)...);
  } catch (std::exception const& e) {
    munit_plus_logf_ex(MUNIT_PLUS_LOG_ERROR, filename, line,
      "Failed to construct %s of %" MUNIT_PLUS_SIZE_MODIFIER "u bytes. (what(): %s)",
      typetext, sizeof(A), e.what());
    throw;
  } catch (...) {
    munit_plus_logf_ex(MUNIT_PLUS_LOG_ERROR, filename, line,
      "Failed to construct %s of %" MUNIT_PLUS_SIZE_MODIFIER "u bytes.", typetext, sizeof(A));
    throw;
  }
  if (MUNIT_PLUS_UNLIKELY(ptr == nullptr)) {
    munit_plus_logf_ex(MUNIT_PLUS_LOG_ERROR, filename, line,
      "Failed to allocate %s of %" MUNIT_PLUS_SIZE_MODIFIER "u bytes.", typetext, sizeof(A));
  }

  return ptr;
}
#endif

template <typename A>
inline A* munit_plus_newa_ex(const char* typetext, const char* filename, int line, std::size_t nmemb) {
  A* ptr;

  if (sizeof(A) == 0 || nmemb == 0)
    return nullptr;

  try {
    ptr = new A[nmemb];
  } catch (std::exception const& e) {
    munit_plus_logf_ex(MUNIT_PLUS_LOG_ERROR, filename, line,
      "Failed to construct %s[%" MUNIT_PLUS_SIZE_MODIFIER "u] of %" MUNIT_PLUS_SIZE_MODIFIER "u bytes. (what(): %s)",
      typetext, nmemb, sizeof(A)*nmemb, e.what());
    throw;
  } catch (...) {
    munit_plus_logf_ex(MUNIT_PLUS_LOG_ERROR, filename, line,
      "Failed to construct %s[%" MUNIT_PLUS_SIZE_MODIFIER "u] of %" MUNIT_PLUS_SIZE_MODIFIER "u bytes.",
      typetext, nmemb, sizeof(A)*nmemb);
    throw;
  }
  if (MUNIT_PLUS_UNLIKELY(ptr == nullptr)) {
    munit_plus_logf_ex(MUNIT_PLUS_LOG_ERROR, filename, line,
      "Failed to allocate %s[%" MUNIT_PLUS_SIZE_MODIFIER "u] of %" MUNIT_PLUS_SIZE_MODIFIER "u bytes.",
      typetext, nmemb, sizeof(A)*nmemb);
  }

  return ptr;
}

template <typename A>
void munit_plus_rand_memory_ex(A &a)
{
  static_assert(std::is_trivial<A>::value, "munit_plus_rand_memory_ex only safe on trivial objects");
  munit_plus_rand_memory(sizeof(A), reinterpret_cast<munit_plus_uint8_t*>(&a));
}

template <typename It>
void munit_plus_rand_memory_ex(It const& begin, It const& end)
{
  It i;
  typedef typename std::remove_reference<decltype(*i)>::type value_type;
  static_assert(std::is_trivial<value_type>::value, "munit_plus_rand_memory_ex only safe on trivial objects");
  for (i = begin; i != end; ++i) {
    value_type v;
    munit_plus_rand_memory(sizeof(value_type), reinterpret_cast<munit_plus_uint8_t*>(&v));
    *i = v;
  }
}

#endif /* !defined(MUNIT_PLUS_H) */

#if defined(MUNIT_ENABLE_ASSERT_ALIASES)
#  if defined(assert)
#    undef assert
#  endif
#  define assert(expr) munit_plus_assert(expr)
#endif
