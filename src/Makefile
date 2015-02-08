CC = g++
LD = g++
CPPFLAGS = -W -Wall
LDFLAGS = -loath

PRGSRC = otpsetpin.cpp otpadduser.cpp otpgenurl.cpp otpdeluser.cpp
LIBSRC = utils.cpp options.cpp userinfo.cpp otperror.cpp
TARGETS = $(PRGSRC:.cpp=)

LIBOBJ = $(LIBSRC:.cpp=.o)

all: depend $(TARGETS)

depend:
	gccmakedep -v -- $(CPPFLAGS) -- $(PRGSRC) $(LIBSRC)

otpsetpin: otpsetpin.o $(LIBOBJ)
	$(LD) -o otpsetpin otpsetpin.o $(LIBOBJ) $(LDFLAGS)

otpadduser: otpadduser.o $(LIBOBJ)
	$(LD) -o otpadduser otpadduser.o $(LIBOBJ) $(LDFLAGS)

otpdeluser: otpdeluser.o $(LIBOBJ)
	$(LD) -o otpdeluser otpdeluser.o $(LIBOBJ) $(LDFLAGS)

otpgenurl: otpgenurl.o $(LIBOBJ)
	$(LD) -o otpgenurl otpgenurl.o $(LIBOBJ) $(LDFLAGS)

clean:
	rm -f *.o $(TARGETS)

install:
	install --mode=4711 --owner=root otpsetpin /usr/local/bin
	install --mode=4711 --owner=root otpgenurl /usr/local/bin
	install --mode=0711 --owner=root otpadduser /usr/local/bin
	install --mode=0711 --owner=root otpdeluser /usr/local/bin
	install --mode=0600 --owner=root ../options.oath.sample /etc/options.oath
	touch /etc/users.oath
	chmod 600 /etc/users.oath
	chown root /etc/users.oath

# DO NOT DELETE
otpsetpin.o: otpsetpin.cpp /usr/include/stdc-predef.h \
 /usr/include/c++/4.9/iostream \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++config.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/os_defines.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/cpu_defines.h \
 /usr/include/c++/4.9/ostream /usr/include/c++/4.9/ios \
 /usr/include/c++/4.9/iosfwd /usr/include/c++/4.9/bits/stringfwd.h \
 /usr/include/c++/4.9/bits/memoryfwd.h \
 /usr/include/c++/4.9/bits/postypes.h /usr/include/c++/4.9/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stdarg.h \
 /usr/include/i386-linux-gnu/bits/wchar.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stddef.h /usr/include/xlocale.h \
 /usr/include/c++/4.9/exception \
 /usr/include/c++/4.9/bits/atomic_lockfree_defines.h \
 /usr/include/c++/4.9/bits/char_traits.h \
 /usr/include/c++/4.9/bits/stl_algobase.h \
 /usr/include/c++/4.9/bits/functexcept.h \
 /usr/include/c++/4.9/bits/exception_defines.h \
 /usr/include/c++/4.9/bits/cpp_type_traits.h \
 /usr/include/c++/4.9/ext/type_traits.h \
 /usr/include/c++/4.9/ext/numeric_traits.h \
 /usr/include/c++/4.9/bits/stl_pair.h /usr/include/c++/4.9/bits/move.h \
 /usr/include/c++/4.9/bits/concept_check.h \
 /usr/include/c++/4.9/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.9/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.9/debug/debug.h \
 /usr/include/c++/4.9/bits/stl_iterator.h \
 /usr/include/c++/4.9/bits/ptr_traits.h \
 /usr/include/c++/4.9/bits/predefined_ops.h \
 /usr/include/c++/4.9/bits/localefwd.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++locale.h \
 /usr/include/c++/4.9/clocale /usr/include/locale.h \
 /usr/include/i386-linux-gnu/bits/locale.h /usr/include/c++/4.9/cctype \
 /usr/include/ctype.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/endian.h \
 /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/bits/byteswap.h \
 /usr/include/i386-linux-gnu/bits/byteswap-16.h \
 /usr/include/c++/4.9/bits/ios_base.h \
 /usr/include/c++/4.9/ext/atomicity.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/gthr.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/bits/timex.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/setjmp.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/atomic_word.h \
 /usr/include/c++/4.9/bits/locale_classes.h /usr/include/c++/4.9/string \
 /usr/include/c++/4.9/bits/allocator.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++allocator.h \
 /usr/include/c++/4.9/ext/new_allocator.h /usr/include/c++/4.9/new \
 /usr/include/c++/4.9/bits/ostream_insert.h \
 /usr/include/c++/4.9/bits/cxxabi_forced.h \
 /usr/include/c++/4.9/bits/stl_function.h \
 /usr/include/c++/4.9/backward/binders.h \
 /usr/include/c++/4.9/bits/range_access.h \
 /usr/include/c++/4.9/bits/basic_string.h \
 /usr/include/c++/4.9/bits/basic_string.tcc \
 /usr/include/c++/4.9/bits/locale_classes.tcc \
 /usr/include/c++/4.9/streambuf /usr/include/c++/4.9/bits/streambuf.tcc \
 /usr/include/c++/4.9/bits/basic_ios.h \
 /usr/include/c++/4.9/bits/locale_facets.h /usr/include/c++/4.9/cwctype \
 /usr/include/wctype.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/ctype_base.h \
 /usr/include/c++/4.9/bits/streambuf_iterator.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/ctype_inline.h \
 /usr/include/c++/4.9/bits/locale_facets.tcc \
 /usr/include/c++/4.9/bits/basic_ios.tcc \
 /usr/include/c++/4.9/bits/ostream.tcc /usr/include/c++/4.9/istream \
 /usr/include/c++/4.9/bits/istream.tcc /usr/include/c++/4.9/sstream \
 /usr/include/c++/4.9/bits/sstream.tcc /usr/include/c++/4.9/vector \
 /usr/include/c++/4.9/bits/stl_construct.h \
 /usr/include/c++/4.9/ext/alloc_traits.h \
 /usr/include/c++/4.9/bits/stl_uninitialized.h \
 /usr/include/c++/4.9/bits/stl_vector.h \
 /usr/include/c++/4.9/bits/stl_bvector.h \
 /usr/include/c++/4.9/bits/vector.tcc /usr/include/c++/4.9/cstdlib \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/bits/waitflags.h \
 /usr/include/i386-linux-gnu/bits/waitstatus.h \
 /usr/include/i386-linux-gnu/sys/types.h \
 /usr/include/i386-linux-gnu/sys/select.h \
 /usr/include/i386-linux-gnu/bits/select.h \
 /usr/include/i386-linux-gnu/bits/sigset.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/i386-linux-gnu/bits/stdlib-float.h utils.h options.h \
 userinfo.h otperror.h
