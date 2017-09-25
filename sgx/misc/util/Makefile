SGX_SDK ?= /opt/intel/sgxsdk
SGX_EDGER8R := $(SGX_SDK)/bin/x64/sgx_edger8r

all: edl cc

edl:
	$(SGX_EDGER8R) demo.edl 

cc:
	gcc demo_*.c main_u.c -I$(SGX_SDK)/include
