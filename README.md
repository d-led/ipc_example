# ipc example #

Motivation: sometimes there is a discourse that 0mq unfortunately doesn't implement the *ipc* transport on Windows.

UPD [2019+](https://github.com/zeromq/libzmq/issues/3691): [ZeroMQ supports IPC on Windows](https://github.com/zeromq/pyzmq/pull/1570)

This must not be a killer argument in case of modular design. If a middleware is not available on a platform - use another one via configuration.

This example is deliberately limited in scope. While the behavior (sync vs. async/buffering/etc..) is not defined in an abstraction,
the `send` and `receive` methods of zeromq and nanomsg sockets are hidden behind a unified facade.

On Windows the nanomsg ipc socket pair is selected. On other platforms - zeromq. The example first creates and uses a default socket, and then, explicitly, a nanomsg one.

Windows ([zeromq 4.0.4](http://zeromq.org/distro:microsoft-windows) expected to be installed globally):

```
On windows: true
Sink is: nn:ipc:///tmp/reqrep
Source is: nn:ipc:///tmp/reqrep
received: hi
Sink is: nn:ipc:///tmp/nreqrep
Source is: nn:ipc:///tmp/nreqrep
received: hi
```

Linux (nn statically linked and installed globally for simplicity):

```
On windows: false
Sink is: 0mq:ipc:///tmp/reqrep
Source is: 0mq:ipc:///tmp/reqrep
received: hi
received after reconnect: ho
Sink is: nn:ipc:///tmp/nreqrep
Source is: nn:ipc:///tmp/nreqrep
received: hi
```

## Used in the project ##

- [zeromq](http://zero.mq/)
- [nanomsg](http://nanomsg.org/)
- [premake](https://premake.github.io/) + some helpers
- [cppzmq](https://github.com/zeromq/cppzmq)
- [cppnanomsg](https://github.com/nanomsg/cppnanomsg)