otpadduser.o: otpadduser.cpp /usr/include/stdc-predef.h \
 /usr/include/c++/4.9/iostream \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++config.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/os_defines.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/cpu_defines.h \
 /usr/include/c++/4.9/ostream /usr/include/c++/4.9/ios \
 /usr/include/c++/4.9/iosfwd /usr/include/c++/4.9/bits/stringfwd.h \
 /usr/include/c++/4.9/bits/memoryfwd.h \
 /usr/include/c++/4.9/bits/postypes.h /usr/include/c++/4.9/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stdarg.h \
 /usr/include/i386-linux-gnu/bits/wchar.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stddef.h /usr/include/xlocale.h \
 /usr/include/c++/4.9/exception \
 /usr/include/c++/4.9/bits/atomic_lockfree_defines.h \
 /usr/include/c++/4.9/bits/char_traits.h \
 /usr/include/c++/4.9/bits/stl_algobase.h \
 /usr/include/c++/4.9/bits/functexcept.h \
 /usr/include/c++/4.9/bits/exception_defines.h \
 /usr/include/c++/4.9/bits/cpp_type_traits.h \
 /usr/include/c++/4.9/ext/type_traits.h \
 /usr/include/c++/4.9/ext/numeric_traits.h \
 /usr/include/c++/4.9/bits/stl_pair.h /usr/include/c++/4.9/bits/move.h \
 /usr/include/c++/4.9/bits/concept_check.h \
 /usr/include/c++/4.9/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.9/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.9/debug/debug.h \
 /usr/include/c++/4.9/bits/stl_iterator.h \
 /usr/include/c++/4.9/bits/ptr_traits.h \
 /usr/include/c++/4.9/bits/predefined_ops.h \
 /usr/include/c++/4.9/bits/localefwd.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++locale.h \
 /usr/include/c++/4.9/clocale /usr/include/locale.h \
 /usr/include/i386-linux-gnu/bits/locale.h /usr/include/c++/4.9/cctype \
 /usr/include/ctype.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/endian.h \
 /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/bits/byteswap.h \
 /usr/include/i386-linux-gnu/bits/byteswap-16.h \
 /usr/include/c++/4.9/bits/ios_base.h \
 /usr/include/c++/4.9/ext/atomicity.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/gthr.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/bits/timex.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/setjmp.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/atomic_word.h \
 /usr/include/c++/4.9/bits/locale_classes.h /usr/include/c++/4.9/string \
 /usr/include/c++/4.9/bits/allocator.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++allocator.h \
 /usr/include/c++/4.9/ext/new_allocator.h /usr/include/c++/4.9/new \
 /usr/include/c++/4.9/bits/ostream_insert.h \
 /usr/include/c++/4.9/bits/cxxabi_forced.h \
 /usr/include/c++/4.9/bits/stl_function.h \
 /usr/include/c++/4.9/backward/binders.h \
 /usr/include/c++/4.9/bits/range_access.h \
 /usr/include/c++/4.9/bits/basic_string.h \
 /usr/include/c++/4.9/bits/basic_string.tcc \
 /usr/include/c++/4.9/bits/locale_classes.tcc \
 /usr/include/c++/4.9/streambuf /usr/include/c++/4.9/bits/streambuf.tcc \
 /usr/include/c++/4.9/bits/basic_ios.h \
 /usr/include/c++/4.9/bits/locale_facets.h /usr/include/c++/4.9/cwctype \
 /usr/include/wctype.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/ctype_base.h \
 /usr/include/c++/4.9/bits/streambuf_iterator.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/ctype_inline.h \
 /usr/include/c++/4.9/bits/locale_facets.tcc \
 /usr/include/c++/4.9/bits/basic_ios.tcc \
 /usr/include/c++/4.9/bits/ostream.tcc /usr/include/c++/4.9/istream \
 /usr/include/c++/4.9/bits/istream.tcc /usr/include/c++/4.9/sstream \
 /usr/include/c++/4.9/bits/sstream.tcc /usr/include/c++/4.9/fstream \
 /usr/include/c++/4.9/bits/codecvt.h /usr/include/c++/4.9/cstdio \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/basic_file.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++io.h \
 /usr/include/c++/4.9/bits/fstream.tcc /usr/include/c++/4.9/vector \
 /usr/include/c++/4.9/bits/stl_construct.h \
 /usr/include/c++/4.9/ext/alloc_traits.h \
 /usr/include/c++/4.9/bits/stl_uninitialized.h \
 /usr/include/c++/4.9/bits/stl_vector.h \
 /usr/include/c++/4.9/bits/stl_bvector.h \
 /usr/include/c++/4.9/bits/vector.tcc /usr/include/c++/4.9/cstdlib \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/bits/waitflags.h \
 /usr/include/i386-linux-gnu/bits/waitstatus.h \
 /usr/include/i386-linux-gnu/sys/types.h \
 /usr/include/i386-linux-gnu/sys/select.h \
 /usr/include/i386-linux-gnu/bits/select.h \
 /usr/include/i386-linux-gnu/bits/sigset.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/i386-linux-gnu/bits/stdlib-float.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h \
 /usr/include/i386-linux-gnu/bits/environments.h \
 /usr/include/i386-linux-gnu/bits/confname.h /usr/include/getopt.h \
 /usr/include/liboath/oath.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stdbool.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stdint.h /usr/include/stdint.h \
 /usr/include/string.h utils.h options.h userinfo.h otperror.h
