include 'premake'
zmq = assert(require('zeromq'))
nn = assert(require('nanomsg'))

make_solution 'test'

includedirs {
    'src/example',
    'deps/cppzmq',
    'deps/cppnanomsg',
}

defines {
    'ZMQ_HAS_RVALUE_REFS'
}

zmq.dirs()
nn.dirs()

make_console_app('test', {
    'src/example/**.cpp',
    'src/example_main/**.cpp',
    'src/example/**.h'
})
use_standard('c++14')
zmq.link()
zmq.deploy()
nn.link()
nn.deploy()
run_target_after_build()
