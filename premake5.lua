include 'premake'

make_solution 'test'

includedirs {
    'src/example'
}

make_console_app('test', {
    'src/example/**.cpp',
    'src/example_main/**.cpp',
    'src/example/**.h'
})
use_standard('c++14')
run_target_after_build()
