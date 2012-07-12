#/bin/sh
# Build all Lucid tools prior to putting them in an installer

# Add Visual Studio to path
PATH=$PATH:/cygdrive/c/Program\ Files/Microsoft\ Visual\ Studio\ 8/Common7/IDE::/cygdrive/c/Program\ Files/Microsoft\ Visual\ Studio\ 8/vc/bin:/cygdrive/c/lint

# Unzip all examples
pushd ../Example-Archive
for zipfile in *.zip
do
	dir=${zipfile%.zip}
	echo Unzipping example $dir
	rm -rf $dir
	unzip $zipfile -d ../Examples/$dir
done
popd

# Make EHS for Windows
echo "Build EHS (windows)"
pushd ../../EHS
make TARGET=win_x86 clean
make TARGET=win_x86
cp ehs_win_x86.exe ../dist/bin
popd

# Make Lucid tools
echo Build Lucid Tools
pushd ../../tools/LucidTools
devenv LucidTools.sln /clean
echo Building Lucid Application Builder...
devenv LucidTools.sln /build Release /project LucidApplicationBuilder
if [ "0" -ne "$?" ]; then echo "**Build Failed" ; fi

echo "Building PngImage (required by LGB)..."
devenv LucidTools.sln /build Release /project PngImage
if [ "0" -ne "$?" ]; then echo **Build Failed ; fi

echo "Building pnglib (required by LGB)..."
devenv LucidTools.sln /build Release /project pnglib
if [ "0" -ne "$?" ]; then echo **Build Failed ; fi

echo "Building zlib (required by LGB)..."
devenv LucidTools.sln /build Release /project zlib
if [ "0" -ne "$?" ]; then echo **Build Failed ; fi

echo "Building Lucid GUI Builder..."
devenv LucidTools.sln /build Release /project LucidGUIBuilder
if [ "0" -ne "$?" ]; then echo **Build Failed ; fi

echo "Building RemoteControl..."
devenv LucidTools.sln /build Release /project RemoteControl
if [ "0" -ne "$?" ]; then echo **Build Failed ; fi
popd
