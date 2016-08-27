# content-type
Simple binary to parse content-type of url that is passed in - currently a slightly hacky mess of horrors. 
`content-type <url>`
curl -I <url> | grep content-type turns out to be a bit of a crapshoot. This works much more simply.
