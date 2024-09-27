# SPDX-License-Identifier: MIT

uapi_opt = get_option('uapi')
o_dir = meson.current_build_dir()
uapi_env = environment()
uapi_env.set('ARCH', libevl_arch)
uapi_env.set('UAPI', uapi_opt)
uapi_env.set('OUTPUT_DIR', o_dir)
run_command(libevl_scripts / 'setup-uapi.sh',
    check : true,
    env : uapi_env
)

arch_incdir = '../lib/arch' / libevl_arch / 'include'
libevl_incdirs = include_directories(
    '.',
    arch_incdir,
)

libevl_headers = [
    'evl/atomic.h',
    'evl/clock.h',
    'evl/compat.h',
    'evl/compiler.h',
    'evl/event.h',
    'evl/evl.h',
    'evl/flags.h',
    'evl/heap.h',
    'evl/list.h',
    'evl/mutex.h',
    'evl/observable.h',
    'evl/poll.h',
    'evl/proxy.h',
    'evl/ring_ptr.h',
    'evl/rwlock.h',
    'evl/sched.h',
    'evl/sem.h',
    'evl/syscall.h',
    'evl/sys.h',
    'evl/thread.h',
    'evl/timer.h',
    'evl/xbuf.h',
]

install_headers(
    libevl_headers,
    subdir : 'evl'
)

libevl_net_headers = [
    'evl/net/socket.h',
]

install_headers(
    libevl_net_headers,
    subdir : 'evl/net'
)
