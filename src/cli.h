
#ifndef CLI_H
#define CLI_H

#include <R.h>
#include <Rinternals.h>
#include <Rversion.h>

SEXP clic_tty_size();
SEXP clic_ansi_simplify(SEXP x);

SEXP clic_utf8_display_width(SEXP x);

typedef volatile int vint;

extern volatile int* cli_timer_flag;
extern volatile int cli__reset;
void cli_progress_add(SEXP bar, int inc);
SEXP cli_progress_bar(vint **ptr, int total, SEXP config);
void cli_progress_done(SEXP bar);
void cli_progress_init_timer(vint **ptr);
int cli_progress_num();
void cli_progress_set(SEXP bar, int set);
void cli_progress_set_clear(SEXP bar, int);
void cli_progress_set_format(SEXP bar, const char *name);
void cli_progress_set_name(SEXP bar, const char *name);
void cli_progress_set_status(SEXP bar, const char *name);
void cli_progress_set_type(SEXP bar, const char *name);
void cli_progress_sleep(int s, long ns);
void cli_progress_update(SEXP bar, int set, int inc, int force);

SEXP cli__progress_update(SEXP bar);
SEXP clic_progress_along(SEXP seq, SEXP bar);
extern SEXP cli_pkgenv;

#if R_VERSION >= R_Version(3, 5, 0)
void cli_init_altrep(DllInfo *dll);
#endif

double clic__get_time();
SEXP clic__find_var(SEXP rho, SEXP symbol);

SEXP clic_start_thread(SEXP pkgenv, SEXP tick, SEXP speed);
SEXP clic_stop_thread();
SEXP clic_tick_reset();
SEXP clic_get_time();
SEXP clic_tick_set(SEXP ticktime, SEXP speedtime);
SEXP clic_tick_pause(SEXP state);
SEXP clic_tick_resume(SEXP state);
SEXP clic_make_timer();
SEXP clic_update_due();

/** Given the first byte in a valid UTF-8 byte sequence, determine the number of
 *  total bytes */

#define UTF8LITE_UTF8_TOTAL_LEN(u) \
	(  ((x) & 0x80) == 0x00 ? 1 \
	 : ((x) & 0xE0) == 0xC0 ? 2 \
	 : ((x) & 0xF0) == 0xE0 ? 3 : 4)

/** Last valid unicode codepoint */
#define UTF8LITE_CODE_MAX 0x10FFFF

/** Indicates whether a 16-bit code unit is a UTF-16 high surrogate.
 *  High surrogates are in the range 0xD800 `(1101 1000 0000 0000)`
 *  to 0xDBFF `(1101 1011 1111 1111)`. */
#define UTF8LITE_IS_UTF16_HIGH(x) (((x) & 0xFC00) == 0xD800)

/** Indicates whether a 16-bit code unit is a UTF-16 low surrogate.
 *  Low surrogates are in the range 0xDC00 `(1101 1100 0000 0000)`
 *  to 0xDFFF `(1101 1111 1111 1111)`. */
#define UTF8LITE_IS_UTF16_LOW(x) (((x) & 0xFC00) == 0xDC00)

/** Indicates whether a given unsigned integer is a valid unicode codepoint */
#define UTF8LITE_IS_UNICODE(x) \
	(((x) <= UTF8LITE_CODE_MAX) \
	 && !UTF8LITE_IS_UTF16_HIGH(x) \
	 && !UTF8LITE_IS_UTF16_LOW(x))

SEXP clic_get_embedded_utf8();
SEXP clic_set_embedded_utf8(SEXP value);
int clic__utf8_display_width_char(const uint8_t **x);

#endif