otpgenurl.o: otpgenurl.cpp /usr/include/stdc-predef.h \
 /usr/include/c++/4.9/iostream \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++config.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/os_defines.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/cpu_defines.h \
 /usr/include/c++/4.9/ostream /usr/include/c++/4.9/ios \
 /usr/include/c++/4.9/iosfwd /usr/include/c++/4.9/bits/stringfwd.h \
 /usr/include/c++/4.9/bits/memoryfwd.h \
 /usr/include/c++/4.9/bits/postypes.h /usr/include/c++/4.9/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stdarg.h \
 /usr/include/i386-linux-gnu/bits/wchar.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stddef.h /usr/include/xlocale.h \
 /usr/include/c++/4.9/exception \
 /usr/include/c++/4.9/bits/atomic_lockfree_defines.h \
 /usr/include/c++/4.9/bits/char_traits.h \
 /usr/include/c++/4.9/bits/stl_algobase.h \
 /usr/include/c++/4.9/bits/functexcept.h \
 /usr/include/c++/4.9/bits/exception_defines.h \
 /usr/include/c++/4.9/bits/cpp_type_traits.h \
 /usr/include/c++/4.9/ext/type_traits.h \
 /usr/include/c++/4.9/ext/numeric_traits.h \
 /usr/include/c++/4.9/bits/stl_pair.h /usr/include/c++/4.9/bits/move.h \
 /usr/include/c++/4.9/bits/concept_check.h \
 /usr/include/c++/4.9/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.9/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.9/debug/debug.h \
 /usr/include/c++/4.9/bits/stl_iterator.h \
 /usr/include/c++/4.9/bits/ptr_traits.h \
 /usr/include/c++/4.9/bits/predefined_ops.h \
 /usr/include/c++/4.9/bits/localefwd.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++locale.h \
 /usr/include/c++/4.9/clocale /usr/include/locale.h \
 /usr/include/i386-linux-gnu/bits/locale.h /usr/include/c++/4.9/cctype \
 /usr/include/ctype.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/endian.h \
 /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/bits/byteswap.h \
 /usr/include/i386-linux-gnu/bits/byteswap-16.h \
 /usr/include/c++/4.9/bits/ios_base.h \
 /usr/include/c++/4.9/ext/atomicity.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/gthr.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/bits/timex.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/setjmp.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/atomic_word.h \
 /usr/include/c++/4.9/bits/locale_classes.h /usr/include/c++/4.9/string \
 /usr/include/c++/4.9/bits/allocator.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++allocator.h \
 /usr/include/c++/4.9/ext/new_allocator.h /usr/include/c++/4.9/new \
 /usr/include/c++/4.9/bits/ostream_insert.h \
 /usr/include/c++/4.9/bits/cxxabi_forced.h \
 /usr/include/c++/4.9/bits/stl_function.h \
 /usr/include/c++/4.9/backward/binders.h \
 /usr/include/c++/4.9/bits/range_access.h \
 /usr/include/c++/4.9/bits/basic_string.h \
 /usr/include/c++/4.9/bits/basic_string.tcc \
 /usr/include/c++/4.9/bits/locale_classes.tcc \
 /usr/include/c++/4.9/streambuf /usr/include/c++/4.9/bits/streambuf.tcc \
 /usr/include/c++/4.9/bits/basic_ios.h \
 /usr/include/c++/4.9/bits/locale_facets.h /usr/include/c++/4.9/cwctype \
 /usr/include/wctype.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/ctype_base.h \
 /usr/include/c++/4.9/bits/streambuf_iterator.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/ctype_inline.h \
 /usr/include/c++/4.9/bits/locale_facets.tcc \
 /usr/include/c++/4.9/bits/basic_ios.tcc \
 /usr/include/c++/4.9/bits/ostream.tcc /usr/include/c++/4.9/istream \
 /usr/include/c++/4.9/bits/istream.tcc /usr/include/c++/4.9/sstream \
 /usr/include/c++/4.9/bits/sstream.tcc /usr/include/c++/4.9/vector \
 /usr/include/c++/4.9/bits/stl_construct.h \
 /usr/include/c++/4.9/ext/alloc_traits.h \
 /usr/include/c++/4.9/bits/stl_uninitialized.h \
 /usr/include/c++/4.9/bits/stl_vector.h \
 /usr/include/c++/4.9/bits/stl_bvector.h \
 /usr/include/c++/4.9/bits/vector.tcc /usr/include/c++/4.9/cstdlib \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/bits/waitflags.h \
 /usr/include/i386-linux-gnu/bits/waitstatus.h \
 /usr/include/i386-linux-gnu/sys/types.h \
 /usr/include/i386-linux-gnu/sys/select.h \
 /usr/include/i386-linux-gnu/bits/select.h \
 /usr/include/i386-linux-gnu/bits/sigset.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/i386-linux-gnu/bits/stdlib-float.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h \
 /usr/include/i386-linux-gnu/bits/environments.h \
 /usr/include/i386-linux-gnu/bits/confname.h /usr/include/getopt.h \
 /usr/include/pwd.h utils.h options.h userinfo.h otperror.h
