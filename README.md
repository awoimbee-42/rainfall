# RainFall

## What this is

RainFall is the second security project at 42, it's organised like a CTF with levels.

This project focuses on exploiting binaries, mostly using buffer overflows.

## How to use

Before anything, run `make`, a helpful description of every command will show up.

* If you are running linux and have libvirt (and `virsh`, `dnsmasq`, `ebtables`): just run `make start` ;)

* Otherwise you will need to download the projects ISO: `make RainFall.iso` and then setup a VM yourself.
Using this method you won't be able to use:
  * `make start`
  * `make stop` / `make shutdown`
  * `make ip`
  * `make list-vm`
  * `make network`

You will then be able to connect to the virtual machine through ssh.

### How to connect through ssh

```bash
user=level0 # level0 to level9 or bonus0 to bonus3
ip=192.168.122.237 # The ip is given by make start, make ip, and by the VM itself when it starts
ssh -p 4242 $user@$ip
```

```raw
The password to user `level0` is `level0`.
The password to user `level1` is in level0/flag
The password to user `level2` is in level1/flag
(...)
The password to user `bonus0` is in level9/flag
(...)
```
