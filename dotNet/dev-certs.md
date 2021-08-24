# Development Certificate for .NET on Fedora

## Steps

```bash
# Clear any stored certificate
$ dotnet dev-cert --clean

# Verify nothing is there!
$ ll ~/.dotnet/corefx/cryptography/x509stores/my/

# Create a new certificate
$ dotnet dev-certs https --trust

# Check it's there!
$ ll ~/.dotnet/corefx/cryptography/x509stores/my/

# Export certificate to a local file
$ dotnet dev-certs https -ep ./localhost.crt --format PEM

# Add to local store
$ certutil -d sql:$HOME/.pki/nssdb -A -t "P,," -n localhost -i ./localhost.crt 
$ certutil -d sql:$HOME/.pki/nssdb -A -t "C,," -n localhost -i ./localhost.crt 

# Add to server store
$ sudo cp ./localhost.crt /etc/pki/tls/certs/localhost.pem
$ sudo update-ca-trust

# Finally, restart your browser and navigate to your https://localhost:NNNN/url
```
