# $FreeBSD$

.include <bsd.own.mk>

LIB=	llvmsoftboundruntime

SRCDIR=	runtime/SoftBoundRuntime
SRCS=	softboundcets.c \
	softboundcets-wrappers.c

TGHDRS=	Intrinsics

CFLAGS+= "-D__SOFTBOUNDCETS_TRIE"

.include "../clang.lib.mk"