otpdeluser.o: otpdeluser.cpp /usr/include/stdc-predef.h \
 /usr/include/c++/4.9/iostream \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++config.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/os_defines.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/cpu_defines.h \
 /usr/include/c++/4.9/ostream /usr/include/c++/4.9/ios \
 /usr/include/c++/4.9/iosfwd /usr/include/c++/4.9/bits/stringfwd.h \
 /usr/include/c++/4.9/bits/memoryfwd.h \
 /usr/include/c++/4.9/bits/postypes.h /usr/include/c++/4.9/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stdarg.h \
 /usr/include/i386-linux-gnu/bits/wchar.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stddef.h /usr/include/xlocale.h \
 /usr/include/c++/4.9/exception \
 /usr/include/c++/4.9/bits/atomic_lockfree_defines.h \
 /usr/include/c++/4.9/bits/char_traits.h \
 /usr/include/c++/4.9/bits/stl_algobase.h \
 /usr/include/c++/4.9/bits/functexcept.h \
 /usr/include/c++/4.9/bits/exception_defines.h \
 /usr/include/c++/4.9/bits/cpp_type_traits.h \
 /usr/include/c++/4.9/ext/type_traits.h \
 /usr/include/c++/4.9/ext/numeric_traits.h \
 /usr/include/c++/4.9/bits/stl_pair.h /usr/include/c++/4.9/bits/move.h \
 /usr/include/c++/4.9/bits/concept_check.h \
 /usr/include/c++/4.9/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.9/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.9/debug/debug.h \
 /usr/include/c++/4.9/bits/stl_iterator.h \
 /usr/include/c++/4.9/bits/ptr_traits.h \
 /usr/include/c++/4.9/bits/predefined_ops.h \
 /usr/include/c++/4.9/bits/localefwd.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++locale.h \
 /usr/include/c++/4.9/clocale /usr/include/locale.h \
 /usr/include/i386-linux-gnu/bits/locale.h /usr/include/c++/4.9/cctype \
 /usr/include/ctype.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/endian.h \
 /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/bits/byteswap.h \
 /usr/include/i386-linux-gnu/bits/byteswap-16.h \
 /usr/include/c++/4.9/bits/ios_base.h \
 /usr/include/c++/4.9/ext/atomicity.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/gthr.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/bits/timex.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/setjmp.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/atomic_word.h \
 /usr/include/c++/4.9/bits/locale_classes.h /usr/include/c++/4.9/string \
 /usr/include/c++/4.9/bits/allocator.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++allocator.h \
 /usr/include/c++/4.9/ext/new_allocator.h /usr/include/c++/4.9/new \
 /usr/include/c++/4.9/bits/ostream_insert.h \
 /usr/include/c++/4.9/bits/cxxabi_forced.h \
 /usr/include/c++/4.9/bits/stl_function.h \
 /usr/include/c++/4.9/backward/binders.h \
 /usr/include/c++/4.9/bits/range_access.h \
 /usr/include/c++/4.9/bits/basic_string.h \
 /usr/include/c++/4.9/bits/basic_string.tcc \
 /usr/include/c++/4.9/bits/locale_classes.tcc \
 /usr/include/c++/4.9/streambuf /usr/include/c++/4.9/bits/streambuf.tcc \
 /usr/include/c++/4.9/bits/basic_ios.h \
 /usr/include/c++/4.9/bits/locale_facets.h /usr/include/c++/4.9/cwctype \
 /usr/include/wctype.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/ctype_base.h \
 /usr/include/c++/4.9/bits/streambuf_iterator.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/ctype_inline.h \
 /usr/include/c++/4.9/bits/locale_facets.tcc \
 /usr/include/c++/4.9/bits/basic_ios.tcc \
 /usr/include/c++/4.9/bits/ostream.tcc /usr/include/c++/4.9/istream \
 /usr/include/c++/4.9/bits/istream.tcc /usr/include/c++/4.9/sstream \
 /usr/include/c++/4.9/bits/sstream.tcc /usr/include/c++/4.9/vector \
 /usr/include/c++/4.9/bits/stl_construct.h \
 /usr/include/c++/4.9/ext/alloc_traits.h \
 /usr/include/c++/4.9/bits/stl_uninitialized.h \
 /usr/include/c++/4.9/bits/stl_vector.h \
 /usr/include/c++/4.9/bits/stl_bvector.h \
 /usr/include/c++/4.9/bits/vector.tcc /usr/include/c++/4.9/cstdlib \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/bits/waitflags.h \
 /usr/include/i386-linux-gnu/bits/waitstatus.h \
 /usr/include/i386-linux-gnu/sys/types.h \
 /usr/include/i386-linux-gnu/sys/select.h \
 /usr/include/i386-linux-gnu/bits/select.h \
 /usr/include/i386-linux-gnu/bits/sigset.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/i386-linux-gnu/bits/stdlib-float.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h \
 /usr/include/i386-linux-gnu/bits/environments.h \
 /usr/include/i386-linux-gnu/bits/confname.h /usr/include/getopt.h \
 /usr/include/liboath/oath.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stdbool.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stdint.h /usr/include/stdint.h \
 /usr/include/string.h utils.h options.h userinfo.h otperror.h
