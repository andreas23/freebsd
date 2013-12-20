
/usr/obj/usr/home/hannes/devel/freebsd/tmp/usr/home/hannes/devel/freebsd/usr.bin/clang/clang/clang -o /tmp/t -nostdlib /usr/obj/usr/home/hannes/devel/freebsd/tmp/usr/lib/crt1.o /usr/obj/usr/home/hannes/devel/freebsd/tmp/usr/lib/crti.o /usr/obj/usr/home/hannes/devel/freebsd/tmp/usr/lib/crtbegin.o /tmp/t.c -fsoftbound /usr/obj/usr/home/hannes/devel/freebsd/lib/libc/libc.a /usr/obj/usr/home/hannes/devel/freebsd/tmp/usr/lib/crtend.o /usr/obj/usr/home/hannes/devel/freebsd/tmp/usr/lib/crtn.o


extern void bar (char * arg);
__attribute__((no_softboundcets_calling_convention)) extern void baz (char * arg);

__attribute__((noinline))
void foo (char* arg) {
  char some[16];
  char* p;
  p = some;
  while (*p++ = *arg++);
}

__attribute__((noinline, no_softboundcets_instrument_body)) void foobar (char* arg) {
  char some[16];
  char* p;
  p = some;
  while (*p++ = *arg++);
}

__attribute__((noinline, no_softboundcets_calling_convention)) void foobar2 (char* arg) {
  char some[16];
  char* p;
  p = some;
  while (*p++ = *arg++);
}

int main (int argc, char** argv) {
  foo(argv[1]);
//bar(argv[1]);
//  baz(argv[1]);
  foobar(argv[1]);
  foobar2(argv[1]);
  return 0;
}

