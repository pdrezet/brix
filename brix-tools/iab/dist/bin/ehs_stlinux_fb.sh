#/bin/sh
# Run EHS on ST71000 under ST-Linux.
#
# Load framebuffer drivers
modprobe stmcore-display-stx7100
modprobe stmfb display0=1280x720-32@60
fbset -depth 32
# Run EHS
/opt/Lucid/ehs_linux_sh4
