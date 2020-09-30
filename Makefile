.PHONY: start shutdown shutdown-force network clean help ip

header:
	toilet -w 9999 -f mono12 'level X'

RainFall.iso:
	./bin/fetch_iso.sh

vm_def.xml:
	sed "s|%%RAINFALL_ISO%%|$${PWD}/RainFall.iso|" bin/vm_def.xml > $@

start: vm_def.xml RainFall.iso ## start the vm and print its IP
	sudo virsh create ./vm_def.xml
	sudo virsh list
	@$(MAKE) ip

ip: ## Prints the ip
	sudo virsh net-dhcp-leases default | grep RainFall || echo "VM doesn't have an IP (yet ?)"

#shutdown: ## shutdown and delete vm
#	sudo virsh shutdown rainfall

shutdown: ## quick shutdown & delete vm
	sudo virsh destroy rainfall

list-vm: ## To see if the vm is running
	sudo virsh list --all

network: ## Can fix network issues with the VM
ifeq ($(shell sudo virsh net-list | grep default),)
	sudo virsh net-define bin/network_def.xml || true
	sudo virsh net-autostart default || true
	sudo virsh net-start default
else
	@echo 'Nothing to be done here !'
endif

clean: shutdown ##
	rm -f RainFall.iso vm_def.xml

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
