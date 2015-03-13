Setting up Eclipse to link with Google Code SVN repository and enable Serial terminal monitoring directly from within Eclipse

# Introduction #
Because we decided to use Eclipse as our development platform and Google SVN to manage our source code, it is ideal to have Eclipse coordinate everything. Also, serial terminal window is very useful for debugging purposes; however, having to rely on Tetra Term is very inconvenient and a much better solution would be to have Eclipse connect to the serial port so everything can be done within Eclipse without the need of outside tools.

# Plug-in List #
The following steps are all done within Eclipse. Plug-ins are installed using the Eclipse Software Update Site feature.

### AVR for Eclipse ###
Update Site: http://avr-eclipse.sourceforge.net/updatesite/

This plug-in allows the user to program AVR chips directly from within Eclipse

### RXTX ###
Update Site: http://rxtx.qbang.org/eclipse/

This plug-in allows Eclipse to transmit or receive data through a serial port

### Target Management ###
Update Site: http://download.eclipse.org/dsdp/tm/updates/3.0

This plug-in provides an easy to use interface to setup a terminal window within Eclipse. It requires the RXTX plug-in pre-installed.

The ONLY component that is needed from this plug-in is the TargetManagement Terminal, all other components can be unchecked to avoid installing them.

### Subversive SVN Connectors ###
Update Site: http://community.polarion.com/projects/subversive/download/eclipse/2.0/update-site/

This plug-in allows Eclipse to access SVN repositories. After installing it, the first time the user trying to set up a SVN repository, another connector install window will pop up. This is normal and the user shouldjust proceed with the installation.