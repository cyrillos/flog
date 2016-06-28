#ifndef __UAPI_FLOG_H__
#define __UAPI_FLOG_H__

#include <stdbool.h>
#include <string.h>
#include <errno.h>

/*
 * By Laurent Deniau at https://groups.google.com/forum/#!topic/comp.std.c/d-6Mj5Lko_s
 */
#define FLOG_PP_NARG_(...)			FLOG_PP_ARG_N(__VA_ARGS__)
#define FLOG_PP_NARG(...)			FLOG_PP_NARG_(1, ##__VA_ARGS__, FLOG_PP_RSEQ_N())

#define FLOG_PP_ARG_N(						\
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,_10,		\
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20,		\
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30,		\
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40,		\
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50,		\
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60,		\
         _61,_62,_63,N,...) N

#define FLOG_PP_RSEQ_N()					\
         63,62,61,60,						\
         59,58,57,56,55,54,53,52,51,50,				\
         49,48,47,46,45,44,43,42,41,40,				\
         39,38,37,36,35,34,33,32,31,30,				\
         29,28,27,26,25,24,23,22,21,20,				\
         19,18,17,16,15,14,13,12,11,10,				\
         9,8,7,6,5,4,3,2,1,0

#define FLOG_FOR_EACH_0(x)			0
#define FLOG_FOR_EACH_1(action, x, ...)		action(x)
#define FLOG_FOR_EACH_2(action, x, ...)		action(x), FLOG_FOR_EACH_1(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_3(action, x, ...)		action(x), FLOG_FOR_EACH_2(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_4(action, x, ...)		action(x), FLOG_FOR_EACH_3(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_5(action, x, ...)		action(x), FLOG_FOR_EACH_4(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_6(action, x, ...)		action(x), FLOG_FOR_EACH_5(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_7(action, x, ...)		action(x), FLOG_FOR_EACH_6(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_8(action, x, ...)		action(x), FLOG_FOR_EACH_7(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_9(action, x, ...)		action(x), FLOG_FOR_EACH_8(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_10(action, x, ...)	action(x), FLOG_FOR_EACH_9(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_11(action, x, ...)	action(x), FLOG_FOR_EACH_10(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_12(action, x, ...)	action(x), FLOG_FOR_EACH_11(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_13(action, x, ...)	action(x), FLOG_FOR_EACH_12(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_14(action, x, ...)	action(x), FLOG_FOR_EACH_13(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_15(action, x, ...)	action(x), FLOG_FOR_EACH_14(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_16(action, x, ...)	action(x), FLOG_FOR_EACH_15(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_17(action, x, ...)	action(x), FLOG_FOR_EACH_16(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_18(action, x, ...)	action(x), FLOG_FOR_EACH_17(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_19(action, x, ...)	action(x), FLOG_FOR_EACH_18(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_20(action, x, ...)	action(x), FLOG_FOR_EACH_19(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_21(action, x, ...)	action(x), FLOG_FOR_EACH_20(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_22(action, x, ...)	action(x), FLOG_FOR_EACH_21(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_23(action, x, ...)	action(x), FLOG_FOR_EACH_22(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_24(action, x, ...)	action(x), FLOG_FOR_EACH_23(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_25(action, x, ...)	action(x), FLOG_FOR_EACH_24(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_26(action, x, ...)	action(x), FLOG_FOR_EACH_25(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_27(action, x, ...)	action(x), FLOG_FOR_EACH_26(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_28(action, x, ...)	action(x), FLOG_FOR_EACH_27(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_29(action, x, ...)	action(x), FLOG_FOR_EACH_28(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_30(action, x, ...)	action(x), FLOG_FOR_EACH_29(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_31(action, x, ...)	action(x), FLOG_FOR_EACH_30(action,  __VA_ARGS__)
#define FLOG_FOR_EACH_32(action, x, ...)	action(x), FLOG_FOR_EACH_31(action,  __VA_ARGS__)

#define FLOG_CONCATENATE(arg1, arg2)		FLOG_CONCATENATE1(arg1, arg2)
#define FLOG_CONCATENATE1(arg1, arg2)		FLOG_CONCATENATE2(arg1, arg2)
#define FLOG_CONCATENATE2(arg1, arg2)		arg1##arg2

#define FLOG_FOR_EACH_(N, action, ...)		FLOG_CONCATENATE(FLOG_FOR_EACH_, N)(action, ##__VA_ARGS__)
#define FLOG_FOR_EACH(action, ...)		FLOG_FOR_EACH_(FLOG_PP_NARG( __VA_ARGS__ ), action, ##__VA_ARGS__)

#define flog_typecode(x, ...)				\
	_Generic((x),					\
							\
		 /* Basic types */			\
		 char:				1,	\
		 signed char:			2,	\
		 unsigned char:			3,	\
		 signed short int:		4,	\
		 unsigned short int:		5,	\
		 signed int:			6,	\
		 unsigned int:			7,	\
		 signed long:			8,	\
		 unsigned long:			9,	\
		 signed long long:		10,	\
		 unsigned long long:		11,	\
							\
		 /* Not used for a while */		\
		 /* float:			12, */	\
		 /* double:			13, */	\
		 /* long double:		14, */	\
							\
		 /* Basic poniters */			\
		 char *:			15,	\
		 signed char *:			16,	\
		 unsigned char *:		17,	\
		 signed short int *:		18,	\
		 unsigned short int *:		19,	\
		 signed int *:			20,	\
		 unsigned int *:		21,	\
		 signed long *:			22,	\
		 unsigned long *:		23,	\
		 signed long long *:		24,	\
		 unsigned long long *:		25,	\
		 void *:			26,	\
							\
		 /* Const basic pointers */		\
		 const char *:			27,	\
		 const signed char *:		28,	\
		 const unsigned char *:		29,	\
		 const signed short int *:	30,	\
		 const unsigned short int *:	31,	\
		 const signed int *:		32,	\
		 const unsigned int *:		33,	\
		 const signed long *:		34,	\
		 const unsigned long *:		35,	\
		 const signed long long *:	36,	\
		 const unsigned long long *:	37,	\
		 const void *:			38,	\
							\
		 /* Systypes and pointers */		\
		 default:			-1)

#define FLOG_MSG_TYPE_UNDEF		0
#define FLOG_MSG_TYPE_REGULAR		1

typedef struct {
	unsigned int	type;
	long long	val;
} flog_arg_t;

typedef struct {
	unsigned int	type;
	size_t		nargs;
	const char	*fmt;
	flog_arg_t	args[0];
} flog_msg_t;

extern void flog_encode_msg(size_t nargs, const char *format, ...);
void flog_decode_msg(int fdout, const char *format, ...);
extern void flog_decode_all(int fdout);

#define flog_encode(fmt, ...)							\
	flog_encode_msg(FLOG_PP_NARG(__VA_ARGS__),				\
			fmt, FLOG_FOR_EACH(flog_typecode, ##__VA_ARGS__),	\
			##__VA_ARGS__)

#endif /* __UAPI_FLOG_H__ */
