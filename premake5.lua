include 'premake'
zmq = assert(require('zeromq'))

make_solution 'test'

includedirs {
    'src/example'
}

zmq.dirs()

make_console_app('test', {
    'src/example/**.cpp',
    'src/example_main/**.cpp',
    'src/example/**.h'
})
use_standard('c++14')
zmq.link()
zmq.deploy()
run_target_after_build()
