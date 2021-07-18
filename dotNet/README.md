# .NET Stuff

## Linux and VS Code

I use Fedora and most of the time things work. Sometimes an update will break VS Code - specifically OmniSharp and that can cause _Red Squigglies_ disease, even though everything is fine.

The recommended method of installing a particular version of a .NET SDK on Fedora (as of 32) is simply

```bash
$ sudo dnf install dotnet-sdk-5.0
# Usual dnf output follows

# You can check what is installed with
$ sudo dnf list installed | grep -i net | grep -i -e dotnet -e aspnet
aspnetcore-runtime-3.1.x86_64                     3.1.16-1.fc34                        @updates              
aspnetcore-runtime-5.0.x86_64                     5.0.7-1.fc34                         @updates              
aspnetcore-targeting-pack-3.1.x86_64              3.1.16-1.fc34                        @updates              
aspnetcore-targeting-pack-5.0.x86_64              5.0.7-1.fc34                         @updates              
dotnet-apphost-pack-3.1.x86_64                    3.1.16-1.fc34                        @updates              
dotnet-apphost-pack-5.0.x86_64                    5.0.7-1.fc34                         @updates              
dotnet-host.x86_64                                5.0.7-1.fc34                         @updates              
dotnet-hostfxr-3.1.x86_64                         3.1.16-1.fc34                        @updates              
dotnet-hostfxr-5.0.x86_64                         5.0.7-1.fc34                         @updates              
dotnet-runtime-3.1.x86_64                         3.1.16-1.fc34                        @updates              
dotnet-runtime-5.0.x86_64                         5.0.7-1.fc34                         @updates              
dotnet-sdk-3.1.x86_64                             3.1.116-1.fc34                       @updates              
dotnet-sdk-5.0.x86_64                             5.0.204-1.fc34                       @updates              
dotnet-targeting-pack-3.1.x86_64                  3.1.16-1.fc34                        @updates              
dotnet-targeting-pack-5.0.x86_64                  5.0.7-1.fc34                         @updates              
dotnet-templates-3.1.x86_64                       3.1.116-1.fc34                       @updates              
dotnet-templates-5.0.x86_64                       5.0.204-1.fc34                       @updates              

```

## OmniSharp Failure with .NET 5.0

After an update, .NET 5.0 was updated and OmniSharp started to give errors and make a mess...

[See this OmniSharp issue](https://github.com/OmniSharp/omnisharp-vscode/issues/4360)

A recommeneded solution is what I am trying and documenting (hopefully it will work!)

1. Remove Fedora versions of all installed .NET SDKs
2. Add Microsoft's Repo and make it have priority for .NET SDKs
   1. Use the above to install the requred .NET SDKs - 3.1 and 5.0 for me
   2. Relax???

```bash
# 1.
$ sudo dnf erase dotnet-sdk-5.0.x86_64 dotnet-sdk-3.1.x86_64
$ sudo dnf clean all
# Gone!

# 2.
sudo rpm --import https://packages.microsoft.com/keys/microsoft.asc
sudo wget -O /etc/yum.repos.d/microsoft-prod.repo https://packages.microsoft.com/config/fedora/33/prod.repo
sudo dnf config-manager --save --setopt="*microsoft-*.priority=50"
sudo dnf install dotnet-sdk-5.0.x86_64

# Set environment - otherwise libhostfxr.so missing errors
DOTNET_ROOT=/usr/share/dotnet
```

### IT WORKED :)