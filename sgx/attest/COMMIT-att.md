Workflow
---

* user codes, compiles, uploads binary to cloud
* cloud loads SGX binary
    * ECREATE: set up environment
    * EADD: commit physical pages
    * EEXTEND: digest
    * EINIT: seal and sign
* (attestation between cloud and user)
    * Between Source (E1) and Destination (E2) Enclaves
    * Secure Channel Establishment: DH
* cloud executes SGX binary
    * EENTER: transfer control to TCS
    * EEXIT: transfer control out of TCS, synchronously
    * AEX/ERESUME: asynchronously exit and resume enclave code
    * Session
        *  Enclave to Enclave Call
        *  Message Exchange
    * Close Session



Overview
---

||classic crypto||sgx||
|---|---|---|---|---|
||sec. channel/sigma|sec. channel| local att.|remote att./sigma-like|
|1.1 authenticate| PKI || | EPID|
|1.2 key nego.| RSA | DH | EC-DH |EC-DSA|
|2. msg transm.|AES+MAC| same | same | same |

Local Attestation 
---

* Between Source (E1) and Destination (E2) Enclaves
1. Secure Channel Establishment: DH
2. Session
    2. Enclave to Enclave Call 
    3. Message Exchange
4. Close Session 

#### Secure channel establishment

* SGX `EREPORT` mechanism
* based on DH key-exchange (`sgx_dh.h`,`libsgx_tservice.a`)

```
      E2/dest                E1/src           

      Z_p*                   Z_p*
Pre   g                      g
=======================================
                             
        + <------------------+
        |     oc + ec
        |      
     randomly gen.
     x in Z_p*
        |        g^x
        +------------------> g^x
          oc.ret + ec.ret
                             y in Z_p*
                 g^y         |
     g^y <-------------------+
        |     oc + ec
        |
        +------------------->

     g^{y*x}=K               g^{x*y}=K
=======================================
Post  K                      K
```