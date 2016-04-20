#!/bin/bash  
#QRealPluginInstaller

echo "Starting installation" 

#Directory of .sh file
EXE_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

#add glabal settings variables
SETTINGS_EXE=$EXE_PATH"/global_settings.sh"
source $SETTINGS_EXE
 
STARTED_PATH=$PWD

function load_plugin {
    echo "Start loading QReal plugin"
    if [ ! -d "$QT_CREATOR_BUILD" ];
      then echo "QT_CREATOR_BUILD not specified, please read README.md"
           exit 1
    fi
    
    cd $QT_CREATOR_BUILD

    if [ ! -f "$BEAUTIFIER_ISO_FILE" ];
      then echo "QT_CREATOR_BUILD not uncorrect specified, please read README.md"
           exit 1
    fi

    file=$EXE_PATH"/"$SETTINGS_DIR"/"$QREAL_ISO_FILE

    if [ ! -f "$QREAL_ISO_FILE" ];
        then
          #moving
          echo "$PWD"
          echo "Make moving $QREAL_ISO_FILE"
          cp $file .
      fi
}

function load_beautifier_settings {
    echo "Start loading beautifier settings"
    cd $QT_CREATOR_PATH

    if [ ! -d "$BEAUTIFIER_DIR" ];
      then 
        echo "Beautifier plugin not installed!"
        exit 1
    fi
    cd $BEAUTIFIER_DIR

    file=$EXE_PATH"/"$SETTINGS_DIR"/"$BEAUTIFIER_FILE

    if [ ! -f "$BEAUTIFIER_FILE" ];
        then
          #moving
          echo "$PWD"
          echo "Make moving $BEAUTIFIER_FILE"
          cp $file .
      fi
}

function load_qreal_settings {
    echo "Start loading qReal settings"
    cd $QT_CREATOR_PATH

    if [ ! -d "$QREAL_DIR" ];
      then 
        mkdir $QREAL_DIR
    fi
    cd $QREAL_DIR

    FILES_PATH=$EXE_PATH"/"$SETTINGS_DIR
    for fileName in "${FILE_NAMES[@]}"
    do
      file=$FILES_PATH"/"$fileName
      if [ ! -f "$fileName" ];
        then
          #moving
          echo "Make moving $file"
          cp $file .
      fi
    done
}


if [ ! -d "$QT_CREATOR_PATH" ]; 
  then
    echo "Cannot find Qt Creator"
    exit
fi

cd $QT_CREATOR_PATH
echo $PWD
load_plugin
load_beautifier_settings
load_qreal_settings 
    
cd $STARTED_PATH

