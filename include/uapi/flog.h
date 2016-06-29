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

#define FLOG_PP_ARG_N( _0, _1, _2, _3, _4,	\
		       _5, _6, _7, _8, _9,	\
		      _10,_11,_12,_13,_14,	\
		      _15,_16,_17,_18,_19,	\
		      _20,_21,_22,_23,_24,	\
		      _25,_26,_27,_28,_29,	\
		      _30,_31,  N, ...)		N

#define FLOG_PP_RSEQ_N()			\
		       31, 30, 29, 28, 27,	\
		       26, 25, 24, 23, 22,	\
		       21, 20, 19, 18, 17,	\
		       16, 15, 14, 13, 12,	\
		       11, 10,  9,  8,  7,	\
		        6,  5,  4,  3,  2,	\
		        1,  0

#define FLOG_FOR_EACH_0(x)			0
#define FLOG_FOR_EACH_1(action, x, ...)		(action(0, x))
#define FLOG_FOR_EACH_2(action, x, ...)		((action(1, x))  | FLOG_FOR_EACH_1(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_3(action, x, ...)		((action(2, x))  | FLOG_FOR_EACH_2(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_4(action, x, ...)		((action(3, x))  | FLOG_FOR_EACH_3(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_5(action, x, ...)		((action(4, x))  | FLOG_FOR_EACH_4(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_6(action, x, ...)		((action(5, x))  | FLOG_FOR_EACH_5(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_7(action, x, ...)		((action(6, x))  | FLOG_FOR_EACH_6(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_8(action, x, ...)		((action(7, x))  | FLOG_FOR_EACH_7(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_9(action, x, ...)		((action(8, x))  | FLOG_FOR_EACH_8(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_10(action, x, ...)	((action(9, x))  | FLOG_FOR_EACH_9(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_11(action, x, ...)	((action(10, x)) | FLOG_FOR_EACH_10(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_12(action, x, ...)	((action(11, x)) | FLOG_FOR_EACH_11(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_13(action, x, ...)	((action(12, x)) | FLOG_FOR_EACH_12(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_14(action, x, ...)	((action(13, x)) | FLOG_FOR_EACH_13(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_15(action, x, ...)	((action(14, x)) | FLOG_FOR_EACH_14(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_16(action, x, ...)	((action(15, x)) | FLOG_FOR_EACH_15(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_17(action, x, ...)	((action(16, x)) | FLOG_FOR_EACH_16(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_18(action, x, ...)	((action(17, x)) | FLOG_FOR_EACH_17(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_19(action, x, ...)	((action(18, x)) | FLOG_FOR_EACH_18(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_20(action, x, ...)	((action(19, x)) | FLOG_FOR_EACH_19(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_21(action, x, ...)	((action(20, x)) | FLOG_FOR_EACH_20(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_22(action, x, ...)	((action(21, x)) | FLOG_FOR_EACH_21(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_23(action, x, ...)	((action(22, x)) | FLOG_FOR_EACH_22(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_24(action, x, ...)	((action(23, x)) | FLOG_FOR_EACH_23(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_25(action, x, ...)	((action(24, x)) | FLOG_FOR_EACH_24(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_26(action, x, ...)	((action(25, x)) | FLOG_FOR_EACH_25(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_27(action, x, ...)	((action(26, x)) | FLOG_FOR_EACH_26(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_28(action, x, ...)	((action(27, x)) | FLOG_FOR_EACH_27(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_29(action, x, ...)	((action(28, x)) | FLOG_FOR_EACH_28(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_30(action, x, ...)	((action(29, x)) | FLOG_FOR_EACH_29(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_31(action, x, ...)	((action(30, x)) | FLOG_FOR_EACH_30(action,  __VA_ARGS__))
#define FLOG_FOR_EACH_32(action, x, ...)	((action(31, x)) | FLOG_FOR_EACH_31(action,  __VA_ARGS__))

#define FLOG_CONCATENATE(arg1, arg2)		FLOG_CONCATENATE1(arg1, arg2)
#define FLOG_CONCATENATE1(arg1, arg2)		FLOG_CONCATENATE2(arg1, arg2)
#define FLOG_CONCATENATE2(arg1, arg2)		arg1##arg2

#define FLOG_FOR_EACH_(N, action, ...)		FLOG_CONCATENATE(FLOG_FOR_EACH_, N)(action, ##__VA_ARGS__)
#define FLOG_FOR_EACH(action, ...)		FLOG_FOR_EACH_(FLOG_PP_NARG( __VA_ARGS__ ), action, ##__VA_ARGS__)

#define flog_typecode(order, var, ...)				\
	_Generic((var),						\
								\
		 /* Basic types */				\
		 char:				0,		\
		 signed char:			0,		\
		 unsigned char:			0,		\
		 signed short int:		0,		\
		 unsigned short int:		0,		\
		 signed int:			0,		\
		 unsigned int:			0,		\
		 signed long:			0,		\
		 unsigned long:			0,		\
		 signed long long:		0,		\
		 unsigned long long:		0,		\
								\
		 /* Not used for a while */			\
		 /* float:			12, */		\
		 /* double:			13, */		\
		 /* long double:		14, */		\
								\
		 /* Basic poniters */				\
		 char *:			(1u << order),	\
		 signed char *:			(1u << order),	\
		 unsigned char *:		(1u << order),	\
		 signed short int *:		0,		\
		 unsigned short int *:		0,		\
		 signed int *:			0,		\
		 unsigned int *:		0,		\
		 signed long *:			0,		\
		 unsigned long *:		0,		\
		 signed long long *:		0,		\
		 unsigned long long *:		0,		\
		 void *:			0,		\
								\
		 /* Const basic pointers */			\
		 const char *:			(1u << order),	\
		 const signed char *:		(1u << order),	\
		 const unsigned char *:		(1u << order),	\
		 const signed short int *:	0,		\
		 const unsigned short int *:	0,		\
		 const signed int *:		0,		\
		 const unsigned int *:		0,		\
		 const signed long *:		0,		\
		 const unsigned long *:		0,		\
		 const signed long long *:	0,		\
		 const unsigned long long *:	0,		\
		 const void *:			0,		\
								\
		 /* Systypes and pointers */			\
		 default:			-1)

#define FLOG_MSG_TYPE_UNDEF		0
#define FLOG_MSG_TYPE_REGULAR		1

typedef struct {
	unsigned int	type;
	unsigned int	nargs;
	unsigned int	mask;
	const char	*fmt;
	long		args[0];
} flog_msg_t;

extern void flog_encode_msg(unsigned int nargs, unsigned int mask, const char *format, ...);
void flog_decode_msg(int fdout, const char *format, ...);
extern void flog_decode_all(int fdout);

#define flog_encode(fmt, ...)							\
	flog_encode_msg(FLOG_PP_NARG(__VA_ARGS__),				\
			FLOG_FOR_EACH(flog_typecode, ##__VA_ARGS__),		\
			fmt, ##__VA_ARGS__)

#endif /* __UAPI_FLOG_H__ */
