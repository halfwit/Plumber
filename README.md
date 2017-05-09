# plumber
=========

Scripts and binaries to action on arbitrary strings, including URLs.
This tool uses [content-type](https://github.com/halfwit/content-type), a simple binary to fetch a decent analogue of a mime type for a given link.

## Configuration
---------------

You can copy the included configurations of cfg/plumber, or provide your own behavior
Modify edit, play, etc to meet your needs. This is suboptimal, and will be changed in the future
(It's likely that in the future, this will lean on $XDG\_DATA\_HOME)

The script will source a file at $XDG_CONFIG_HOME/plumber/special, which should be a runnable script that will `exit 1` if a match is found (this is used for special cases, like youtube)

## Installation
--------------

PREFIX=myprefix make install

## Examples
----------

### edit
```sh
#!/bin/sh
EDIT=vis
st "$EDIT" "$@"
```

### play
```sh
#!/bin/sh
# Open or append to playlist
if ! pgrep mpv; then
	mpv --input-ipc-server=/tmp/mpvsock "$@"
else
	echo ' { "command": ["loadfile", "'"$1"'", "append-play"] }' socat - /tmp/mpvsock
fi
```

### browse
```sh
#!/bin/sh

exec surf "$@"
```

### docs
```sh
#!/bin/sh

exec zathura "$@"
```

### listen
```sh
#!/bin/sh

exec mpv "$@"
```

### special
```sh
#!/bin/sh

case "$@" in
	*youtube.com*)	play "$@" &
					exit 1 ;;
	*webm*)			play "$@" &
					exit 1 ;;
esac

exit 0