utils.o: utils.cpp /usr/include/stdc-predef.h /usr/include/c++/4.9/vector \
 /usr/include/c++/4.9/bits/stl_algobase.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++config.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/os_defines.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/cpu_defines.h \
 /usr/include/c++/4.9/bits/functexcept.h \
 /usr/include/c++/4.9/bits/exception_defines.h \
 /usr/include/c++/4.9/bits/cpp_type_traits.h \
 /usr/include/c++/4.9/ext/type_traits.h \
 /usr/include/c++/4.9/ext/numeric_traits.h \
 /usr/include/c++/4.9/bits/stl_pair.h /usr/include/c++/4.9/bits/move.h \
 /usr/include/c++/4.9/bits/concept_check.h \
 /usr/include/c++/4.9/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.9/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.9/debug/debug.h \
 /usr/include/c++/4.9/bits/stl_iterator.h \
 /usr/include/c++/4.9/bits/ptr_traits.h \
 /usr/include/c++/4.9/bits/predefined_ops.h \
 /usr/include/c++/4.9/bits/allocator.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++allocator.h \
 /usr/include/c++/4.9/ext/new_allocator.h /usr/include/c++/4.9/new \
 /usr/include/c++/4.9/exception \
 /usr/include/c++/4.9/bits/atomic_lockfree_defines.h \
 /usr/include/c++/4.9/bits/memoryfwd.h \
 /usr/include/c++/4.9/bits/stl_construct.h \
 /usr/include/c++/4.9/ext/alloc_traits.h \
 /usr/include/c++/4.9/bits/stl_uninitialized.h \
 /usr/include/c++/4.9/bits/stl_vector.h \
 /usr/include/c++/4.9/bits/stl_bvector.h \
 /usr/include/c++/4.9/bits/range_access.h \
 /usr/include/c++/4.9/bits/vector.tcc /usr/include/c++/4.9/fstream \
 /usr/include/c++/4.9/istream /usr/include/c++/4.9/ios \
 /usr/include/c++/4.9/iosfwd /usr/include/c++/4.9/bits/stringfwd.h \
 /usr/include/c++/4.9/bits/postypes.h /usr/include/c++/4.9/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stdarg.h \
 /usr/include/i386-linux-gnu/bits/wchar.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stddef.h /usr/include/xlocale.h \
 /usr/include/c++/4.9/bits/char_traits.h \
 /usr/include/c++/4.9/bits/localefwd.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++locale.h \
 /usr/include/c++/4.9/clocale /usr/include/locale.h \
 /usr/include/i386-linux-gnu/bits/locale.h /usr/include/c++/4.9/cctype \
 /usr/include/ctype.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/endian.h \
 /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/bits/byteswap.h \
 /usr/include/i386-linux-gnu/bits/byteswap-16.h \
 /usr/include/c++/4.9/bits/ios_base.h \
 /usr/include/c++/4.9/ext/atomicity.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/gthr.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/bits/timex.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/setjmp.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/atomic_word.h \
 /usr/include/c++/4.9/bits/locale_classes.h /usr/include/c++/4.9/string \
 /usr/include/c++/4.9/bits/ostream_insert.h \
 /usr/include/c++/4.9/bits/cxxabi_forced.h \
 /usr/include/c++/4.9/bits/stl_function.h \
 /usr/include/c++/4.9/backward/binders.h \
 /usr/include/c++/4.9/bits/basic_string.h \
 /usr/include/c++/4.9/bits/basic_string.tcc \
 /usr/include/c++/4.9/bits/locale_classes.tcc \
 /usr/include/c++/4.9/streambuf /usr/include/c++/4.9/bits/streambuf.tcc \
 /usr/include/c++/4.9/bits/basic_ios.h \
 /usr/include/c++/4.9/bits/locale_facets.h /usr/include/c++/4.9/cwctype \
 /usr/include/wctype.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/ctype_base.h \
 /usr/include/c++/4.9/bits/streambuf_iterator.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/ctype_inline.h \
 /usr/include/c++/4.9/bits/locale_facets.tcc \
 /usr/include/c++/4.9/bits/basic_ios.tcc /usr/include/c++/4.9/ostream \
 /usr/include/c++/4.9/bits/ostream.tcc \
 /usr/include/c++/4.9/bits/istream.tcc \
 /usr/include/c++/4.9/bits/codecvt.h /usr/include/c++/4.9/cstdio \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/basic_file.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++io.h \
 /usr/include/c++/4.9/bits/fstream.tcc /usr/include/c++/4.9/sstream \
 /usr/include/c++/4.9/bits/sstream.tcc /usr/include/c++/4.9/cstdlib \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/bits/waitflags.h \
 /usr/include/i386-linux-gnu/bits/waitstatus.h \
 /usr/include/i386-linux-gnu/sys/types.h \
 /usr/include/i386-linux-gnu/sys/select.h \
 /usr/include/i386-linux-gnu/bits/select.h \
 /usr/include/i386-linux-gnu/bits/sigset.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/i386-linux-gnu/bits/stdlib-float.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h \
 /usr/include/i386-linux-gnu/bits/environments.h \
 /usr/include/i386-linux-gnu/bits/confname.h /usr/include/getopt.h \
 /usr/include/pwd.h /usr/include/liboath/oath.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stdbool.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stdint.h /usr/include/stdint.h \
 /usr/include/string.h utils.h options.h userinfo.h otperror.h
