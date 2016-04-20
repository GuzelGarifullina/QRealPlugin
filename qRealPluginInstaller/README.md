Description
-----------

QRealPlugin is plugin for supporting general code style(?) of QRealProject.


License
-------

GNU License (?) 


Homepage
--------

QRealPlugin is hosted at https://github.com/GuzelGarifullina/QRealPlugin

Origins
-------


Dependencies
------------
QRealPlugin has the following dependencies:

1) Qt >= 5.5

2) Qt Creator >= 3.6.82

3) uncrustify 

  sudo apt-get install uncrustify

Installation
------------
To install plugin you need:

1) Unpack archive contents to the some directory(for example home/Example).

2) Open "global_settings.sh" file and set "QT_CREATOR_BUILD" variable full path to qtCreator plugins directory. 

For example home/username/Qt5.2.0/Tools/QtCreator/lib/qtcreator/plugins or /opt/Qt5.2.0/Tools/QtCreator/lib/qtcreator/plugins

3) Execute "qrealPluginInstaller.sh" file.

     Change into the unpacked directory
     cd home/Example/QRealPlugin{version of plugin}

     Make file executable
     chmod +x qrealPluginInstaller.sh

     Execute installer
     ./qrealPluginInstaller.sh












