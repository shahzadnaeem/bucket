# Security

Verifying a site's certificate

## openssl Verification

Use openssl s_client to check the status of a site's SSL Certificate

```shell
$ openssl s_client -connect bbc.co.uk:443
```

> Verify return code: 0 (ok) <br>
> \---
>
> You will need to Ctrl-D or Ctrl-C to exit the above command

To see the certificate chain add *-showcerts*

```shell
$ openssl s_client -connect bbc.co.uk:443 -showcerts
```

> ... <br>
> Certificate chain <br>
> 0 s:/C=GB/ST=London/L=London/O=British Broadcasting Corporation/CN=*.bbc.co.uk <br>
>   i:/C=BE/O=GlobalSign nv-sa/CN=GlobalSign Organization Validation CA - SHA256 - G2 <br>
> -----BEGIN CERTIFICATE----- <br>
> MIIFdDCCBFygAwIBAgISESHaDZOvlX/ywkcPKcj0RTp7MA0GCSqGSIb3DQEBCwUA <br>
> ...

The above does not verify if the certificate matches the site's domain.
You need curl's help for that

```shell
curl --verbose -IL https://tv.eurosport.com
```
> \* Rebuilt URL to: https://tv.eurosport.com/ <br>
> \*   Trying 88.221.87.139... <br>
> \* Connected to tv.eurosport.com (88.221.87.139) port 443 (#0) <br>
> \* Initializing NSS with certpath: sql:/etc/pki/nssdb <br>
> \*   CAfile: /etc/pki/tls/certs/ca-bundle.crt <br>
>   CApath: none <br>
> \* Server certificate: <br>
> \* 	subject: CN=a248.e.akamai.net,O=Akamai Technologies Inc.,L=Cambridge,ST=MA,C=US <br>
> \* 	start date: Aug 27 16:10:12 2015 GMT <br>
> \* 	expire date: Aug 27 16:10:11 2016 GMT <br>
> \* 	common name: a248.e.akamai.net <br>
> \* 	issuer: CN=Verizon Akamai SureServer CA G14-SHA2,OU=Cybertrust,O=Verizon Enterprise Solutions,L=Amsterdam,C=NL <br>
> \* NSS error -12276 (SSL_ERROR_BAD_CERT_DOMAIN) <br>
> \* Unable to communicate securely with peer: requested domain name does not match the server's certificate. <br>
> \* Closing connection 0 <br>
> curl: (51) Unable to communicate securely with peer: requested domain name does not match the server's certificate. <br>
> curl --verbose -IL https://tv.eurosport.com <br>
> \* Rebuilt URL to: https://tv.eurosport.com/ <br>
> \*   Trying 88.221.87.139... <br>
> \* Connected to tv.eurosport.com (88.221.87.139) port 443 (#0) <br>
> \* Initializing NSS with certpath: sql:/etc/pki/nssdb <br>
> \*   CAfile: /etc/pki/tls/certs/ca-bundle.crt <br>
>   CApath: none <br>
> \* Server certificate: <br>
> \* 	subject: CN=a248.e.akamai.net,O=Akamai Technologies Inc.,L=Cambridge,ST=MA,C=US <br>
> \* 	start date: Aug 27 16:10:12 2015 GMT <br>
> \* 	expire date: Aug 27 16:10:11 2016 GMT <br>
> \* 	common name: a248.e.akamai.net <br>
> \* 	issuer: CN=Verizon Akamai SureServer CA G14-SHA2,OU=Cybertrust,O=Verizon Enterprise Solutions,L=Amsterdam,C=NL <br>
> \* NSS error -12276 (SSL_ERROR_BAD_CERT_DOMAIN) <br>
> \* Unable to communicate securely with peer: requested domain name does not match the server's certificate. <br>
> \* Closing connection 0 <br>
> curl: (51) Unable to communicate securely with peer: requested domain name does not match the server's certificate. <br>