options.o: options.cpp /usr/include/stdc-predef.h \
 /usr/include/c++/4.9/string \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++config.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/os_defines.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/cpu_defines.h \
 /usr/include/c++/4.9/bits/stringfwd.h \
 /usr/include/c++/4.9/bits/memoryfwd.h \
 /usr/include/c++/4.9/bits/char_traits.h \
 /usr/include/c++/4.9/bits/stl_algobase.h \
 /usr/include/c++/4.9/bits/functexcept.h \
 /usr/include/c++/4.9/bits/exception_defines.h \
 /usr/include/c++/4.9/bits/cpp_type_traits.h \
 /usr/include/c++/4.9/ext/type_traits.h \
 /usr/include/c++/4.9/ext/numeric_traits.h \
 /usr/include/c++/4.9/bits/stl_pair.h /usr/include/c++/4.9/bits/move.h \
 /usr/include/c++/4.9/bits/concept_check.h \
 /usr/include/c++/4.9/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.9/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.9/debug/debug.h \
 /usr/include/c++/4.9/bits/stl_iterator.h \
 /usr/include/c++/4.9/bits/ptr_traits.h \
 /usr/include/c++/4.9/bits/predefined_ops.h \
 /usr/include/c++/4.9/bits/postypes.h /usr/include/c++/4.9/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stdarg.h \
 /usr/include/i386-linux-gnu/bits/wchar.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stddef.h /usr/include/xlocale.h \
 /usr/include/c++/4.9/bits/allocator.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++allocator.h \
 /usr/include/c++/4.9/ext/new_allocator.h /usr/include/c++/4.9/new \
 /usr/include/c++/4.9/exception \
 /usr/include/c++/4.9/bits/atomic_lockfree_defines.h \
 /usr/include/c++/4.9/bits/localefwd.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++locale.h \
 /usr/include/c++/4.9/clocale /usr/include/locale.h \
 /usr/include/i386-linux-gnu/bits/locale.h /usr/include/c++/4.9/iosfwd \
 /usr/include/c++/4.9/cctype /usr/include/ctype.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/endian.h \
 /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/bits/byteswap.h \
 /usr/include/i386-linux-gnu/bits/byteswap-16.h \
 /usr/include/c++/4.9/bits/ostream_insert.h \
 /usr/include/c++/4.9/bits/cxxabi_forced.h \
 /usr/include/c++/4.9/bits/stl_function.h \
 /usr/include/c++/4.9/backward/binders.h \
 /usr/include/c++/4.9/bits/range_access.h \
 /usr/include/c++/4.9/bits/basic_string.h \
 /usr/include/c++/4.9/ext/atomicity.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/gthr.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/bits/timex.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/setjmp.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/atomic_word.h \
 /usr/include/c++/4.9/bits/basic_string.tcc /usr/include/c++/4.9/vector \
 /usr/include/c++/4.9/bits/stl_construct.h \
 /usr/include/c++/4.9/ext/alloc_traits.h \
 /usr/include/c++/4.9/bits/stl_uninitialized.h \
 /usr/include/c++/4.9/bits/stl_vector.h \
 /usr/include/c++/4.9/bits/stl_bvector.h \
 /usr/include/c++/4.9/bits/vector.tcc /usr/include/c++/4.9/fstream \
 /usr/include/c++/4.9/istream /usr/include/c++/4.9/ios \
 /usr/include/c++/4.9/bits/ios_base.h \
 /usr/include/c++/4.9/bits/locale_classes.h \
 /usr/include/c++/4.9/bits/locale_classes.tcc \
 /usr/include/c++/4.9/streambuf /usr/include/c++/4.9/bits/streambuf.tcc \
 /usr/include/c++/4.9/bits/basic_ios.h \
 /usr/include/c++/4.9/bits/locale_facets.h /usr/include/c++/4.9/cwctype \
 /usr/include/wctype.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/ctype_base.h \
 /usr/include/c++/4.9/bits/streambuf_iterator.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/ctype_inline.h \
 /usr/include/c++/4.9/bits/locale_facets.tcc \
 /usr/include/c++/4.9/bits/basic_ios.tcc /usr/include/c++/4.9/ostream \
 /usr/include/c++/4.9/bits/ostream.tcc \
 /usr/include/c++/4.9/bits/istream.tcc \
 /usr/include/c++/4.9/bits/codecvt.h /usr/include/c++/4.9/cstdio \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/basic_file.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++io.h \
 /usr/include/c++/4.9/bits/fstream.tcc /usr/include/c++/4.9/sstream \
 /usr/include/c++/4.9/bits/sstream.tcc /usr/include/c++/4.9/algorithm \
 /usr/include/c++/4.9/utility /usr/include/c++/4.9/bits/stl_relops.h \
 /usr/include/c++/4.9/bits/stl_algo.h /usr/include/c++/4.9/cstdlib \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/bits/waitflags.h \
 /usr/include/i386-linux-gnu/bits/waitstatus.h \
 /usr/include/i386-linux-gnu/sys/types.h \
 /usr/include/i386-linux-gnu/sys/select.h \
 /usr/include/i386-linux-gnu/bits/select.h \
 /usr/include/i386-linux-gnu/bits/sigset.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/i386-linux-gnu/bits/stdlib-float.h \
 /usr/include/c++/4.9/bits/algorithmfwd.h \
 /usr/include/c++/4.9/bits/stl_heap.h \
 /usr/include/c++/4.9/bits/stl_tempbuf.h /usr/include/c++/4.9/iostream \
 options.h otperror.h
