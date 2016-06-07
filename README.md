# ipc example #

Motivation: sometimes there is a discourse that 0mq unfortunately doesn't implement the *ipc* transport on Windows.

This must not be a killer argument in case of modular design. If a middleware is not available on a platform - use another one via configuration.

This example is deliberately limited in scope. While the behavior (sync vs. async/buffering/etc..) is not defined in an abstraction,
the `send` and `receive` methods of zeromq and nanomsg sockets are hidden behind a unified facade.

On Windows the nanomsg ipc socket pair is selected. On other platforms - zeromq.

Windows:

```
On windows: true
Sink is: nn:ipc:///tmp/reqrep
Source is: nn:ipc:///tmp/reqrep
received: hi
Sink is: nn:ipc:///tmp/nreqrep
Source is: nn:ipc:///tmp/nreqrep
received: hi
```
