source ./exportVariables.sh

cd $JETSON_KERNEL_SOURCE
make ARCH=$ARCH O=$JETSON_KERNEL_OUT -j4
sudo make ARCH=$ARCH O=$JETSON_KERNEL_OUT modules_install INSTALL_MOD_PATH=$JETSON_KERNEL_MODULE_OUT