userinfo.o: userinfo.cpp /usr/include/stdc-predef.h \
 /usr/include/c++/4.9/string \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++config.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/os_defines.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/cpu_defines.h \
 /usr/include/c++/4.9/bits/stringfwd.h \
 /usr/include/c++/4.9/bits/memoryfwd.h \
 /usr/include/c++/4.9/bits/char_traits.h \
 /usr/include/c++/4.9/bits/stl_algobase.h \
 /usr/include/c++/4.9/bits/functexcept.h \
 /usr/include/c++/4.9/bits/exception_defines.h \
 /usr/include/c++/4.9/bits/cpp_type_traits.h \
 /usr/include/c++/4.9/ext/type_traits.h \
 /usr/include/c++/4.9/ext/numeric_traits.h \
 /usr/include/c++/4.9/bits/stl_pair.h /usr/include/c++/4.9/bits/move.h \
 /usr/include/c++/4.9/bits/concept_check.h \
 /usr/include/c++/4.9/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.9/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.9/debug/debug.h \
 /usr/include/c++/4.9/bits/stl_iterator.h \
 /usr/include/c++/4.9/bits/ptr_traits.h \
 /usr/include/c++/4.9/bits/predefined_ops.h \
 /usr/include/c++/4.9/bits/postypes.h /usr/include/c++/4.9/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stdarg.h \
 /usr/include/i386-linux-gnu/bits/wchar.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stddef.h /usr/include/xlocale.h \
 /usr/include/c++/4.9/bits/allocator.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++allocator.h \
 /usr/include/c++/4.9/ext/new_allocator.h /usr/include/c++/4.9/new \
 /usr/include/c++/4.9/exception \
 /usr/include/c++/4.9/bits/atomic_lockfree_defines.h \
 /usr/include/c++/4.9/bits/localefwd.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++locale.h \
 /usr/include/c++/4.9/clocale /usr/include/locale.h \
 /usr/include/i386-linux-gnu/bits/locale.h /usr/include/c++/4.9/iosfwd \
 /usr/include/c++/4.9/cctype /usr/include/ctype.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/endian.h \
 /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/bits/byteswap.h \
 /usr/include/i386-linux-gnu/bits/byteswap-16.h \
 /usr/include/c++/4.9/bits/ostream_insert.h \
 /usr/include/c++/4.9/bits/cxxabi_forced.h \
 /usr/include/c++/4.9/bits/stl_function.h \
 /usr/include/c++/4.9/backward/binders.h \
 /usr/include/c++/4.9/bits/range_access.h \
 /usr/include/c++/4.9/bits/basic_string.h \
 /usr/include/c++/4.9/ext/atomicity.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/gthr.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/bits/timex.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/setjmp.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/atomic_word.h \
 /usr/include/c++/4.9/bits/basic_string.tcc /usr/include/c++/4.9/sstream \
 /usr/include/c++/4.9/istream /usr/include/c++/4.9/ios \
 /usr/include/c++/4.9/bits/ios_base.h \
 /usr/include/c++/4.9/bits/locale_classes.h \
 /usr/include/c++/4.9/bits/locale_classes.tcc \
 /usr/include/c++/4.9/streambuf /usr/include/c++/4.9/bits/streambuf.tcc \
 /usr/include/c++/4.9/bits/basic_ios.h \
 /usr/include/c++/4.9/bits/locale_facets.h /usr/include/c++/4.9/cwctype \
 /usr/include/wctype.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/ctype_base.h \
 /usr/include/c++/4.9/bits/streambuf_iterator.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/ctype_inline.h \
 /usr/include/c++/4.9/bits/locale_facets.tcc \
 /usr/include/c++/4.9/bits/basic_ios.tcc /usr/include/c++/4.9/ostream \
 /usr/include/c++/4.9/bits/ostream.tcc \
 /usr/include/c++/4.9/bits/istream.tcc \
 /usr/include/c++/4.9/bits/sstream.tcc /usr/include/c++/4.9/fstream \
 /usr/include/c++/4.9/bits/codecvt.h /usr/include/c++/4.9/cstdio \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/basic_file.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++io.h \
 /usr/include/c++/4.9/bits/fstream.tcc /usr/include/c++/4.9/iostream \
 /usr/include/i386-linux-gnu/sys/stat.h \
 /usr/include/i386-linux-gnu/bits/stat.h userinfo.h options.h \
 /usr/include/c++/4.9/vector /usr/include/c++/4.9/bits/stl_construct.h \
 /usr/include/c++/4.9/ext/alloc_traits.h \
 /usr/include/c++/4.9/bits/stl_uninitialized.h \
 /usr/include/c++/4.9/bits/stl_vector.h \
 /usr/include/c++/4.9/bits/stl_bvector.h \
 /usr/include/c++/4.9/bits/vector.tcc utils.h otperror.h
