
# Tweaking Grub

Info on how to modify grub to launch a specific kernel by default.

Needed to select kernel that was compatible with NVidia driver

# Preventing Kernel Updates

    # Install the versionlock dnf plugin
    $ sudo dnf install versionlock

    # Block kernel updates
    $ sudo dnf versionlock add kernel

    # Config is in /etc/dnf/plugins
    file: versionlock.list

    # Added locks on Sat Jan 11 13:42:57 2020
    kernel-0:5.3.16-200.fc30.*
    kernel-0:5.4.7-100.fc30.*
    kernel-0:5.2.17-200.fc30.*

