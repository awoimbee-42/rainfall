ifeq ($(tmpdir),)
location = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
self := $(location)
.PHONY: all
all: help
%:
	@tmpdir=`mktemp --tmpdir -d`; \
	trap 'rm -rf "$$tmpdir"' EXIT; \
	$(MAKE) -f $(self) --no-print-directory tmpdir=$$tmpdir $@
else

RainFall.iso:
	./bin/fetch_iso.sh

vm_def.xml:
	sed "s|%%RAINFALL_ISO%%|$${PWD}/RainFall.iso|" bin/vm_def.xml > $@

executables:
	mkdir executables || true

executables/%: | executables
	@nb=$$(echo $* | sed 's|[a-z]*||') \
	&& str=$$(echo $* | sed 's|\([a-z]*\)[0-9]*|\1|') \
	&& pass=$$(cat ./$${str}$$(expr $${nb} - 1)/flag || echo level0) \
	&& echo "echo $$pass" > $(tmpdir)/$* && chmod +x $(tmpdir)/$* \
	&& echo "Copying files from $* ($$pass)" \
	&& SSH_ASKPASS="$(tmpdir)/$*" setsid scp -P 4242 '$*@192.168.122.237:~/*' "executables" 2>/dev/null

EXECUTABLES := $(addprefix executables/, $(shell printf 'level%d ' {0..10})) #$(shell printf 'bonus%d' {0..10})

extract_exes: $(EXECUTABLES) ## Extract all the important files from the VM

.PHONY:	header start ip stop shutdown shutdown-hard list-vm network clean fclean help

header:
	toilet -w 9999 -f mono12 'level X'

start: vm_def.xml RainFall.iso ## Start the vm and print its IP
	sudo virsh create ./vm_def.xml
	sudo virsh list
	@$(MAKE) ip

ip: ## Prints the ip
	sudo virsh net-dhcp-leases default | grep RainFall || echo "VM doesn't have an IP (yet ?)"

stop: shutdown ## Shutdown alias

shutdown: shutdown-hard ## Shutdown and delete vm

shutdown-hard:
	sudo virsh destroy rainfall

list-vm: ## See if the vm is running
	sudo virsh list --all

network: ## Can fix network issues with the VM
	@command -V dnsmasq
	@command -V ebtables
	@command -V virsh
	if [ "$$(sudo virsh net-list | grep default)" ]; then \
		echo 'Nothing to be done here !'; \
	else \
		sudo virsh net-define bin/network_def.xml || true; \
		sudo virsh net-autostart default || true; \
		sudo virsh net-start default; \
	fi

clean: shutdown ##
	rm -rf vm_def.xml e_tmp executables

fclean: clean ## hardcore clean
	rm -rf RainFall.iso

help: ## Show this help.
	@perl -e '$(HELP_FUN)' $(MAKEFILE_LIST)
	@printf "Connect to the VM through ssh at port 4242:\n"
	@printf "\tssh -p 4242 level00@192.168.122.237\n"


.DEFAULT_GOAL = help
SHELL := /bin/bash

GREEN := $(shell command -v tput >/dev/null 2>&1 && tput -Txterm setaf 2 || echo "")
YELLOW := $(shell command -v tput >/dev/null 2>&1 && tput -Txterm setaf 3 || echo "")
RED := $(shell command -v tput >/dev/null 2>&1 && tput -Txterm setaf 1 || echo "")
RESET := $(shell command -v tput >/dev/null 2>&1 && tput -Txterm sgr0 || echo "")

HELP_FUN = %help; \
	while(<>) { push @{$$help{$$2 // "Other"}}, [$$1, $$3] if /^([a-zA-Z\-._]+)\s*:.*\#\#(?:@([a-zA-Z\-_]+))?\s(.*)$$/ }; \
	print "$(RESET)project: $(PURPLE)$(NAME)$(RESET)\n"; \
	print "usage: make [target]\n\n"; \
	for (sort keys %help) { \
	print "$$_:\n"; \
	for (@{$$help{$$_}}) { \
	$$sep = " " x (25 - length $$_->[0]); \
	print " ${YELLOW}$$_->[0]${RESET}$$sep${GREEN}$$_->[1]${RESET}\n"; \
	}; \
	print "\n"; }

endif
