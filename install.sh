# Erase previous build folder
sudo rm -r build

# Set shell to exit in the first error
set -e

# Init and update submodules
git submodule init && git submodule update

# Setup github hooks
sudo cp test/hook/pre-commit .git/hooks/
sudo chmod +x .git/hooks/pre-commit

# Create build folder, generate MakeFile and install Armorial library
mkdir build && cd build
qmake install_path=/usr/lib ..
sudo make install
cd ..

# Clean old headers
if [ -d /usr/include/Armorial ];
    then
        if [ -w /usr/include/Armorial ];
            then
                rm -rf /usr/include/Armorial

            else
                echo ""
                echo ">> Armorial: Error in library headers installation! (Are you root?)"
                exit 1
        fi
fi

# Copies Armorial library headers to /usr/include
if [ -w /usr/include ];
    then
        mkdir /usr/include/Armorial
    else
        echo ""
        echo ">> Armorial: Error in library headers installation! (Are you root?)"
        exit 1
fi

if [ -d /usr/include/Armorial ];
    then
        cp -rf include/Armorial/* /usr/include/Armorial
        echo ""
        echo ">> Armorial: Installation complete!"

    else
        echo ""
        echo ">> Armorial: Error in library headers installation! (Are you root?)"
        exit 1
fi
