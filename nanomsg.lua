local nanomsg = {}
-------------------------------
nanomsg.root = {
    osx = [[/usr/local/Cellar/nanomsg/0.8-beta/]] -- brew install nanomsg
}

nanomsg.lib = {
    osx = 'nanomsg',
}

nanomsg.dirs = function()
    configuration 'macosx'
        includedirs { path.join(nanomsg.root.osx,'include') }
        libdirs { path.join(nanomsg.root.osx,'lib') }
    configuration '*'
end

nanomsg.deploy = function()
end

nanomsg.link = function()
    configuration 'macosx'
        links {
            nanomsg.lib.osx,
        }
    configuration '*'
end

return nanomsg
