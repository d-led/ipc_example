include 'premake'

make_solution 'test'
make_console_app('test', {
    'src/example/**.cpp',
    'src/example/**.h'
}) 
use_standard('c++14')
run_target_after_build()
