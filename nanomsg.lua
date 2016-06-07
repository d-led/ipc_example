local nanomsg = {}
-------------------------------
nanomsg.root = {
    osx = [[/usr/local/Cellar/nanomsg/0.8-beta/]], -- brew install nanomsg
    win = [[deps/nanomsg]]
}

nanomsg.lib = {
    osx = 'nanomsg',
    win = 'nanomsg'
}

nanomsg.dirs = function()
    configuration 'macosx'
        includedirs { path.join(nanomsg.root.osx,'include') }
        libdirs { path.join(nanomsg.root.osx,'lib') }
    configuration {'x32','windows'}
        includedirs { path.join(nanomsg.root.win,'install/windows/x32/include') }
        libdirs { path.join(nanomsg.root.win,'install/windows/x32/lib') }
    configuration {'x64','windows'}
        includedirs { path.join(nanomsg.root.win,'install/windows/x64/include') }
        libdirs { path.join(nanomsg.root.win,'install/windows/x64/lib') }
    configuration '*'
end

function post_build_deploy(what)
    local command
    if os.get() == 'windows' then
        command = [[xcopy "]]..path.getabsolute(what):gsub('/','\\')..[[" "$(TargetDir)" /s /d /y]]
    else
        command = 'cp ' .. path.getabsolute(what) .. [[ "$(TARGETDIR)"]]
    end
    -- print(command)
    postbuildcommands {
        command
    }
end

nanomsg.deploy = function()
    configuration {'x32','windows'}
        post_build_deploy(path.join(nanomsg.root.win,'install/windows/x32/bin/*.dll'))
    configuration {'x64','windows'}
        post_build_deploy(path.join(nanomsg.root.win,'install/windows/x64/bin/*.dll'))
    configuration '*'
end

nanomsg.link = function()
    configuration 'macosx'
        links {
            nanomsg.lib.osx,
        }
    configuration 'windows'
        links {
            nanomsg.lib.win,
        }
    configuration '*'
end

return nanomsg
