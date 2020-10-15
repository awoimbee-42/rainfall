SHELL := /bin/bash
.DEFAULT_GOAL = help

GRN := $(shell command -v tput >/dev/null 2>&1 && tput -Txterm setaf 2 || echo "")
YLW := $(shell command -v tput >/dev/null 2>&1 && tput -Txterm setaf 3 || echo "")
RED := $(shell command -v tput >/dev/null 2>&1 && tput -Txterm setaf 1 || echo "")
RST := $(shell command -v tput >/dev/null 2>&1 && tput -Txterm sgr0 || echo "")

ifeq ($(shell command -v virsh),)
$(info $(RED) /!\ virsh is required to run the VM $(RST))
endif
ifneq ($(shell command -v dnsmasq ebtables | wc -l),2)
$(info $(RED) /!\ dnsmasq & ebtables are required to setup the network $(RST))
endif

RainFall.iso:
	./bin/fetch_iso.sh

vm_def.xml:
	sed "s|%%RAINFALL_ISO%%|$${PWD}/RainFall.iso|" bin/vm_def.xml > $@

EXE = $(shell printf 'level%d ' {0..9}) $(shell printf 'bonus%d ' {0..3})
EXE_RECREATED = $(addsuffix _recreated, $(EXE))
EXECUTABLES := $(addprefix executables/, $(EXE) $(EXE_RECREATED))

executables:
	mkdir executables || true

executables/%_recreated: | executables
	gcc -m32 $*/source.c -o $@

define set_pass
if [ "$(1)$(2)" = "level0" ]; \
then echo "level0"; \
elif [ "$(1)$(2)" = "bonus0" ]; \
then echo $$(cat ./level9/flag 2>/dev/null || true) \
else echo $$(cat ./$(1)$$(expr $(2) - 1)/flag 2>/dev/null || true); \
fi
endef

executables/%: | executables
	@get_pass() { \
		if [ "$$1$$2" = "level0" ]; then \
			echo "level0"; \
		elif [ "$$1$$2" = "bonus0" ]; then \
			echo $$(cat ./level9/flag 2>/dev/null || true); \
		else \
			echo $$(cat ./$$1$$(expr $$2 - 1)/flag 2>/dev/null || true); \
		fi \
	} \
	&& nb=$$(echo $* | sed 's|[a-z]*||') \
	&& str=$$(echo $* | sed 's|\([a-z]*\)[0-9]*|\1|') \
	&& pass="$$(get_pass $$str $$nb)" \
	&& if [[ -z "$$pass" ]]; then echo "Flag for $* not present" && exit; fi \
	&& echo "Copying files from $* ($$pass)" \
	&& echo "echo $$pass" > mkftmp-$* && chmod +x mkftmp-$* \
	&& SSH_ASKPASS="$(CURDIR)/mkftmp-$*" setsid scp -P 4242 '$*@192.168.122.237:~/*' "executables" 2>/dev/null \
	&& rm mkftmp-$*

.PHONY: extract_exes header start ip stop shutdown shutdown-hard list-vm network clean fclean help

get_executables: $(EXECUTABLES) ## Extracts and compiles al the executables

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

HELP_FUN = %help; \
	while(<>) { push @{$$help{$$2 // "Other"}}, [$$1, $$3] if /^([a-zA-Z\-._]+)\s*:.*\#\#(?:@([a-zA-Z\-_]+))?\s(.*)$$/ }; \
	print "$(RST)project: $(PURPLE)$(NAME)$(RST)\n"; \
	print "usage: make [target]\n\n"; \
	for (sort keys %help) { \
	print "$$_:\n"; \
	for (@{$$help{$$_}}) { \
	$$sep = " " x (25 - length $$_->[0]); \
	print " ${YLW}$$_->[0]${RST}$$sep${GRN}$$_->[1]${RST}\n"; \
	}; \
	print "\n"; }
