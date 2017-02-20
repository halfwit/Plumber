# plumber
=========

Scripts and binaries to action on arbitrary strings, including URLs.
This tool uses content-type, a simple binary to fetch a decent analogue of a mime type for a given link.

##Configuration
---------------

##Installation
--------------

This script comes with several files that you will have to modify to match your system. These will be installed into your $XDG_DATA_HOME/plumber directory. 
It also integrates with https://github.com/halfwit/dsearch for handling both manpage entries missed plumbs.

##Examples
----------

###edit
```sh
#!/bin/sh
EDIT=vis
st "$EDIT" "$@"
```

###play
```sh
#!/bin/sh
# Open or append to playlist
if ! pgrep mpv; then
	mpv --input-ipc-server=/tmp/mpvsock "$@"
else
	echo ' { "command": ["loadfile", "'"$1"'", "append-play"] }' socat - /tmp/mpvsock
fi
```

###browse
```sh
#!/bin/sh

exec surf "$@"
```

###docs
```sh
#!/bin/sh

exec zathura "$@"
```

###listen
```sh
#!/bin/sh

exec mpv "$@"
```