otperror.o: otperror.cpp /usr/include/stdc-predef.h \
 /usr/include/c++/4.9/string \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++config.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/os_defines.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/cpu_defines.h \
 /usr/include/c++/4.9/bits/stringfwd.h \
 /usr/include/c++/4.9/bits/memoryfwd.h \
 /usr/include/c++/4.9/bits/char_traits.h \
 /usr/include/c++/4.9/bits/stl_algobase.h \
 /usr/include/c++/4.9/bits/functexcept.h \
 /usr/include/c++/4.9/bits/exception_defines.h \
 /usr/include/c++/4.9/bits/cpp_type_traits.h \
 /usr/include/c++/4.9/ext/type_traits.h \
 /usr/include/c++/4.9/ext/numeric_traits.h \
 /usr/include/c++/4.9/bits/stl_pair.h /usr/include/c++/4.9/bits/move.h \
 /usr/include/c++/4.9/bits/concept_check.h \
 /usr/include/c++/4.9/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.9/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.9/debug/debug.h \
 /usr/include/c++/4.9/bits/stl_iterator.h \
 /usr/include/c++/4.9/bits/ptr_traits.h \
 /usr/include/c++/4.9/bits/predefined_ops.h \
 /usr/include/c++/4.9/bits/postypes.h /usr/include/c++/4.9/cwchar \
 /usr/include/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stdarg.h \
 /usr/include/i386-linux-gnu/bits/wchar.h \
 /usr/lib/gcc/i586-linux-gnu/4.9/include/stddef.h /usr/include/xlocale.h \
 /usr/include/c++/4.9/bits/allocator.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++allocator.h \
 /usr/include/c++/4.9/ext/new_allocator.h /usr/include/c++/4.9/new \
 /usr/include/c++/4.9/exception \
 /usr/include/c++/4.9/bits/atomic_lockfree_defines.h \
 /usr/include/c++/4.9/bits/localefwd.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/c++locale.h \
 /usr/include/c++/4.9/clocale /usr/include/locale.h \
 /usr/include/i386-linux-gnu/bits/locale.h /usr/include/c++/4.9/iosfwd \
 /usr/include/c++/4.9/cctype /usr/include/ctype.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/endian.h \
 /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/bits/byteswap.h \
 /usr/include/i386-linux-gnu/bits/byteswap-16.h \
 /usr/include/c++/4.9/bits/ostream_insert.h \
 /usr/include/c++/4.9/bits/cxxabi_forced.h \
 /usr/include/c++/4.9/bits/stl_function.h \
 /usr/include/c++/4.9/backward/binders.h \
 /usr/include/c++/4.9/bits/range_access.h \
 /usr/include/c++/4.9/bits/basic_string.h \
 /usr/include/c++/4.9/ext/atomicity.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/gthr.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
 /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/bits/timex.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/setjmp.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/atomic_word.h \
 /usr/include/c++/4.9/bits/basic_string.tcc /usr/include/c++/4.9/sstream \
 /usr/include/c++/4.9/istream /usr/include/c++/4.9/ios \
 /usr/include/c++/4.9/bits/ios_base.h \
 /usr/include/c++/4.9/bits/locale_classes.h \
 /usr/include/c++/4.9/bits/locale_classes.tcc \
 /usr/include/c++/4.9/streambuf /usr/include/c++/4.9/bits/streambuf.tcc \
 /usr/include/c++/4.9/bits/basic_ios.h \
 /usr/include/c++/4.9/bits/locale_facets.h /usr/include/c++/4.9/cwctype \
 /usr/include/wctype.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/ctype_base.h \
 /usr/include/c++/4.9/bits/streambuf_iterator.h \
 /usr/include/i386-linux-gnu/c++/4.9/bits/ctype_inline.h \
 /usr/include/c++/4.9/bits/locale_facets.tcc \
 /usr/include/c++/4.9/bits/basic_ios.tcc /usr/include/c++/4.9/ostream \
 /usr/include/c++/4.9/bits/ostream.tcc \
 /usr/include/c++/4.9/bits/istream.tcc \
 /usr/include/c++/4.9/bits/sstream.tcc otperror.h
